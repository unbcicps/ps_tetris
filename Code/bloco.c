#include "estruturas.h"
 
int put_block(int newX, int newY) {
    int i;
   
    for(i = 0; i < 4; i++)
        game.field[currentBlock.x + currentBlock.dot[i].x][currentBlock.y + currentBlock.dot[i].y] = VAZIO; /* Esvazia todas as posições na matriz que formam o bloco na sua posição atual */
       
    for(i = 0; i < 4; i++)
        game.field[newX + currentBlock.dot[i].x][newY + currentBlock.dot[i].y] = currentBlock.color; /*  Preenche todas as posições na matriz que formam o bloco na sua nova posição */
   
    currentBlock.x = newX;
    currentBlock.y = newY;
   
    return 0;
}
 
void new_block(){
 
    int c = 1 + rand() % 5, type = rand() % 7, i;
 
    while(c == currentBlock.color) c = 1 + rand() % 5; /* Muda a cor do bloco em relação ao anterior */
   
    currentBlock.color = c;
   
    switch(type) {
        case 0: currentBlock.dot[0].x = 0;  /* [][] */
                currentBlock.dot[0].y = 0;  /* [][] */
                currentBlock.dot[1].x = 1;
                currentBlock.dot[1].y = 0;
                currentBlock.dot[2].x = 0;
                currentBlock.dot[2].y = 1;
                currentBlock.dot[3].x = 1;
                currentBlock.dot[3].y = 1;
                currentBlock.size = 2;
                break;
        case 1: currentBlock.dot[0].x = 0;  /* [][][] */
                currentBlock.dot[0].y = 1;  /*   []   */
                currentBlock.dot[1].x = 1;
                currentBlock.dot[1].y = 1;
                currentBlock.dot[2].x = 2;
                currentBlock.dot[2].y = 1;
                currentBlock.dot[3].x = 1;
                currentBlock.dot[3].y = 2;
                currentBlock.size = 3;
                break;
        case 2: currentBlock.dot[0].x = 0;  /* [][]   */
                currentBlock.dot[0].y = 1;  /*   [][] */
                currentBlock.dot[1].x = 1;
                currentBlock.dot[1].y = 1;
                currentBlock.dot[2].x = 1;
                currentBlock.dot[2].y = 2;
                currentBlock.dot[3].x = 2;
                currentBlock.dot[3].y = 2;
                currentBlock.size = 3;
                break;
        case 3: currentBlock.dot[0].x = 1;  /*   [][] */
                currentBlock.dot[0].y = 1;  /* [][]   */
                currentBlock.dot[1].x = 2;
                currentBlock.dot[1].y = 1;
                currentBlock.dot[2].x = 0;
                currentBlock.dot[2].y = 2;
                currentBlock.dot[3].x = 1;
                currentBlock.dot[3].y = 2;
                currentBlock.size = 3;
                break;
        case 4: currentBlock.dot[0].x = 0;  /* []     */
                currentBlock.dot[0].y = 0;  /* [][][] */
                currentBlock.dot[1].x = 0;
                currentBlock.dot[1].y = 1;
                currentBlock.dot[2].x = 1;
                currentBlock.dot[2].y = 1;
                currentBlock.dot[3].x = 2;
                currentBlock.dot[3].y = 1;
                currentBlock.size = 2;
                break;
        case 5: currentBlock.dot[0].x = 2;  /*     [] */
                currentBlock.dot[0].y = 0;  /* [][][] */
                currentBlock.dot[1].x = 0;
                currentBlock.dot[1].y = 1;
                currentBlock.dot[2].x = 1;
                currentBlock.dot[2].y = 1;
                currentBlock.dot[3].x = 2;
                currentBlock.dot[3].y = 1;
                currentBlock.size = 2;
                break;
        case 6: currentBlock.dot[0].x = 0;  /* [][][][] */
                currentBlock.dot[0].y = 1;
                currentBlock.dot[1].x = 1;
                currentBlock.dot[1].y = 1;
                currentBlock.dot[2].x = 2;
                currentBlock.dot[2].y = 1;
                currentBlock.dot[3].x = 3;
                currentBlock.dot[3].y = 1;
                currentBlock.size = 4;
    }
   
    currentBlock.y = 0; /* A peça começa sempre no topo do campo */
   
    currentBlock.x = rand()%(LARGURA-currentBlock.size-1); /* A peça começa em uma posição aleatória em relação ao eixo x */
   
    put_block(currentBlock.x, currentBlock.y);
   
    srand(time(NULL));
    i = rand() % 4;
    while(i--)
        spin_block(); /* A peça é girada um número aleatório de vezes para aumentar as possibilidades de orientação que elas podem apresentar ao ser criadas */
}
 
