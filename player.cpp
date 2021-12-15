#include <iostream>
#include <string>
#include "player.h"
#include "board.h"

using namespace std;

player initPlayer(string name, board* b, int x, int y){
	player p;
	p.name = (char*)malloc(20);
	// strcpy(p.name, name); //TEST
	p.pos.x = x;
	p.pos.y = y;

	setTab(JOUEUR, b, p.pos.x, p.pos.y);

	return p;
}

void movePlayer(player* p, board* b, char direction){
	int xmv = 0;
	int ymv = 0;

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

		if (getTab(*b, p->pos.x+xmv, p->pos.y+ymv)==0) {
			
		}

		p->pos.x += xmv;
		p->pos.y += ymv;

		setTab(JOUEUR, b, p->pos.x, p->pos.y);
	}
}