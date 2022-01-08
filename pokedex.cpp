#include <iostream>
#include "pokedex.h"
#include "pokemon.h"

pokedex_ initPokedex(){
	/* Init the player's pokedex, with some calloc to have zeroed tables */
	pokedex_ pkdx;
	pkdx.size = PKDXS;
	pkdx.knownSpecies = (int*)calloc(pkdx.size, sizeof(int));
	
	return pkdx;
}

void appendPkdx(pokedex_* pkdx, species s){
	if (pkdx->knownSpecies[s-1] == 0){
		pkdx->knownSpecies[s-1] = 1;
	}
}

int pokedexFull(pokedex_ pkdx){
	for (int i = 0; i < pkdx.size; i++){
		if (pkdx.knownSpecies[i] == 0){
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