int collision(int deslocX, int deslocY) {
    int i, j, origX, origY, dirX, dirY, newX, newY, check;
   
    origX = currentBlock.x;
    origY = currentBlock.y;
 
    for(i = 0 ; i < 4 ; i++) {
        newX = origX + currentBlock.dot[i].x + deslocX;
        newY = origY + currentBlock.dot[i].y + deslocY;
        if(newX >= 0 && newX < LARGURA && newY >= 0 && newY < ALTURA) { /* Testa em cada bloco na nova posição da peça se está dentro dos limites do campo */
            if(game.field[newX][newY] != VAZIO) { /* Testa se a posiçao é um espaço vazio */
                check = 0;
                for(j = 0 ; j < 4 ; j++) {
                    if((newX == origX + currentBlock.dot[j].x) && (newY == origY + currentBlock.dot[j].y)) /* Se não for vazio, testa se a posição está ocupada pela própria peça */
                        check = 1;
                }
                if(check == 0)
                    return 1; /* Se nenhuma das posições não vazias estiver ocupada pela própria peça então retorna que houve colisão */
            }
        }
        else
            return 1; /* Se a peça tiver fora dos limites também é retornado que houve colisão */
    }
 
    return 0;
}
 
int spin_block() {
    block new, aux = currentBlock;
    int i, j, newX, newY, check;
 
    for( i = 0 ; i < 4 ; i++) {
        aux.dot[i].x = currentBlock.dot[i].y;
        aux.dot[i].y = currentBlock.dot[i].x; /* Inversão da peça no sentido diagonal */
    }
    new = aux;
    for( i = 0 ; i < 4 ; i++)
        new.dot[i].x = (currentBlock.size-1)-aux.dot[i].x; /* Inversão da peça no sentido horizontal */
 
    for(i=0;i<4;i++) {
        newX = new.x + new.dot[i].x;
        newY = new.y + new.dot[i].y;
        if(newX >= 0 && newX < LARGURA && newY >= 0 && newY < ALTURA) {  /* Testa em cada bloco na nova posição da peça se está dentro dos limites do campo */
            if(game.field[newX][newY] != VAZIO) { /* Testa se a posiçao é um espaço vazio */
                check = 0;
                for(j = 0 ; j < 4 ; j++)
                    if((new.dot[i].x == currentBlock.dot[j].x) && (new.dot[i].y == currentBlock.dot[j].y)) /* Se não for vazio, testa se a posição está ocupada pela própria peça */
                        check = 1;
                if(check == 0)
                    return 1; /* Se nenhuma das posições não vazias estiver ocupada pela própria peça então a peça não é girada */
            }
        }
        else
            return 1; /* Se a peça tiver fora dos limites ela também não é girada */
    }
   
    for(i = 0; i < 4; i++)
        game.field[currentBlock.x + currentBlock.dot[i].x][currentBlock.y + currentBlock.dot[i].y] = VAZIO; /* Esvazia todas as posições na matriz que formam a peça na sua posição atual */
           
    currentBlock = new;
   
    for(i = 0; i < 4; i++)
        game.field[currentBlock.x + currentBlock.dot[i].x][currentBlock.y + currentBlock.dot[i].y] = currentBlock.color; /*  Preenche todas as posições na matriz que formam a peça após o giro */
 
    return 0;
}
 
int move_block(int opt){
    int newX = currentBlock.x, newY = currentBlock.y;
   
    if(opt == KEY_DOWN) { /* dobra a velocidade com que a peça cai */
        currentBlock.gravSpeed *= 2;
    }
    else if(opt == KEY_RIGHT){ /* move para direita */
        if(!collision(1, 0))
            newX++;
    }
    else if(opt == KEY_LEFT){ /* move para esquerda */
        if(!collision(-1, 0))
            newX--;
    }
    else if(opt == KEY_UP) /* gira a peça no sentido horário */
        spin_block();
    else
        return FALSO;
   
    if(newX != currentBlock.x || newY != currentBlock.y)
        put_block(newX, newY);
 
    return 0;
}
 
void apply_gravity() {
    currentBlock.gravTimer += currentBlock.gravSpeed; /* Incrementa o contador que controla o quanto que a peça deve descer baseada na sua velocidade atual */
    while(currentBlock.gravTimer >= GRAVITYMAX) { /* Se o contador passar do limite a peça se move uma posição para baixo */
        if(!collision(0, 1))
            put_block(currentBlock.x, currentBlock.y + 1);
        currentBlock.gravTimer -= GRAVITYMAX; /* Reseta o contador */
    }
}
 
int cut_this_line(int y){
 
    if(y < 5 || y > ALTURA){ /* Nao tem como o y ser menor que 5 ja que os bloco nao chegam até essa altura */
        return FALSO;
    }
 
    int x;
    for(x=0;x<LARGURA;x++)
        game.field[x][y] = 7; /* atribuiu a linha que sera cortada o valor 7, para que a proxima funcao "show_field" preencha-a de cor diferente indicando para o usuario que ela sera cortada */
    show_field();
    usleep(500000);
    for(;y>=1;y--)
        for(x=0;x<LARGURA;x++)
            game.field[x][y]=game.field[x][y-1]; /* Desce os blocos acima da linha cortada */
 
    return 0;
}
 
void any_complete_line(){
    int x, y, cnt;
    for(y = LIMITE; y < ALTURA; y++){
        cnt = 0;
        for(x = 0; x < LARGURA; x++)
            if(game.field[x][y] != VAZIO) cnt += 1;
        if(cnt == LARGURA) {    /* confere se o contador tem o tamanho da linha maxima */
            cut_this_line(y);
            game.points += 100;
        }
    }
}

