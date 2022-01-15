#include <ncurses.h>

#include "ui.h"
#include "pokemon.h"
#include "player.h"

int menulist(window_ wmenu, char ** choices, int menulength, int wcl){
	if(wcl){
		wclear(wmenu.w);
		box(wmenu.w, ACS_VLINE, ACS_HLINE);
	}

	int selection = 0;
	int c = 0;

	while(c != 127){ //while true
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

			case 127 :		//DEBUG
				return 127;
			default:
				break;
		}

	}
	return 127;
}

int pokemonlist(window_ wmenu, player_ p){
	char* pokenames[p.team.nbpkmn];
	char pv[6];
	pokemon_ poke;
	wempty(wmenu);
	for (int i = 0; i < p.team.nbpkmn; i++){
		poke = p.team.pokemons[i];
		pokenames[i] = poke.name;
		sprintf(pv, "%d/%d", poke.pv, poke.pvmax);
		msgbox(wmenu, pv, i, 22, 0);
	}
	
	int choix=0;
	do{
		choix = menulist(wmenu, pokenames, p.team.nbpkmn, 0);
	} while (p.team.pokemons[choix].pv==0);

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