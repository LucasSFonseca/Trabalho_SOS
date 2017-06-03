#include "procStat.h"

using namespace std;

proc_data proc;

int filter(const struct dirent *dir)
{
     return !fnmatch("[1-9]*", dir->d_name, 0);
}

const char* processdir(const struct dirent *dir)
{
    return dir->d_name;
}


/*
** Função que percorre a pasta /proc/.
*/
void procCounter()
{
    struct dirent **namelist;
    int n;
    
    n = scandir("/proc", &namelist, filter, 0);
	if (n < 0){
    	perror("Not enough memory.");
    }
    else {
    	while(n--) {
    		proc.pid = processdir(namelist[n]);
        	getProcStat(processdir(namelist[n]));
        	getVmSwap(processdir(namelist[n]));

        	free(namelist[n]);
	  	}
	  	free(namelist);
    }	
     
}
/*
** getProcStat: Percorre o arquivo /proc/$PID/stat, e recolhe as informações necessárias.
*/


void getProcStat(const char *pid){

	ifstream file;
	char str[20];
	strcpy(str, "/proc/");
    strcat(str, pid);
    strcat(str, "/stat");

    
    file.open(str);
    std::string word;
    char x ;
    word.clear();
    int i = 0;

    if(file.is_open()){
    	while(i < 23){
    		x = file.get();
    		while (x != ' '){
	            word = word + x;
	            x = file.get();
	        }
	        if(i == 9){ // Page Faults Minor.
	        	fltMin = word;
	        	
	        }
	        else if (i == 11){ // Page Faults Major.
	        	fltMaj = word;
	        }
	        else if(i == 22){ // Memória ocupada.
	        	vmSize = word;
	        }
	        word.clear();
	   	    i++;
	    }
	    file.close(); 		
	}
	else{
		std::cout << "Erro" << std::endl;
	}
}

/*
** getVmSwap: Percorre o /proc/$PID/status
*/

void getVmSwap(const char *pid){
	
	ifstream file;
	char str[20];
	strcpy( str,"/proc/");
    strcat( str, pid);
    strcat( str, "/status");

    file.open(str);
    char c;

    if (file.is_open()){
    	while(file.get(c)){
    		vmSwap = vmSwap + c;
    		if ( c == ':' ){

    			if(vmSwap == "VmSwap:"){
    			
    				vmSwap.clear();

    				while(file.get(c)){
    					vmSwap = vmSwap + c;
    					
    					if( c == '\n'){
    						vmSwap.erase(std::remove(vmSwap.begin(),vmSwap.end(),' '),vmSwap.end());
    						vmSwap.erase(std::remove(vmSwap.begin(),vmSwap.end(),'k'),vmSwap.end());
    						vmSwap.erase(std::remove(vmSwap.begin(),vmSwap.end(),'B'),vmSwap.end());
    						vmSwap.erase(std::remove(vmSwap.begin(),vmSwap.end(),'\n'),vmSwap.end());
							proc.vm_swap = vmSwap;
    						goto end;
    					}
    				}
    			}
    			vmSwap.clear();
    		}
    		else if( c == '\n'){
    			vmSwap.clear();
    		}
    	}

    }

    end:

	proc.flt_min = fltMin;
	proc.flt_maj = fltMaj;
	proc.vm_size = vmSize;

	// printw("%-10s %-10s %-10s %-10s %-10s \n", proc.pid, proc.flt_min.c_str(), proc.flt_maj.c_str(), proc.vm_size.c_str(), proc.vm_swap.c_str());
	processes.push_back(proc);

    file.close();

}

int main(){
	std::list<proc_data>::iterator it;

	initscr();
   	printw("%-10s %-10s %-10s %-10s %-10s \n", "PID", "Maj", "Min", "Mem(kB)", "Swap");	
	while (1) {
		procCounter();
		
		for (it = processes.begin(); it != processes.end(); it++) {
			printw("%-10s %-10s %-10s %-10s %-10s \n", it->pid, it->flt_maj.c_str(), it->flt_min.c_str(), it->vm_size.c_str(), it->vm_swap.c_str());
		}

		refresh();
		usleep(500000);
	}
	getch();
	endwin();

	return 0;
}



