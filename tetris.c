//	Programacao Sistematica	                      |
//	Trabalho Pratico 1                            |
//	Professor(a): Genaina                         |
//	Alunos:                                       |
//		André Luiz de Moura Ramos Bittencourt     |
//		Claudio Segala Rodrigues Silva Filho      |
//		Anne Caroline de Assis Pereira            |
//		Hector Rocha Margittay                    |
// _______________________________________________|


// Bibliotecas --------------------------------------------------------------------------------------------------------------------------------------

#include<time.h> /* calcular o tempo */
#include<stdio.h> /* para entrada e saida padroes*/
#include<stdlib.h> 
#include<unistd.h> /* para a funcao getch_char e getch*/
#include<string.h> 
#include<termios.h> /* para a funcao getch_char e getch*/

// Defines ------------------------------------------------------------------------------------------------------------------------------------------

#define RESET "\x1b[0m"
#define KBLC "\x1b[30m"
#define KRED "\x1b[31m"
#define KGRN "\x1b[32m"
#define KYEL "\x1b[33m"
#define KBLU "\x1b[34m"
#define KMAG "\x1b[35m"
#define KCYN "\x1b[36m"
#define KWHT "\x1b[37m"
#define BGBLC "\x1b[40m"
#define BGRED "\x1b[41m"
#define BGGRN "\x1b[42m"
#define BGYEL "\x1b[43m"
#define BGBLU "\x1b[44m"
#define BGMAG "\x1b[45m"
#define BGCYN "\x1b[46m"
#define BGWHT "\x1b[47m"
#define LARGURA 15
#define ALTURA 25
#define LIMITE 5
#define HORIZONTAL 0
#define VERTICAL 1
#define VAZIO 0

// Structs -------------------------------------------------------------------------------------------------------------------------------------------

typedef struct{
	int field[LARGURA][ALTURA], points;
	double duration;
} tetris;

typedef struct{
	int color, direction, size, x, y;
} block;

// Variaveis Globais ---------------------------------------------------------------------------------------------------------------------------------

tetris game;
block currentBlock;
int next_round = 1;

// Funcoes -------------------------------------------------------------------------------------------------------------------------------------------

// MODULO TELA________________________________________________________________________________________________________________________________________

void limpa_tela_legal(){
	system("clear || cls");
}

void show_title(){
	limpa_tela_legal();
	printf(KBLU "______________  ______________  ______________  ___________    __________  ______________ \n" RESET);
	printf(KBLU "      |         |                     |         |          \\       ||      |              \n" RESET);
	printf(KBLU "      |         |                     |         |           |      ||      |              \n" RESET);
	printf(KBLU "      |         |_____________        |         |__________/       ||      |_____________ \n" RESET);
	printf(KBLU "      |         |                     |         |         \\        ||                   | \n" RESET);
	printf(KBLU "      |         |                     |         |          \\       ||                   | \n" RESET);
	printf(KBLU "      |         |_____________        |         |           \\  ____||____   ____________| \n" RESET);
	printf("\n\n");
}

void show_menu() {
	limpa_tela_legal();
	printf(KBLU "1 - Jogar\n" RESET);
	printf(KBLU "2 - Sair\n" RESET);
}

void show_instructions(){
	limpa_tela_legal();
	printf(" Use as teclas [A], [S] e [D] (pode usar CapsLock) para mover as pecas\n\n");
	printf("                  Aperte [ENTER] para ir ao MENU\n");
}

void show_field(){
	int x, y;
	limpa_tela_legal();
    printf(KBLC BGWHT" Pontuacao: %d\n\n" RESET, game.points);
    for(x = 0; x < LARGURA+2; x++)
    	printf(BGWHT "  ");
    printf(RESET "\n");
    for(y = 0; y < ALTURA; y++){
    	printf(BGWHT "  ");
		for(x = 0; x < LARGURA; x++) {
			if(game.field[x][y] == VAZIO) {
				if(y == LIMITE)	
					printf(KWHT BGBLC "--");
				else 
					printf(BGBLC "  ");
			}
			else {
				switch(currentBlock.color) {
					case 1:	printf(KRED);
							break;
					case 2:	printf(KGRN);
							break;
					case 3:	printf(KYEL);
							break;
					case 4:	printf(KBLU);
							break;
					case 5:	printf(KMAG);
							break;
					case 6:	printf(KCYN);
							break;
				}
				printf(BGBLC "[]");
			}
		}
		printf(BGWHT "  \n" RESET);
    }
    for(x = 0; x < LARGURA+2; x++)
    	printf(BGWHT "  ");
    printf(RESET "\n");
}

void show_end(){
	limpa_tela_legal();
	printf(KRED "Vc pontuou %d em %lf\n"  RESET, game.points, game.duration);
	printf(KGRN "Parabens por ter chegado tao longe jovem padawan\n" RESET);
	printf(KGRN "Todo seu progresso foi inutil pois nao guardamos ranking ainda\n" RESET);
	printf(KGRN "Sinta-se livre de baixar um app de tetris decente\n" RESET);
	printf(KGRN "Feito por: programadores escravos da bolivia\n" RESET);
	printf(KGRN "Fazer o que?\n" RESET);
	printf(KGRN " ¯\\_(ツ)_/¯\n");
	usleep(500000);
}

// MODULO BLOCO_______________________________________________________________________________________________________________________________________

