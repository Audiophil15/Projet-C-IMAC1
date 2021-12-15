#include <iostream>
#include <ncurses.h>

#include "board.h"
#include "pokemon.h"

using namespace std;

/*
The board game has the x axis downward, the y axis from left to right
	0 ---> y
	|
	v
	x
*/

// Needs to be updated with the species enum
char const * displayChar[] = {"#", ".", "P", "S", "C", "B"};

int getTab(board b, int x, int y){
	return b.grid[x*b.width+y];
}

void setTab(int val, board* b, int x, int y){
	b->grid[x*b->width+y] = val;
}

board initBoard(int height, int width){
	board b;
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

void refreshBoard(WINDOW* win, board b){

	// -1	0	1	2	...
	//  #	.	P	C	...

	int bposx = (LINES-b.height+2)/2;
	int bposy = (COLS-b.width+2)/2;
	b.win = derwin(win, b.height+2, b.width+2, bposx, bposy);
	box(b.win, ACS_VLINE, ACS_HLINE);

	char const * c;
	for (int i = 0; i < b.height; i++){
		for (int j = 0; j < b.width; j++){
			if (getTab(b, i, j)==-1){
				c = "#";
			} else {
				c = displayChar[getTab(b, i, j)+1];
			}

			// sprintf(c, "%d", getTab(b, i, j)); //TEST
			mvprintw(bposx+i+1, bposy+j+1, c);
		}
	}

	wrefresh(b.win);
}