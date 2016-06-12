// RESOLVE 5
#include "estruturas.h"

void sortRank(){
	int cnt;
	do{
		cnt = 0;
		int i;
		for(i = 0; i < 5; i++)
			if(ranked[i].points < ranked[i+1].points || (ranked[i].points == ranked[i+1].points && ranked[i].time > ranked[i+1].time) ){
				player aux;
				aux = ranked[i];
				ranked[i] = ranked[i+1];
				ranked[i+1] = aux;
				cnt++;
			}	
	}while(cnt);
}

void newRankFile(){
	
	FILE *arq = fopen("ranking.txt", "w+");

	if(arq == NULL){
		printw("Falha ao criar arquivo\n");
		return;
	}

	int i;

	for(i = 0; i < 5; i++){
		fprintf(arq , "%s\n", "ola");
		fprintf(arq , "%d\n", ranked[i].points);
		fprintf(arq , "%lf\n", ranked[i].time);
	}

}

bool isItRanked(){
	FILE *Rank = fopen("ranking.txt", "r"); 	// r é para leitura

	if(Rank == NULL){
		Rank = fopen("ranking.txt", "w");		//cria arquivo
		int i;
		for(i = 0; i < 6; i++){
			if(i == 0)		strcpy(ranked[i].name, "QUEM");
			else if(i == 1)	strcpy(ranked[i].name, "SERA");
			else if(i == 2)	strcpy(ranked[i].name,"O   ");
			else if(i == 3)	strcpy(ranked[i].name,"PRIMEIRO");
			else if(i == 4)	strcpy(ranked[i].name,"MITO?");
			else 			strcpy(ranked[i].name, "hehehehehe");
			ranked[i].points = 0;
			ranked[i].time = 0;
		}
		newRankFile();
	}
	
	int i;

	for(i = 0; i < 5; i++){
		
		fscanf(Rank, "%[^\n] ", ranked[i].name);
		
		fscanf(Rank, "%d ", &ranked[i].points);

		fscanf(Rank, "%lf ", &ranked[i].time);

	}

	strcpy(ranked[5].name,currentPlayer.name);
	ranked[5].points = currentPlayer.points;
	ranked[5].time = currentPlayer.time;
	sortRank();
	if( strcmp(ranked[5].name,currentPlayer.name) == 0    &&
				ranked[5].points == currentPlayer.points &&
				ranked[5].time == currentPlayer.time ) // se o ultimo player continuar la em baixo
		return false;
	return true;
}

void show_rank(){
	clear();
	printw("Ranking:\n");
	int i;
	for(i = 0; i < 5; i++)	printw("%d. %10s - %10d - %.0lf\n", i+1, ranked[i].name, ranked[i].points, ranked[i].time);
	printw("\n\n Press [enter] to leave.");
	refresh();
	while(getch() != '\n'); // loop até pegar um [enter]
}

void rank(){
	char a;

	do{
		clear();
		printw("Diga vos seu nome!\nConsigo ler um nome de até 10 caracteres.\n >");
		scanf("%4s", currentPlayer.name);
		refresh();
		printw("Seu nome é %s?\n", currentPlayer.name);
		printw("Aperte [Y/y] para confirmar.\n");
		a = getch();
		refresh();
	}while(a != 'Y' && a != 'y');
	newRankFile(); // modifica o rank atual para o novo
	//}
	if(isItRanked()){ // pontuação for maior que a do ultimo rankeado no txt
		show_rank();
	}
	else {
		clear();
		printw("Me desculpe %s, mas sua pontuação não foi alta o suficiente :(", currentPlayer.name);
		refresh();
	}
}
