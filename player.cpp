#include <iostream>
#include <string>
#include "player.h"
#include "pokemon.h"
#include "map.h"

using namespace std;

player initPlayer(string name, map_* b, int x, int y){
	player p;
	p.name = name;
	p.pos.x = x;
	p.pos.y = y;
	p.pokeballs = 15;

	p.pokedex = initPokedex();
	p.team = initTeam();

	setTab(JOUEUR, b, p.pos.x, p.pos.y);

	return p;
}

int addPokeTeam(player* p, pokemon_ poke){
	if (p->team.size == p->team.nbpkmn){
		p->team.size += 1;
		p->team.pokemons = (pokemon_*)realloc(p->team.pokemons, p->team.size*sizeof(pokemon_));
	}
	if (!p->team.pokemons){
		return -1;
	}
	p->team.pokemons[p->team.nbpkmn] = poke;
	p->team.nbpkmn += 1;
	return 0;
}

void movePlayer(player* p, map_* b, char direction){
	int xmv = 0;
	int ymv = 0;
	species s;
	int c;

	if (64 < direction && direction < 69){
		setTab(0, b, p->pos.x, p->pos.y);

		if (direction == 65 && p->pos.x > 0) {
			xmv = -1;
		} else if (direction == 66 && p->pos.x < b->height-1){
			xmv = 1;
		} else if (direction == 67 && p->pos.y < b->width-1){
			ymv = 1;
		} else if (direction == 68 && p->pos.y > 0){
			ymv = -1;
		}

		p->pos.x += xmv;
		p->pos.y += ymv;

		setTab(JOUEUR, b, p->pos.x, p->pos.y);
	}
}