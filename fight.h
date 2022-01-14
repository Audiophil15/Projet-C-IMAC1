#ifndef FIGHT_H
#define FIGHT_H

#include <ncurses.h>
#include "pokemon.h"

void fight(WINDOW* win, player_* p, pokemon_* enemy);
void attack(pokemon_* attacker, pokemon_* defender);
int isdead(pokemon_ poke);

#endif