#include <ncurses.h>

#include "ui.h"
#include "pokemon.h"

typedef struct {
	WINDOW* w;
	int wposx;
	int wposy;
	int wsx;
	int wsy;
} window_;

int menulist(WINDOW* menu, int posx, int posy, int sx, int sy, char const** choices, int menulength){
	// WINDOW* menu;
	// menu = derwin(win, sx, sy, posx-2, posy-4);
	wclear(menu);
	box(menu, ACS_VLINE, ACS_HLINE);

	int selection = 0;
	int c = 0;

	while(c != 127){ //while true
		for (int i = 0; i < menulength; i++){
			mvprintw(posx+i, posy, choices[i]);
		}
		attron(A_REVERSE);
		mvprintw(posx+selection, posy, choices[selection]);
		attroff(A_REVERSE);
		
		wrefresh(menu);
		// wrefresh(win);
				
		c = getch();
		switch (c){
			case 65 :	// up
				selection += -1+(!selection)*menulength;
				break;
			case 66 :	// down
				selection += 1;
				selection %= menulength;
				break;
			case 9 :
			case 10 :
			case 32 :
				return selection;

			case 127 :		//DEBUG
				return 127;
			default:
				break;
		}

	}
	return 127;
}

// void msgbox(WINDOW* msgbox, int posx, int posy, int sx, int sy, char const* msg){
void msgbox(WINDOW* msgbox, int posx, int posy, char const* msg){
	// WINDOW* msgbox;
	// msgbox = derwin(win, sx, sy, posx-2, posy-4);
	wclear(msgbox);
	box(msgbox, ACS_VLINE, ACS_HLINE);

	mvprintw(posx, posy, msg);
	wrefresh(msgbox);
}

void pkmnInfoDisplay(int posx, int posy, pokemon_ poke){
	float hbar;
	float hbarmax = 19;
	char pv[21] = "                    ";
	hbar = (int)((float)(poke.pv)/poke.pvmax*hbarmax);
	for (int i = 0; i < hbar; i++){
		pv[i] = '=';
	}
	mvprintw(posx, posy, "%s", poke.name);
	mvprintw(posx+1, posy, "PV : %2d/%2d", poke.pv, poke.pvmax);
	mvprintw(posx+2, posy, "   : %s", pv);

	// mvprintw(posx+2, posy, "ATQ : %2d / DEF : %2d", poke.atq, poke.def);
}