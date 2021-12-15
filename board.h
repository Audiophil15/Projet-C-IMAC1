#ifndef BOARD_H
#define BOARD_H

#include <ncurses.h>

using namespace std;

typedef struct board{
	int* grid;
	int width;
	int height;
	WINDOW* win;
} board;

int getTab(board, int, int);
void setTab(int, board*, int, int);
board initBoard(int, int);
void refreshBoard(WINDOW*, board);

#endif