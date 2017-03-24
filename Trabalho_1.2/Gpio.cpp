#ifndef _GPIO_
#define _GPIO_

#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

const int HIGH = 1;
const int LOW = 0;

class Gpio{
	public:
		char gpio[4];
		char direction[4];
		Gpio(const char *gp, const char* direc);
		void setDirection(char* direc);;
		void setValue(int value);
		char getValue();
};

Gpio::Gpio(const char *gp, const char* direc){
	strcpy(gpio, gp);
	strcpy(direction, direc);
	setDirection(direction);
	 
}

void Gpio::setDirection(char* direc){
	ofstream file;
	//char str[50] = "/home/lucaspc2/Downloads/LSOP/Trabalho 2/direc";
	char str[50];
	strcpy( str, "/sys/class/gpio/gpio");
	strcat( str, gpio);
	strcat(str, "/direction");

	file.open(str);

	if(file.is_open()){
		file.write(direc, sizeof(direc));

		file.close();
	}
	else{
		std::cout << "Erro direction!!" << std::endl;
	}
	return;
}

void Gpio::setValue(int value){
	if(strcmp("out", direction) == 0){
		ofstream file;
		//char str[50] = "/home/lucaspc2/Downloads/LSOP/Trabalho 2/text";
		char str[50];
		strcpy( str, "/sys/class/gpio/gpio");
		strcat( str, gpio);
		strcat(str, "/value");

		file.open(str);

		if(file.is_open()){
			if(value == 1){
				file.put('1');
				return;
			}
			else{
				file.put('0');
				return;
			}

			file.close();
		}
		else{
			std::cout << "Erro value!!" << std::endl;
		}
		return;
	}
	else{
		std::cout << "Esse pino é de entrada" << std::endl;
		return;
	}
}

char Gpio::getValue(){
	ifstream file;

	//char str[50] = "/home/lucaspc2/Downloads/LSOP/Trabalho 2/text";
	char str[50];
	strcpy( str, "/sys/class/gpio/gpio");
	strcat( str, gpio);
	strcat(str, "/value");

	file.open(str);
	char aux;

	if(file.is_open()){
		aux = file.get();

		file.close();
		return aux;
	}
	else{
		std::cout << "Erro file!" << std::endl;
	}
	return 'a';
}

#endif