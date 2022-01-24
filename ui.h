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

window_ initWindow(int sx, int sy, int posx, int posy);
// int menulist(window_ wmenu, char const ** choices, int menulength, int menusize=0, int offsetx=0, int offsety=0, int wcl=1);
int menulist(window_ wmenu, char const ** choices, int menulength, int offsetx=0, int offsety=0, int wcl=1);
int getReturn();
void wempty(window_ w, int boxed=1);
int pokedex(window_ wpokedex, player_ p);
// int pokedexList(window_ wpokedex, player_ p);
int pokemonList(window_ wlist, player_ p);
int bagList(window_ wbag, player_ p);
int pokemonMenu(window_ wmenu, player_ p);
int bagMenu(window_ wbag, player_ p);
int pauseMenu(window_ wpause, player_ p);
void msgbox(window_ wmsgbox, char const* msg, int offx = 0, int offy = 0, int wcl = 1);
void pkmnInfoDisplay(window_ wfight, int posx, int posy, pokemon_ poke);
void greetScreen(window_ w, char* name);
void splashscreen(window_ win);
void button(window_ w, char* text, int posx, int posy, int sx=1, int sy=0);

#endif