#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "map.h"
#include "pokemon.h"

using namespace std;

#define JOUEUR -1

typedef struct player{
	string name;
	position pos;
	int pokeballs;
	pokedex pkdx;
} player;

player initPlayer(string name, map*, int, int);
void movePlayer(player*, map*, char);

#endif