#ifndef MENU_H
#define MENU_H

#include <ncurses.h>
#include "pokemon.h"

int menulist(WINDOW* win, int posx, int posy, int sx, int sy, char const** choices, int menulength);
// void msgbox(WINDOW* win, int posx, int posy, int sx, int sy, char const* msg);
void msgbox(WINDOW* win, int posx, int posy, char const* msg);
void pkmnInfoDisplay(int posx, int posy, pokemon_ poke);

#endif