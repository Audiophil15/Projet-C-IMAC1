#include <iostream>
#include <string>
#include "pokemon.h"

using namespace std;


pokemon initPokemon(string name, board* b, position pos, int pv, int atq, int def, type t, species e){
	pokemon p;
	p.name = name; // pokedex[e-1];
	p.pos.x = pos.x;
	p.pos.y = pos.y;
	p.pv = pv;
	p.atq = atq;
	p.def = def;
	p.t = t;

	setTab(e, b, p.pos.x, p.pos.y);

	return p;
}