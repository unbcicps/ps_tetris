/*    BIBLIOTECAS -------------------------------------------------------------------- */
#include <time.h> 		/* biblioteca que permite manipulação de tempo */
#include <stdio.h>		/* biblioteca padrão de entrada e saída */
#include <stdlib.h> 	/* biblioteca padrão de funções adicionais */
#include <unistd.h> 	/* para a funcao getch_char e getch*/
#include <string.h> 	/* biblioteca para manipulação de strings */
#include <ncurses.h>	/* biblioteca de interface gráfica entre outras coisas */

/* DEFINIÇÕES --------------------------------------------------------------------- */
#define LARGURA 15
#define ALTURA 25
#define LIMITE 5
#define HORIZONTAL 0
#define VERTICAL 1
#define VAZIO 0
#define FALSO 2
#define GRAVITYMAX 10

/* ESTRUTURAS --------------------------------------------------------------------- */
typedef struct{
	int field[LARGURA][ALTURA],			// matriz usada para simular o tetris 
		points; 						// pontos da partida atual
	struct timespec t_start, t_stop;	// estrutura usada para saber o tempo de inicio e final da partida
	double duration;					// guarda o tempo total da partida
} tetris;

typedef struct{
	int x, y;							// estrutura de coordenadas
} loc;

typedef struct{
	loc dot[4];							// guarda as 4 posições de cada peça
	int color, 							// cor da peça
		size, 							// serve para saber o tamanho da matriz simulada para o giro e a movimentação das peças
		x, y, 							// coordenadas da matriz simulada para girar e mover a peça
		gravSpeed,						// guarda a velocidade da gravidade
		gravTimer;						// atualiza a posição vertical da peça de acordo com a sua velocidade
} block;

typedef struct{
	char name[11]; 						// máximo de caracteres para o nome do player é 10
	int points;							// pontuação do jogador atual
	double time;						// guarda a duração da partida
} player;

/* VARIÁVEIS GLOBAIS -------------------------------------------------------------- */
tetris game;			// grava as informações do jogo atual
block currentBlock;		// bloco atual
player 	currentPlayer, 	// jogador atual
		ranked[6]; 		// os 5 rankeados + o atual
