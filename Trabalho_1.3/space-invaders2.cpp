/* Esse codigo deve ser compilado com as flags -lncurses e -pthread: 

	g++ space-invaders2.cpp -pthread -o space-invaders -lncurses
	
*/

#include <ncurses.h>
#include <unistd.h>
#include <thread>
#include <fstream>
#include <string>
#include <sstream>
#include "Gpio.cpp"

#define DELAY 30000
#define PATH_ADC "/sys/bus/iio/devices/iio:device0/in_voltage"



int input;
Gpio mygpio("115", "in");

int readAnalog(int number){
   stringstream ss;
   ss << PATH_ADC << number << "_raw";
   fstream fs;
   fs.open(ss.str().c_str(), fstream::in);
   fs >> number;
   fs.close();
   return number;
}

void controleDirecao(int &direcao){
	int value = readAnalog(1);
	direcao = 0;

	if( value > 2500){
		direcao = 1;
	}
	else if(value < 2048){
		direcao = -1;
	}
}

void controleTiro(int &tiro , int &direcao, int &armadura){
	if(mygpio.getValue() == '1' && direcao == 0 && armadura == 0){
		tiro = 1;
	}
	else{
		tiro = 0;
	}
}

void controleArmadura( int &armadura, int &direcao){
	if ( readAnalog(3) < 1000 && direcao == 0){
		armadura = 1;
	}
	else{
		armadura = 0;
	}
} 

	
int main(int argc, char *argv[]) {
	int x = 50, y = 25;
	int max_y = 0, max_x = 0;
	int next_x = 0;
	
	int bullet_x = 0, bullet_y = 0;
	int bullet_speed = 2;              // velocidade da bala
	int has_shot = 0;                  // flag de tiro
	int has_armor = 0; 					// Flag de armadura
	int direction = 1;				   

	initscr();               // inicia a tela padrao
	start_color();
	noecho();                // retira os echos dos outputs
	curs_set(FALSE);         // esconde o cursor
	timeout(100);            // timeout pra caso nao haja interacao
	keypad(stdscr, TRUE);    // ativa teclado
	
	// pega tamanho maximo da janela padrao (stdscr, inicializada em initscr())
	getmaxyx(stdscr, max_y, max_x);
	
	x = max_x/2;
	mvprintw(y, x, "o");
	
	// configurando cores
	init_pair(1, COLOR_BLACK, COLOR_RED);
	init_pair(2, COLOR_BLACK, COLOR_GREEN);

	while (1) {
		
		// INPUT DO CONTROLE
		//input = getch();
	
		/*	
			Sobre Input do Controle:
			Atualmente,
			o input vem da funcao getch(), da biblioteca ncurses. Duas
			threads, uma para cada (potenciometro e botao), vao monitorar os 				controles para atualizar o valor do input.
		
			Para mover e atirar, basta calcular o valor atual do 
			potenciometro e checar o botao:
		
			 - caso o valor atual do potenciometro seja maior que a 
			   metade, input = KEY_RIGHT
			   (simulando essa tecla sendo pressionada)
			 - caso o valor atual do potenciometro seja menor que a 
			   metade, input = KEY_LEFT
			 - caso o botao tenha sido pressionado, input = KEY_UP
			 	- o botao tem maior prioridade
		*/
	
		getmaxyx(stdscr, max_y, max_x);
		
		
		thread t1 (controleDirecao, ref(direction));
		thread t2 (controleArmadura, ref(has_armor), ref(direction));
		thread t3( controleTiro, ref(has_shot), ref(direction), ref(has_armor));

				
		// limpa a tela
		clear();
		
		// desenha nave
		x += direction;

		if (has_armor == 1)
			attron(COLOR_PAIR(1));
		else
			attron(COLOR_PAIR(2));

		mvprintw(y, x, "/\\");
		
		// desenha a bala
		if (has_shot == 0) {
			bullet_x = x;
			bullet_y = y;
		} else {
			bullet_x = bullet_x;
			bullet_y = bullet_y - 1 * bullet_speed;
		
			mvprintw(bullet_y, bullet_x, "|");
			
			// caso a bala esteja fora da janela, autoriza um proximo tiro
			if (bullet_y < 0) {
				has_shot = 0;
			}
		}
		
		// atualiza a tela
		refresh();
		t1.join();
		t2.join();
		t3.join();

		usleep(DELAY);
	}

	endwin();
}	