#include <ncurses.h>

#include "ui.h"
#include "pokemon.h"
#include "player.h"

window_ initWindow(int sx, int sy, int posx, int posy){
	/* Inits a window_ with the corresponding sizes and position */
	window_ win;
	win.sx = sx;
	win.sy = sy;
	win.posx = posx;
	win.posy = posy;
	return win;
}

int menulist(window_ wmenu, char const ** choices, int menulength, int wcl){
	/* Creates a menu based on the choices and menulength given */

	// Clears the window if needed (default yes)
	if(wcl){
		wclear(wmenu.w);
		box(wmenu.w, ACS_VLINE, ACS_HLINE);
	}

	int selection = 0;
	int c = 0;

	while(c != 120){ //while true
		// prints all the choices, then prints the selected choice with reverse attribute
		for (int i = 0; i < menulength; i++){
			mvprintw(wmenu.posx+i, wmenu.posy, choices[i]);
		}
		attron(A_REVERSE);
		mvprintw(wmenu.posx+selection, wmenu.posy, choices[selection]);
		attroff(A_REVERSE);
		
		wrefresh(wmenu.w);
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

			// Case to be ignored, if returns -1 the value should not be used as a choice, i.e. it allows to get out of the menu
			case 127 : // Backspace
			case 68 : // Left Arrow
				return -1;

			case 120 :		//DEBUG
				return 120;
			default:
				break;
		}

	}
	return 120;
}

int pokemonlist(window_ wmenu, player_ p){
	/* Creates a menu with pokemons */
	char const * pokenames[6];
	char pv[6];
	int choix=0;
	pokemon_ poke;

	wempty(wmenu);
	for (int i = 0; i < p.team.nbpkmn; i++){
		poke = p.team.pokemons[i];
		pokenames[i] = poke.name;
		sprintf(pv, "%d/%d", poke.pv, poke.pvmax);
		msgbox(wmenu, pv, i, 22, 0);
	}

	do{
		choix = menulist(wmenu, pokenames, p.team.nbpkmn, 0);
	} while (choix!=-1 && p.team.pokemons[choix].pv==0); // If the user doesn't quit the menu, checks if the pokemon has non-zero life

	return choix;
}

void wempty(window_ w){
	/* Clears a window */
	wclear(w.w);
	box(w.w, ACS_VLINE, ACS_HLINE);
}

void msgbox(window_ wmsgbox, char const* msg, int offsetx, int offsety, int wcl){
	/* Prints a message in a box, clears it if needed */
	if (wcl){
		wempty(wmsgbox);
	}
	mvprintw(wmsgbox.posx+offsetx, wmsgbox.posy+offsety, msg);
	wrefresh(wmsgbox.w);
}

void pkmnInfoDisplay(int posx, int posy, pokemon_ poke){
	/* Shows a pokemon info at given position. Shows name and pv stats with a healthbar */
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
}