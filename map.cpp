#include <iostream>
#include <ncurses.h>

#include "map.h"
#include "pokemon.h"

using namespace std;

/*
The map game has the x axis downward, the y axis from left to right
	0 ---> y
	|
	v
	x
*/

// Needs to be updated with the species enum
char const * displayChar[] = {"#", ".", "P", "S", "C", "B"};

int getTab(map b, int x, int y){
	return b.grid[x*b.width+y];
}

void setTab(int val, map* b, int x, int y){
	b->grid[x*b->width+y] = val;
}

map initMap(int height, int width){
	map b;
	b.height = height;
	b.width = width;
	b.grid = (int*)malloc(sizeof(int)*b.width*b.height);
	for (int i = 0; i < b.height; i++){
		for (int j = 0; j < b.width; j++){
			setTab(0, &b, i, j);
		}
	}
	return b;
}

void refreshMap(WINDOW* win, map b){

	// -1	0	1	2	...
	//  #	.	P	C	...

	int bposx = (LINES-b.height+2)/2;
	int bposy = (COLS-b.width+2)/2;
	b.win = derwin(win, b.height+2, b.width+2, bposx, bposy);
	box(b.win, ACS_VLINE, ACS_HLINE);

	char const * c;
	for (int i = 0; i < b.height; i++){
		for (int j = 0; j < b.width; j++){
			c = displayChar[getTab(b, i, j)+1];
			mvprintw(bposx+i+1, bposy+j+1, c);
		}
	}

	wrefresh(b.win);
}