#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include <iostream>
#include <chrono>
#include <thread>
#include "Gpio.cpp"
#include "unistd.h"
#include "signal.h"

static unsigned long long lastTotalUser, lastTotalUserLow, lastTotalSys, lastTotalIdle;

void init(){
    FILE* file = fopen("/proc/stat", "r");
    fscanf(file, "cpu %llu %llu %llu %llu", &lastTotalUser, &lastTotalUserLow,
        &lastTotalSys, &lastTotalIdle);
    fclose(file);
}

double getCurrentValue(){
    double percent;
    FILE* file;
    unsigned long long totalUser, totalUserLow, totalSys, totalIdle, total;

    file = fopen("/proc/stat", "r");
    fscanf(file, "cpu %llu %llu %llu %llu", &totalUser, &totalUserLow,
        &totalSys, &totalIdle);
    fclose(file);

    if (totalUser < lastTotalUser || totalUserLow < lastTotalUserLow ||
        totalSys < lastTotalSys || totalIdle < lastTotalIdle){
        //Overflow detection. Just skip this value.
        percent = -1.0;
    }
    else{
        total = (totalUser - lastTotalUser) + (totalUserLow - lastTotalUserLow) +
            (totalSys - lastTotalSys);
        percent = total;
        total += (totalIdle - lastTotalIdle);
        percent /= total;
        percent *= 100;
    }

    lastTotalUser = totalUser;
    lastTotalUserLow = totalUserLow;
    lastTotalSys = totalSys;
    lastTotalIdle = totalIdle;

    return percent;
}

int main(){
    char retCode;
    Gpio mygpio("50", "out"); //Verde
    Gpio mygpio2("115", "in"); //amarelo
    Gpio mygpio3("14", "out");
    Gpio mygpio4("51", "out"); //vermelho

    while(1){    
        std::chrono::milliseconds timespan(1000);
        std::this_thread::sleep_for(timespan);
        
        pid_t pid = fork();

        double aux = getCurrentValue();
        
        if(aux <= 25){
            mygpio.setValue(HIGH);
            mygpio3.setValue(LOW);
            mygpio4.setValue(LOW);
            std::cout << "Cpu: " << aux << "%"<< std::endl;
        }
        else if(aux <= 50){
            mygpio.setValue(LOW);
            mygpio3.setValue(HIGH);
            mygpio4.setValue(LOW);
            std::cout << "Cpu: " << aux << "%"<< std::endl;
        }
        else if(aux <= 75){
             mygpio.setValue(LOW);
            mygpio3.setValue(LOW);
            mygpio4.setValue(HIGH);
        }
        else{
            while( mygpio2.getValue() == '0'){
                std::cout << "Cpu: " << aux << "%"<< std::endl;
                mygpio.setValue(HIGH);
                mygpio3.setValue(HIGH);
                mygpio4.setValue(HIGH);

    
                std::this_thread::sleep_for(timespan);

                mygpio.setValue(LOW);
                mygpio3.setValue(LOW);    
                mygpio4.setValue(LOW);

            }

            mygpio.setValue(LOW);
            mygpio3.setValue(LOW);
            mygpio4.setValue(LOW);

            killpg(getpgid(pid), SIGTERM);

        }
        init();
    }
    
}