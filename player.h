#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "position.h"
#include "pokedex.h"
#include "map.h"

using namespace std;

#define JOUEUR -1

typedef struct {
	pokemon_* pokemons;
	int sizemax;
	int nbpkmn;
}team_;

typedef struct player{
	string name;
	position_ pos;
	int pokeballs;
	pokedex_ pokedex;
	team_ team;
} player_;

player initPlayer(string name, map_*, int, int);
team_ initTeam();
int addPokeTeam(player* p, pokemon_ poke);
void movePlayer(player*, map_*, char);

#endif