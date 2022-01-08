#ifndef POKE_H
#define POKE_H

#include <string>
#include "position.h"

using namespace std;

typedef enum type {ELEK, FEU, EAU, PLANTE} type;
typedef enum species {PIKACHU, SALAMECHE, CARAPUCE, BULBIZARRE} species;

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

pokemon_ initPokemon(species e);

#endif