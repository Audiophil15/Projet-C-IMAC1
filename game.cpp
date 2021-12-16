#include <iostream>
#include <ncurses.h>

#include "map.h"
#include "player.h"
#include "pokemon.h"

int main(){

	WINDOW *win, *menu;
	win = initscr();

	srand(time(NULL));

	int mapxsize = 15;
	int mapysize = 30;
	map b = initMap(mapxsize, mapysize);
	
	player p = initPlayer("Philippe", &b, b.height/2, b.width/2);

	addPokemons(&b, &(p.pkdx), 15);

	refreshMap(win, b);

	char* msg = (char*)malloc(50); //TEST


	int c = 0;
	while (c!=127){
		c = getch();
		
		// 410 is the "screen resize" code
		if (c==410){
			clear();
		}

		for (int i = 0; i < p.pkdx.size; i++){
			sprintf(msg, ": %d\n: %d\n", p.pkdx.existingSpecies[i], p.pkdx.knownSpecies[i]);
			mvprintw(0, COLS/2-(p.pkdx.size/2)+i*4, msg);	
		}
		

		movePlayer(&p, &b, c);
		refreshMap(win, b);

	}

	endwin();
}