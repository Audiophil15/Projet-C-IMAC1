#ifndef PKDX_H
#define PKDX_H

#include "pokemon.h"

#define PKDXS 4

typedef struct {
	// Contains 1 for known species, 0 otherwise
	int* knownSpecies;
	int size;
} pokedex_;

pokedex_ initPokedex();
void appendPkdx(pokedex_* pkdx, species s);
int pokedexFull(pokedex_ pkdx);
int isKnown(species s, pokedex_ pdx);
void learn(species s, pokedex_* pdx);

#endif