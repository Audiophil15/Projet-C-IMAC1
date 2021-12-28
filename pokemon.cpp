#include <iostream>
#include <cstring>
#include "pokemon.h"

using namespace std;

char const * pokeNames[] = {"Pikachu", "Salameche", "Carapuce", "Bulbizarre"};
int pokePV[] = {50, 50, 50, 50};
int pokeAtq[] = {10, 10, 10, 10};
int pokeDef[] = {10, 10, 10, 10};
type pokeType[] = {ELEK, FEU, EAU, PLANTE};

pokemon_ initPokemon(species e){
	/* Inits a pokemon with its caracteristics according to its species */
	pokemon_ p;
	int propIndex = e-1;
	strcpy(p.name,pokeNames[propIndex]);
	// p.pos.x = pos.x;
	// p.pos.y = pos.y;
	p.pvmax = pokePV[propIndex];
	p.pv = p.pvmax;
	p.atq = pokeAtq[propIndex];
	p.def = pokeDef[propIndex];
	p.t = pokeType[propIndex];

	return p;
}

pokedex_ initPokedex(){
	/* Init the player's pokedex, with some calloc to have zeroed tables */
	pokedex_ pkdx;
	pkdx.size = PKDXS;
	pkdx.existingSpecies = (int*)calloc(pkdx.size, sizeof(int));
	pkdx.knownSpecies = (int*)calloc(pkdx.size, sizeof(int));
	for (int i = 0; i < pkdx.size; i++){
		pkdx.existingSpecies[i] = 1;
	}
	
	return pkdx;
}

team_ initTeam(){
	team_ t;
	t.pokemons = (pokemon_*)malloc(sizeof(pokemon_));
	t.sizemax = 1;
	t.nbpkmn = 0;
	return t;
}

void appendPkdx(pokedex_* pkdx, species s){
	if (pkdx->existingSpecies[s-1] == 0){
		pkdx->existingSpecies[s-1] = 1;
	}
}

int pokedexFull(pokedex_ pkdx){
	for (int i = 0; i < pkdx.size; i++){
		if (pkdx.knownSpecies[i] != pkdx.existingSpecies[i]){
			return 0;
		}
	}
	return 1;
}

int isKnown(species s, pokedex_ pdx){
	return pdx.knownSpecies[s-1]==1;
}

void learn(species s, pokedex_* pdx){
	pdx->knownSpecies[s-1]=1;
}