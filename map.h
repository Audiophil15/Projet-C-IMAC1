#ifndef MAP_H
#define MAP_H

#include <ncurses.h>

using namespace std;

typedef struct map{
	int* grid;
	int width;
	int height;
	WINDOW* win;
} map;

typedef struct position{
	int x;
	int y;
} position;

int getTab(map, int, int);
void setTab(int, map*, int, int);
map initMap(int, int);
void refreshMap(WINDOW*, map);

#endif