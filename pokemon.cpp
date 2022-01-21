#include <iostream>
#include <cstring>
#include "pokemon.h"

using namespace std;

char const * pokeNames[] = {"Pikachu", "Salameche", "Carapuce", "Bulbizarre"};
int pokePV[] = {50, 50, 50, 50};
int pokeAtq[] = {10, 10, 10, 10};
int pokeDef[] = {5, 5, 5, 5};
type pokeType[] = {ELEK, FEU, EAU, PLANTE};

int coeff[] =  {1, 1, 2, 1,
				1, 1, 0, 2,
				1, 2, 1, 1,
				1, 0, 2, 1};

pokemon_ initPokemon(species s){
	/* Inits a pokemon with its caracteristics according to its species */
	pokemon_ p;
	p.name = pokeNames[s];
	p.pvmax = pokePV[s];
	p.pv = p.pvmax;
	p.atq = pokeAtq[s];
	p.def = pokeDef[s];
	p.s = s;
	p.t = pokeType[s];

	return p;
}

char const * getPokeName(int index){
	return pokeNames[index];
}

int atkCoeff(pokemon_ atk, pokemon_ def){
	return coeff[4*(int)atk.t+(int)def.t];
}