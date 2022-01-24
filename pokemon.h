#ifndef POKE_H
#define POKE_H

#include <string>
#include "position.h"

using namespace std;

#define NBTYPES 6
typedef enum type {NORMAL, ELEK, FEU, EAU, PLANTE, ROCHE} type;
typedef enum species {PIKACHU, SALAMECHE, CARAPUCE, BULBIZARRE, RACAILLOU, GROLEM, RONFLEX, MIMITOSS, RAICOU, ENTEI, SUICUNE} species;

typedef struct {
	char const * name;
	int pvmax;
	int pv;
	int atq;
	int def;
	int legend;
	type t;
	species s;
} pokemon_;

pokemon_ initPokemon(species e);
char const * getPokeName(int index);
int atkCoeff(pokemon_ atk, pokemon_ def);

#endif