void put_block(int newX, int newY) {
	int i, dirX, dirY;
	
	if(currentBlock.direction == HORIZONTAL) {
		dirX = 1;
		dirY = 0;
	}
	else if(currentBlock.direction == VERTICAL) {
		dirX = 0;
		dirY = 1;
	}
	
	for(i = 0; i < currentBlock.size; i++)
		game.field[currentBlock.x + (dirX * i)][currentBlock.y + (dirY * i)] = VAZIO;
		
	for(i = 0; i < currentBlock.size; i++)
		game.field[newX + (dirX * i)][newY + (dirY * i)] = currentBlock.color;
}

void new_block(){
	int c = 1 + rand() % 5;

	while(c == currentBlock.color) c = 1 + rand() % 5;
	currentBlock.color = c;
	currentBlock.direction =rand() % 2;
	currentBlock.size = rand() % 3 + 3;
	currentBlock.y = 0;
	currentBlock.x = rand()%(LARGURA-(currentBlock.direction?0:currentBlock.size-1)); printf("x=%d\n", currentBlock.x);
	put_block(currentBlock.x, currentBlock.y);
}

int collision(int deslocX, int deslocY) {
	int i, j, origX, origY, dirX, dirY, x, y, check;
	
	origX = currentBlock.x;
	origY = currentBlock.y;

	if(currentBlock.direction == HORIZONTAL) {
		dirX = 1;
		dirY = 0;
	}
	else if(currentBlock.direction == VERTICAL) {
		dirX = 0;
		dirY = 1;
	}

	for(i = 0 ; i < currentBlock.size ; i++) {
		x = origX + (dirX * i) + deslocX;
		y = origY + (dirY * i) + deslocY;
		if(x >= 0 && x < LARGURA && y >= 0 && y < ALTURA) {
			if(game.field[x][y] != VAZIO) {
				check = 0;
				for(j = 0 ; j < currentBlock.size ; j++) {
					if(x == origX + (dirX * j) && y == origY + (dirY * j))
						check = 1;
				}
				if(check == 0)
					return 1;
			}
		}
		else 
			return 1;
	}

	return 0;
}

void move_block(char opt){
	int newX = currentBlock.x, newY = currentBlock.y;
	
	if(opt == 'S'){ /* move para baixo */ 
		while(!collision(0, 1)) {
			newY++;
			put_block(newX, newY);
			currentBlock.x = newX;
			currentBlock.y = newY;	
			show_field();
			usleep(5000);
		}
	}
	else if(opt == 'D'){ /* move para direita */ 
		if(!collision(1, 0))
			newX++;	
	}
	else if(opt == 'A'){ /* move para esquerda */ 
		if(!collision(-1, 0))
			newX--;	
	}
	
	if(newX != currentBlock.x || newY != currentBlock.y) {
		put_block(newX, newY);
		currentBlock.x = newX;
		currentBlock.y = newY;	
	}
}

void cut_this_line(int y){
	int x;
	for(;y>=1;y--)
		for(x=0;x<LARGURA;x++)
			game.field[x][y]=game.field[x][y-1];
}

void any_complete_line(){
	int x, y, cnt;
	for(y = LIMITE; y < ALTURA; y++){
		cnt = 0;
		for(x = 0; x < LARGURA; x++)
			if(game.field[x][y] != VAZIO) cnt += 1;
		if(cnt == LARGURA) {	/* confere se o contador tem o tamanho da linha maxima*/
			cut_this_line(y);
			game.points += 100;
		}
	}
}

// MODULO ENGINE______________________________________________________________________________________________________________________________________

void start() {
	show_title();
	usleep(1500000);
}

char getch(void) {
	int ch;
	struct termios oldt;
	struct termios newt;
	tcgetattr(STDIN_FILENO, &oldt); /*store old settings */
	newt = oldt; /* copy old settings to new settings */
	newt.c_lflag &= ~(ICANON | ECHO); /* make one change to old settings in new settings */
	tcsetattr(STDIN_FILENO, TCSANOW, &newt); /*apply the new settings immediatly */
	ch = getchar(); /* standard getchar call */
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt); /*reapply the old settings */
	return ch; /*return received char */
}

char read_input() {
	char ch;
	
	ch = getch();
	fflush(stdin);
	if(ch >= 'a' && ch <= 'z')
		ch -= 'a' - 'A';
	return ch;
}

void set_game(){
	srand(time(NULL));
	memset(game.field, VAZIO, sizeof(int)*LARGURA*ALTURA);
	game.points = 0;
}

int game_over(){
	if(currentBlock.y < LIMITE) return 1;
	return 0;
}

void game_on(){
	clock_t t_begin = clock() / CLOCKS_PER_SEC, t_end;
	char input;
	
	set_game();
	show_instructions();
	do{
		new_block();
		do {
			show_field();
			input = read_input();
			move_block(input);
		} while(!collision(0,1));
		show_field();
		any_complete_line();
	} while(!game_over());
	t_end = clock() / CLOCKS_PER_SEC;
	/* De acordo com o dito pelo IME em uma de suas apostilas, esse metodo so consegue guardar ate 35 minutos*/
	game.duration = t_end - t_begin;
	show_end();
}

int main() {
	char opt;
	
	start();
	do {
		show_menu();
		do { 
			opt = read_input();
		}while(opt != '1' && opt != '2');
		if(opt == '1') {
		 	game_on();
		}
	} while(opt != '2');
	return 0;
}