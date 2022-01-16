#include <ncurses.h>

#include "ui.h"
#include "pokemon.h"
#include "player.h"

int menulist(window_ wmenu, char const ** choices, int menulength, int wcl){
	if(wcl){
		wclear(wmenu.w);
		box(wmenu.w, ACS_VLINE, ACS_HLINE);
	}

	int selection = 0;
	int c = 0;

	while(c != 120){ //while true
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
	char const * pokenames[6];
	char pv[6];
	int choix=0;
	pokemon_ poke;
	
	char msg[50]; //DEBUG

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
	wclear(w.w);
	box(w.w, ACS_VLINE, ACS_HLINE);
}

void msgbox(window_ wmsgbox, char const* msg, int offsetx, int offsety, int wcl){
	if (wcl){
		wempty(wmsgbox);
	}
	

	mvprintw(wmsgbox.posx+offsetx, wmsgbox.posy+offsety, msg);
	wrefresh(wmsgbox.w);
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
}