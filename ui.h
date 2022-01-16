#ifndef MENU_H
#define MENU_H

#include <ncurses.h>
#include "pokemon.h"
#include "player.h"

typedef struct {
	WINDOW* w;
	int posx;
	int posy;
	int sx;
	int sy;
} window_;

void wempty(window_ w);
int menulist(window_ wmenu, char const ** choices, int menulength, int wcl=1);
int pokemonlist(window_ wmenu, player_ p);
void msgbox(window_ wmsgbox, char const* msg, int offx = 0, int offy = 0, int wcl = 1);
void pkmnInfoDisplay(int posx, int posy, pokemon_ poke);

#endif