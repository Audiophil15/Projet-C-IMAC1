#include <iostream>
#include <string>
#include "player.h"
#include "pokemon.h"
#include "map.h"

using namespace std;

player initPlayer(char const * name, int x, int y){
	player p;
	p.name = name;
	p.pos.x = x;
	p.pos.y = y;
	p.pokeballs = 15;
	p.pkdx = initPokedex();
	return p;
}

