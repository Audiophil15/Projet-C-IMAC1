#include <iostream>
#include <ncurses.h>

#include "map.h"
#include "player.h"
#include "pokemon.h"

int main(){

	// Creates pointers to place windows of ncurses in
	WINDOW *win, *menu;

	// inits the screen with the whole term as a window
	win = initscr();

	// First refresh allows curs_set() to work
	refresh();
	noecho();
	curs_set(0);

	// Rand seed init
	srand(time(NULL));

	// Init of the sides of the map, then the map itself is initialised and zeroed
	int mapxsize = 3*LINES/4;
	int mapysize = 3*COLS/4;

	int nbPokes = 15;

	map b = initMap(mapxsize, mapysize, nbPokes);
	
	// Creates a player and puts it in the map
	player p = initPlayer("Philippe", b.height/2, b.width/2);

	// Adds player and pokemons to the map, updates the pokedex when a new species is created
	putsPlayer(&b, p);
	addPokemons(&b, &(p.pkdx), nbPokes);

	// First refresh of the map to see it when starting
	refreshMap(win, b);

	// Will receive the code returned by getch();
	int c = 0;

	// Beginning of the game, stop when all species have been encountered, or when Backspace is hit
	while (!pokedexFull(p.pkdx) && c!=127){
		c = getch();
		
		// 410 is the "screen resize" code
		if (c==410){
			clear();
		}

		// Move the player if c is the code of an arrow
		movePlayer(&p, &b, c);

		refreshMap(win, b);
		
	}

	// Closes ncurses
	endwin();
}