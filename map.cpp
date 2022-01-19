#include <iostream>
#include <ncurses.h>

#include "map.h"

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
char const * displayChar[] = {"#", " ", "X"};

int getTab(map_ b, int x, int y){
	/* map getter of a case's content */
	return b.grid[x*b.width+y];
}

void setTab(int val, map_* b, int x, int y){
	/* map setter of a case's content */
	b->grid[x*b->width+y] = val;
}

map_ initMap(int height, int width){
	/* Initialises the map with given dimensions and fills them with 0s */
	map_ b;
	b.height = height;
	b.width = width;
	b.grid = (int*)malloc(sizeof(int)*b.width*b.height);
	for (int i = 0; i < b.height; i++){
		for (int j = 0; j < b.width; j++){
			if (i>2 && i>6 && j>4 && j<9){
				setTab(1, &b, i, j);
			} else {
				setTab(0, &b, i, j);
			}
		}
	}
	return b;
}

void delMap(map_ map){
	free(map.grid);
}

void refreshMap(WINDOW* win, map_ b){
	// TODO : Map case is normal or grass, 0 normal or 1 grass
	//		  Todo after the game works

	/* Refreshes the map display according to what's in the map's grid */

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