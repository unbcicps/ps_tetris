#include "estruturas.h"

/* função para colocar dor no ncurses */
void set_color() {
	start_color();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_YELLOW, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(6, COLOR_CYAN, COLOR_BLACK);
	init_pair(7, COLOR_WHITE, COLOR_BLACK);
	init_pair(8, COLOR_BLACK, COLOR_WHITE);
}

/* função que mostra a tele de início do jogo */
void show_title(){
	int i;
	clear();
	move(0,0);
	printw(" _____   _____   _____   _____   _   _____  \n");
	printw("|_|_|_| |_|_|_| |_|_|_| |_|_|_| |_| |_|_|_| \n");
	printw("  |_|   |_|___    |_|   |_|     |_| |_|___  \n");
	printw("  |_|   |_|_|_|   |_|   |_|     |_| |_|_|_| \n");
	printw("  |_|   |_|___    |_|   |_|     |_|  ___|_| \n");
	printw("  |_|   |_|_|_|   |_|   |_|     |_| |_|_|_| \n\n");
	printw("      Aperte [ENTER] para continuar\n");
	for(i = 0; i < 6; i++) {
		mvchgat(i, 0, 8, A_BOLD, 1, NULL);
		mvchgat(i, 8, 8, A_BOLD, 6, NULL);
		mvchgat(i, 16, 8, A_BOLD, 1, NULL);
		mvchgat(i, 24, 8, A_BOLD, 2, NULL);
		mvchgat(i, 32, 4, A_BOLD, 5, NULL);
		mvchgat(i, 36, 8, A_BOLD, 3, NULL);
	}
	refresh();
}

/* função que mostra a tela de menu */
void show_menu() {
	clear();
	attron(A_BOLD | COLOR_PAIR(4));
	printw(" ________________\n");
	printw("|                |\n");
	printw("| [1][  Jogar  ] |\n");
	printw("|________________|\n");
	printw(" ________________\n");
	printw("|                |\n");
	printw("| [2][  Rank   ] |\n");
	printw("|________________|\n");
	printw(" ________________\n");
	printw("|                |\n");
	printw("| [3][  Sair   ] |\n");
	printw("|________________|\n");
	attroff(A_BOLD | COLOR_PAIR(4));
	mvchgat(2, 8, 5, A_BOLD, 7, NULL);
	mvchgat(6, 8, 4, A_BOLD, 3, NULL);
	mvchgat(10, 8, 4, A_BOLD, 1, NULL);
	refresh();
}

/* função que mostra as intruções do tetris */
void show_instructions(){
	clear();
	printw("     [ˆ] ---------> Gira a peça\n\n");
	printw(" [<] [V] [>] -----> Move para Direita\n\n");
	printw("  |   |-----------> Move para Baixo\n");
	printw("  |---------------> Move para Esquerda\n");
	refresh();
}

void create_border() {
	int x, y;
	
	clear();
	attron(COLOR_PAIR(8));
	for(y = 0; y < ALTURA + 3; y++)
		for(x = 0; x < (LARGURA * 2) + 2; x++)
			mvaddch(y, x, ' ');
	mvprintw(0, 1, "Pontuacao:");
	attroff(COLOR_PAIR(8));
}

void show_field(){
	int x, y;
	create_border();
	attron(COLOR_PAIR(8));
	mvprintw(0, 11, "%07d %d", game.points, currentBlock.gravity);
	attroff(COLOR_PAIR(8));
    for(y = 0; y < ALTURA; y++)
		for(x = 0; x < LARGURA; x++) {
			move(y + 2, (2 * x) + 1);
			attron(A_NORMAL);
			if(game.field[x][y] == VAZIO) {
				attron(COLOR_PAIR(7));
				if(y == LIMITE)	
					printw("--");
				else 
					printw("  ");
				attroff(COLOR_PAIR(7));
			}
			else {
				switch(game.field[x][y]) {
					case 1:	attron(COLOR_PAIR(1));
							break;
					case 2:	attron(COLOR_PAIR(2));
							break;
					case 3: attron(COLOR_PAIR(3));
							break;
					case 4:	attron(COLOR_PAIR(4));
							break;
					case 5:	attron(COLOR_PAIR(5));
							break;
					case 6:	attron(COLOR_PAIR(6));
							break;
					case 7:	attron(COLOR_PAIR(7));
							break
;				}
				attron(A_BOLD);
				printw("[]");
				attroff(A_BOLD);
			}
		}
	refresh();
}

void show_end(){
	clear();
	refresh();
	attrset(COLOR_PAIR(1));
	printw("Voce fez %d pontos em %d minutos e %d segundos\n", game.points, (int)(game.duration/60), (int)(game.duration-(game.duration/60)));
	refresh();
	usleep(2000000);
	attrset(COLOR_PAIR(2));
	printw("Parabens por ter chegado tao longe jovem padawan\n");
	refresh();
	usleep(2000000);
	printw("Todo seu progresso foi inutil pois nao guardamos ranking ainda\n" );
	refresh();
	usleep(2000000);
	printw("Sinta-se livre de baixar um app de tetris decente\n");
	refresh();
	usleep(2000000);
	printw("Feito por: programadores escravos da bolivia\n");
	refresh();
	usleep(2000000);
	printw("Fazer o que?\n");
	printw("¯\\_(^-^)_/¯\n");
	refresh();
	attrset(A_NORMAL);
	printw("      Aperte [ENTER] para continuar\n");
}

