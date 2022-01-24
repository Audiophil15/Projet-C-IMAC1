#include <iostream>
#include <cstring>
#include "pokemon.h"

using namespace std;

char const * pokeNames[] = {"Pikachu", "Salameche", "Carapuce", "Bulbizarre", "Racaillou", "Grolem", "Ronflex", "Mimitoss", "Raicou", "Entei", "Suicune"};
int pokePV[] = {75, 56, 62, 80, 85, 92, 112, 50, 85, 81, 83};
int pokeAtq[] = {17, 17, 15, 16, 14, 16, 14, 11, 17, 19, 16};
int pokeDef[] = {11, 8, 11, 10, 13, 16, 13, 8, 13, 12, 14};
int legendary[] = {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1};
type pokeType[] = {ELEK, FEU, EAU, PLANTE, ROCHE, ROCHE, NORMAL, PLANTE, ELEK, FEU, EAU};

//				NORMAL, ELEK, FEU, EAU, PLANTE, ROCHE
int coeff[] =  {1, 1, 1, 1, 1, 1,
				1, 1, 1, 2, 1, 0,
				1, 1, 1, 0, 2, 0,
				1, 0, 2, 1, 1, 2,
				1, 1, 0, 2, 1, 2,
				1, 2, 2, 0, 0, 1};

// int coeff[] =  {1, 1, 2, 1,
// 				1, 1, 0, 2,
// 				0, 2, 1, 1,
// 				1, 0, 2, 1};

pokemon_ initPokemon(species s){
	/* Inits a pokemon with its caracteristics according to its species */
	pokemon_ p;
	p.name = pokeNames[s];
	p.pvmax = pokePV[s];
	p.pv = p.pvmax;
	p.atq = pokeAtq[s];
	p.def = pokeDef[s];
	p.legend = legendary[s];
	p.t = pokeType[s];
	p.s = s;

	return p;
}

char const * getPokeName(int index){
	return pokeNames[index];
}

int atkCoeff(pokemon_ atk, pokemon_ def){
	/* Returns the coeff used to calculate damages, based on pokemon types */
	return coeff[NBTYPES*(int)atk.t+(int)def.t];
}

int isdead(pokemon_ poke){
	/* Cmon, do smthing... */
	return poke.pv==0;
}