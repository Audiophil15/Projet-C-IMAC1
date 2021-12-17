#ifndef PLAYER_H
#define PLAYER_H

#include "position.h"
#include "pokemon.h"

using namespace std;

#define JOUEUR -1

typedef struct player{
	char const * name;
	position pos;
	int pokeballs;
	pokedex pkdx;
} player;

player initPlayer(char const* name,  int, int);

#endif