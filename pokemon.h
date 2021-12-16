#ifndef POKE_H
#define POKE_H

#include <string>
#include "map.h"

using namespace std;

typedef enum type {ELEK, FEU, EAU, PLANTE} type;
typedef enum species {PIKACHU=1, SALAMECHE, CARAPUCE, BULBIZARRE} species;
#define PKDXS 4

typedef struct pokemon{
	char const * name;
	position pos;
	int pv;
	int atq;
	int def;
	type t;
	species s;
} pokemon;

typedef struct pokedex{
	// Contains 1 for existing species, 0 otherwise
	int* existingSpecies;
	// Contains 1 for known species, 0 otherwise
	int* knownSpecies;
	int size;
} pokedex;




pokemon initPokemon(map* b, position pos, species e);
void initPokedex(pokedex*);
void appendPkdx(pokedex* pkdx, species s);
void addPokemons(map* m, pokedex* pkdx, int nbpkm);
int isKnown(species s, pokedex pdx);
void learn(species s, pokedex* pdx);

#endif