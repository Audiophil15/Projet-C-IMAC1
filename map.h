#ifndef MAP_H
#define MAP_H

#include <ncurses.h>

using namespace std;

typedef struct {
	int* grid;
	int width;
	int height;
	WINDOW* win;
} map_;

int getTab(map_, int, int);
void setTab(int, map_*, int, int);
map_ initMap(int, int);
void delMap(map_);
void refreshMap(WINDOW*, map_);

#endif