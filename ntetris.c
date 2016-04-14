//	Programacao Sistematica	                          |
//	Trabalho Pratico 1                                |
//	Professor(a): Genaina                             |
//	Alunos:                                           |
//	  André Luiz de Moura Ramos Bittencourt           |
//	  Claudio Segala Rodrigues Silva Filho            |
//	  Anne Caroline de Assis Pereira                  |
//	  Hector Rocha Margittay                          |
// ___________________________________________________|

#include<ncurses.h>
#include<time.h> /* calcular o tempo */
#include<stdlib.h> 
#include<unistd.h> /* para a funcao getch_char e getch*/
#include<string.h> 
#include<termios.h> /* para a funcao getch_char e getch*/

int main() {
	char opt;
	
	init_ncurses();
	start();
	get_enter();
	do {
		show_menu();
		do { 
			opt = getch();
		}while(opt != '1' && opt != '2');
		if(opt == '1') {
		 	game_on();
		}
	} while(opt != '2');
	endwin();
	
	return 0;
}
