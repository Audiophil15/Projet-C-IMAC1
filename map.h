#ifndef MAP_H
#define MAP_H

#include <ncurses.h>
#include "player.h"
#include "pokemon.h"

using namespace std;

typedef struct map{
	int* grid;
	int width;
	int height;
	int* pkmlist;
	int nbpkmn;
	WINDOW* win;
} map;

int getTab(map, int, int);
void setTab(int, map*, int, int);
map initMap(int, int, int);
void refreshMap(WINDOW*, map);
void addPokemons(map* m, pokedex* pkdx, int nbpkm);
void putsPlayer(map* m, player p);
void putsPokemon(map* m, pokemon poke);
void movePlayer(player*, map*, char);
void movePokemons(map* m);

#endif