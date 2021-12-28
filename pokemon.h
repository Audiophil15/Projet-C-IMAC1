#ifndef POKE_H
#define POKE_H

#include <string>
#include "map.h"

using namespace std;

typedef enum type {ELEK, FEU, EAU, PLANTE} type;
typedef enum species {PIKACHU=1, SALAMECHE, CARAPUCE, BULBIZARRE} species;
#define PKDXS 4

typedef struct {
	char name[50];
	position_ pos;
	int pvmax;
	int pv;
	int atq;
	int def;
	type t;
	species s;
} pokemon_;

typedef struct {
	// Contains 1 for existing species, 0 otherwise
	int* existingSpecies;
	// Contains 1 for known species, 0 otherwise
	int* knownSpecies;
	int size;
} pokedex_;


typedef struct {
	pokemon_* pokemons;
	int sizemax;
	int nbpkmn;
}team_;



pokemon_ initPokemon(species e);
pokedex_ initPokedex();
team_ initTeam();
void appendPkdx(pokedex_* pkdx, species s);
int pokedexFull(pokedex_ pkdx);
int isKnown(species s, pokedex_ pdx);
void learn(species s, pokedex_* pdx);

#endif