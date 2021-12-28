#ifndef FIGHT_H
#define FIGHT_H

#include <ncurses.h>
#include "pokemon.h"
#include "player.h"

void fight(WINDOW* win, player_* p);
int menu(WINDOW* win, int posx, int posy, int sx, int sy, char ** actions, int menulength);

#endif