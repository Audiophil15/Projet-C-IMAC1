#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "inventory.h"
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
	char name[25];
	position_ pos;
	inventory_ bag;
	// int pokeballs;
	// int potions;
	pokedex_ pokedex;
	team_ team;
} player_;

player initPlayer(char* name, map_*, int, int);
team_ initTeam();
void delTeam(team_);
void delInventory(inventory_ invent);
int addPokeTeam(player* p, pokemon_ poke);
int getFirstAliveIndex(player p);
int movePlayer(player*, map_*, char);

#endif