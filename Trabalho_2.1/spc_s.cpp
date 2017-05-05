/*
	Compile com g++ -o spc_s spc_s.cpp -lncurses
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <ncurses.h>
#include <unistd.h>
//#include <thread>
#include <fstream>
#include <string>
#include <sstream>

#define DELAY 30000

#define SERVICE_PORT 5000
#define BUFSIZE 2048

void controle(unsigned char* pacote, int &has_shot, int &direction, int &has_armor){
	for (int i = 0 ; i < 5 ; i++){
		if(pacote[i] == 'D'){
			direction = 1;
			return;
		}
		else if(pacote[i] == 'E'){
			direction = -1;			
			return;
		}
		else if(pacote[i] == 'A'){
			has_armor = 1;
			return;
		}
		else if(pacote[i] == 'T'){
			has_shot = 1;
			return;
		}
	}
	return;

}

int main(int argc, char **argv)
{
	struct sockaddr_in myaddr;	/* our address */
	struct sockaddr_in remaddr;	/* remote address */
	socklen_t addrlen = sizeof(remaddr);		/* length of addresses */
	int recvlen;			/* # bytes received */
	int fd;				/* our socket */
	unsigned char buf[BUFSIZE];	/* receive buffer */

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

	/* create a UDP socket */
	if ((fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		perror("cannot create socket\n");
		return 0;
	}

	/* bind the socket to any valid IP address and a specific port */

	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family = AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port = htons(SERVICE_PORT);

	if (bind(fd, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) {
		perror("bind failed");
		return 0;
	}

	/* now loop, receiving data and printing what we received */
	for (;;) {
		
		recvlen = recvfrom(fd, buf, BUFSIZE, 0, (struct sockaddr *)&remaddr, &addrlen);
		
		
		getmaxyx(stdscr, max_y, max_x);

		if (recvlen > 0) {
			buf[recvlen] = 0;
			controle(buf, has_shot, direction, has_armor);
		}

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
		}
		else {
			bullet_x = bullet_x;
			bullet_y = bullet_y - 1 * bullet_speed;
		
			mvprintw(bullet_y, bullet_x, "|");
			
			// caso a bala esteja fora da janela, autoriza um proximo tiro
			if (bullet_y < 0) {
				has_shot = 0;
			}
		}

		direction = 0;
		has_armor = 0;
		refresh();
		usleep(DELAY);

	}
}
