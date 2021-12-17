#include <iostream>
#include <ncurses.h>

#include "map.h"
#include "player.h"
#include "pokemon.h"

using namespace std;

/*
The map game has the x axis downward, the y axis from left to right
	0 ---> y
	|
	v
	x

The map contains -1 for the player, 0 for an empty case, and integers from 1 to n for pokemons

*/

// Must to be updated when species enum is changed
char const * displayChar[] = {"#", " ", "P", "S", "C", "B"};

int getTab(map b, int x, int y){
	/* map getter of a case's content */
	return b.grid[x*b.width+y];
}

void setTab(int val, map* b, int x, int y){
	/* map setter of a case's content */
	b->grid[x*b->width+y] = val;
}

map initMap(int height, int width, int maxPokemons){
	/* Initialises the map with given dimensions and fills them with 0s */
	map b;
	b.height = height;
	b.width = width;
	b.grid = (int*)malloc(sizeof(int)*b.width*b.height);
	for (int i = 0; i < b.height; i++){
		for (int j = 0; j < b.width; j++){
			setTab(0, &b, i, j);
		}
	}
	b.pokemonList = (pokemon*)malloc(sizeof(pokemon)*maxPokemons);
	return b;
}

void refreshMap(WINDOW* win, map b){
	/* Refreshes the map display according to what's in the map's grid */

	// -1	0	1	2	...
	//  #	.	P	C	...

	// Contain the position x and y of the map box
	int bposx = (LINES-b.height+2)/2;
	int bposy = (COLS-b.width+2)/2;
	// Derivate window of the main window
	b.win = derwin(win, b.height+2, b.width+2, bposx, bposy);
	box(b.win, ACS_VLINE, ACS_HLINE);

	char const * c;
	// Adds on the screen the character according to the number read in the grid
	for (int i = 0; i < b.height; i++){
		for (int j = 0; j < b.width; j++){
			c = displayChar[getTab(b, i, j)+1];
			mvprintw(bposx+i+1, bposy+j+1, c);
		}
	}

	// Refreshes only the subwin, little savings are savings !
	wrefresh(b.win);
}

void addPokemons(map* m, pokedex* pkdx, int nbpkm){
	int x, y;
	species s;
	for (int i = 0; i < nbpkm; i++){
		do{
			x=rand()%m->height;
			y=rand()%m->width;
		} while (getTab(*m, x, y)!=0);
		s = (species)(rand()%4+1);

		// BUGS HERE
		m->pokemonList[i] = initPokemon(position{x, y}, s);
		putsPokemon(m, m->pokemonList[i]);
		appendPkdx(pkdx, s);
	}
}

void putsPlayer(map* m, player p){
	setTab(JOUEUR, m, p.pos.x, p.pos.y);
}

void putsPokemon(map* m, pokemon poke){
	setTab(poke.s, m, poke.pos.x, poke.pos.y);
}

void movePlayer(player* p, map* b, char direction){
	int xmv = 0;
	int ymv = 0;
	species s;
	int c;

	if (64 < direction && direction < 69){
		setTab(0, b, p->pos.x, p->pos.y);

		if (direction == 65 && p->pos.x > 0) {
			xmv = -1;
		} else if (direction == 66 && p->pos.x < b->height-1){
			xmv = 1;
		} else if (direction == 67 && p->pos.y < b->width-1){
			ymv = 1;
		} else if (direction == 68 && p->pos.y > 0){
			ymv = -1;
		}

		c = getTab(*b, p->pos.x+xmv, p->pos.y+ymv);
		if (c!=0) {
			s = (species)c;
			if (!isKnown(s, p->pkdx)){
				learn(s, &(p->pkdx));
			}
		}

		p->pos.x += xmv;
		p->pos.y += ymv;

		setTab(JOUEUR, b, p->pos.x, p->pos.y);
	}
}