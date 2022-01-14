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
	char name[25];
	position_ pos;
	int pokeballs;
	int potions;
	pokedex_ pokedex;
	team_ team;
} player_;

typedef struct inventaire{

} inventaire_;

player initPlayer(char* name, map_*, int, int);
team_ initTeam();
void delTeam(team_);
int addPokeTeam(player* p, pokemon_ poke);
int getFirstAliveIndex(player p);
void movePlayer(player*, map_*, char);

#endif