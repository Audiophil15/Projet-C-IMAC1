#include <iostream>
#include <cstring>
#include "pokemon.h"

using namespace std;

char const * pokeNames[] = {"Pikachu", "Salameche", "Carapuce", "Bulbizarre"};
int pokePV[] = {50, 50, 50, 50};
int pokeAtq[] = {10, 10, 10, 10};
int pokeDef[] = {10, 10, 10, 10};
type pokeType[] = {ELEK, FEU, EAU, PLANTE};

pokemon_ initPokemon(species s){
	/* Inits a pokemon with its caracteristics according to its species */
	pokemon_ p;
	strcpy(p.name,pokeNames[s]);
	// p.pos.x = pos.x;
	// p.pos.y = pos.y;
	p.pvmax = pokePV[s];
	p.pv = p.pvmax;
	p.atq = pokeAtq[s];
	p.def = pokeDef[s];
	p.t = pokeType[s];

	return p;
}