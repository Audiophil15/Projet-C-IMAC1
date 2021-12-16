#include <iostream>
#include <string>
#include "player.h"
#include "pokemon.h"
#include "map.h"

using namespace std;

player initPlayer(string name, map* b, int x, int y){
	player p;
	p.name = name;
	p.pos.x = x;
	p.pos.y = y;
	p.pokeballs = 15;

	initPokedex(&(p.pkdx));

	setTab(JOUEUR, b, p.pos.x, p.pos.y);

	return p;
}

void movePlayer(player* p, map* b, char direction){
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

		c = getTab(*b, p->pos.x+xmv, p->pos.y+ymv);
		if (c!=0) {
			s = (species)c;
			if (!isKnown(s, p->pkdx)){
				learn(s, &(p->pkdx));
			}
		}

		p->pos.x += xmv;
		p->pos.y += ymv;

		setTab(JOUEUR, b, p->pos.x, p->pos.y);
	}
}