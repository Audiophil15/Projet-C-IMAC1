#ifndef POKE_H
#define POKE_H

#include <string>
#include "board.h"
#include "player.h"

using namespace std;

typedef enum type {ELEK, FEU, EAU, PLANTE} type;
typedef enum species {PIKACHU=1, SALAMECHE, CARAPUCE, BULBIZARRE} species;

// char const * pokedex[] = {"Pikachu", "Salameche", "Carapuce", "Bulbizarre"};
// int pokedexSize = 4;


typedef struct pokemon{
	string name;
	position pos;
	int pv;
	int atq;
	int def;
	type t;
	species s;
} pokemon;


pokemon initPokemon(string name, board*, position, int, int, int, type, species);


#endif