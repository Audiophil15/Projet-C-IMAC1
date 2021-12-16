#include <iostream>
#include <ncurses.h>

#include "map.h"
#include "player.h"
#include "pokemon.h"

int main(){

	WINDOW *win, *menu;
	win = initscr();
	refresh();
	noecho();
	curs_set(0);

	srand(time(NULL));

	int mapxsize = 3*LINES/4;
	int mapysize = 3*COLS/4;
	map b = initMap(mapxsize, mapysize);
	
	player p = initPlayer("Philippe", &b, b.height/2, b.width/2);

	addPokemons(&b, &(p.pkdx), 10);

	refreshMap(win, b); //TEST

	char* msg = (char*)malloc(50); //TEST


	int c = 0;
	while (!pokedexFull(p.pkdx) && c!=127){
		c = getch();
		
		// 410 is the "screen resize" code
		if (c==410){
			clear();
		}

		// printf("-----\n");
		// for (int i = 0; i < p.pkdx.size; i++){
		// 	printf(": %d ", p.pkdx.existingSpecies[i]);
		// }
		// printf("\n");
		// for (int i = 0; i < p.pkdx.size; i++){
		// 	printf(": %d ", p.pkdx.knownSpecies[i]);
		// }
		// printf("\n");

		movePlayer(&p, &b, c);
		refreshMap(win, b);

		// for (int i = 0; i < p.pkdx.size; i++){
		// 	sprintf(msg, ": %d ", p.pkdx.knownSpecies[i]);
		// 	mvprintw(0, COLS/2-(p.pkdx.size/2)+i*4, msg);	
		// } //TEST
		
	}

	endwin();
}