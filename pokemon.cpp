#include <iostream>
#include <string>
#include "pokemon.h"

using namespace std;

char const * pokeNames[] = {"Pikachu", "Salameche", "Carapuce", "Bulbizarre"};
int pokePV[] = {50, 50, 50, 50};
int pokeAtq[] = {10, 10, 10, 10};
int pokeDef[] = {10, 10, 10, 10};
type pokeType[] = {ELEK, FEU, EAU, PLANTE};

pokemon initPokemon(map* b, position pos, species e){
	/* Inits a pokemon with its caracteristics according to its species */
	pokemon p;
	int propIndex = e-1;
	p.name = pokeNames[propIndex];
	p.pos.x = pos.x;
	p.pos.y = pos.y;
	p.pv = pokePV[propIndex];
	p.atq = pokeAtq[propIndex];
	p.def = pokeDef[propIndex];
	p.t = pokeType[propIndex];

	setTab(e, b, p.pos.x, p.pos.y);

	return p;
}

pokedex initPokedex(){
	/* Init the player's pokedex, with some calloc to have zeroed tables */
	pokedex pkdx;
	pkdx.size = PKDXS;
	pkdx.existingSpecies = (int*)calloc(pkdx.size, sizeof(int));
	pkdx.knownSpecies = (int*)calloc(pkdx.size, sizeof(int));
	return pkdx;
}

void appendPkdx(pokedex* pkdx, species s){
	if (pkdx->existingSpecies[s-1] == 0){
		pkdx->existingSpecies[s-1] = 1;
		// pkdx->size += 1;
	}
}

void addPokemons(map* m, pokedex* pkdx, int nbpkm){
	int x, y;
	species s;
	for (int i = 0; i < nbpkm; i++){
		do{
			x=rand()%m->height;
			y=rand()%m->width;
		} while (getTab(*m, x, y)!=0);
		s = (species)(rand()%4+1);
		setTab(s, m, x, y);
		appendPkdx(pkdx, s);
	}
}

int pokedexFull(pokedex pkdx){
	for (int i = 0; i < pkdx.size; i++){
		if (pkdx.knownSpecies[i] != pkdx.existingSpecies[i]){
			return 0;
		}
	}
	return 1;
}

int isKnown(species s, pokedex pdx){
	return pdx.knownSpecies[s-1]==1;
}

void learn(species s, pokedex* pdx){
	pdx->knownSpecies[s-1]=1;
}