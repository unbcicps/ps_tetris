#include "estruturas.h"
 
void init_ncurses() { /* Configura os parâmetros da Ncurses */
    initscr(); /* Inicia a tela padrão */
    cbreak(); /* Desabilita a bufferização da entrada */
    noecho(); /* Desabilita a apresentação da entrada na tela */
    curs_set(0);
    set_color(); /* Inicializa os sistema de cores */
    keypad(stdscr, TRUE); /* Ativa a leitura de teclas especiais do teclado */
    halfdelay(1); /* Configura um tempo limite de espera para entrada no programa */
}
 
void start() {
    show_title();
    usleep(2000000);
}
 
void get_enter() {
    while(getch()!='\n');
}
 
void set_game(){
    srand(time(NULL));
    memset(game.field, VAZIO, sizeof(int)*LARGURA*ALTURA);
    game.points = 0;
}
 
void start_clock() {
    clock_gettime(CLOCK_REALTIME, &(game.t_start));
}
 
int game_over(){
    if(collision(0,1) && currentBlock.y < LIMITE) return 1; /* O jogo termina quando uma peça para acima do limite */
    return 0;
}
 
void stop_clock() {
    clock_gettime(CLOCK_REALTIME, &(game.t_stop));
}
 
void get_duration() {
    stop_clock();
    game.duration = (game.t_stop.tv_sec - game.t_start.tv_sec) +
                    ((game.t_stop.tv_nsec - game.t_start.tv_nsec)/1E9);
}
 
void game_on(){
    set_game();
    show_instructions();
    get_enter();
    create_border();
    start_clock();
    do{
        new_block();
        currentBlock.gravSpeed = 1;
        currentBlock.gravTimer = 0;
        do {
            show_field();
            move_block(getch());
            apply_gravity();
        } while(!collision(0,1));
        show_field();
        any_complete_line();
    } while(!game_over());
    get_duration();
    rank();
    show_end();
    get_enter();
}
