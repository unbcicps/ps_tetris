//	Programacao Sistematica	                          |
//	Trabalho Pratico 1                                |
//	Professor(a): Genaina                             |
//	Alunos:                                           |
//	  André Luiz de Moura Ramos Bittencourt           |
//	  Claudio Segala Rodrigues Silva Filho            |
//	  Anne Caroline de Assis Pereira                  |
//	  Hector Rocha Margittay                          |
// ___________________________________________________|

#include "estruturas.h"

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
	rank();
	endwin();
	return 0;
}
