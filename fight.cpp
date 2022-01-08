#include <iostream>
#include <ncurses.h>
#include <unistd.h>

#include "pokemon.h"
// #include "map.h"
#include "player.h"
#include "fight.h"

#define MENULEN 3
char const * actions[] = {"Attaque", "Capture", "Fuite"};


void fight(WINDOW* win, player_* p, pokemon_ poke){
	clear();

	WINDOW *fight;
	
	int menulen;
	int teamindex = 0;
	
	int end = 0;

	while (end != 127){
		char ally[35];

		int fightWinSizex = min(COLS, LINES)/2;
		int fightWinSizey = fightWinSizex*3;
		int fightwinposx = (LINES-fightWinSizex)/2;
		int fightwinposy = (COLS-fightWinSizey)/2;

		int enemyposx = fightwinposx+1;
		int enemyposy = fightwinposy+10;
		int allyposx = fightwinposx+fightWinSizex-1-fightWinSizex/2;
		int allyposy = fightwinposy+fightWinSizey-1-fightWinSizey/4;

		int menuposx = allyposx+5;
		int menuposy = fightwinposy+7;
		int menusizex = fightwinposx+fightWinSizex-menuposx;
		int menusizey = fightWinSizey-6;


		fight = derwin(win, fightWinSizex+2, fightWinSizey+2, fightwinposx-1, fightwinposy-1);
		box(fight, ACS_VLINE, ACS_HLINE);

		mvprintw(enemyposx, enemyposy, "%s", poke.name);
		mvprintw(enemyposx+1, enemyposy, "PV : %d/%d", poke.pv, poke.pvmax);

		sprintf(ally, "%s", p->team.pokemons[teamindex]);
		mvprintw(allyposx, allyposy, ally);
		mvprintw(allyposx+1, allyposy, "PV : %d/%d", poke.pv, poke.pvmax);
	
		
		end = menu(win, menuposx, menuposy, menusizex, menusizey);
		// A changer car non

		wrefresh(fight);
	}
}

int menu(WINDOW* win, int posx, int posy, int sx, int sy){
	WINDOW* menu;
	int selection = 0;

	int c = 0;

	while(c != 127){
		menu = derwin(win, sx, sy, posx-2, posy-4);
		box(menu, ACS_VLINE, ACS_HLINE);
		for (int i = 0; i < MENULEN; i++){
			mvprintw(posx+i, posy, actions[i]);
		}
		attron(A_REVERSE);
		mvprintw(posx+selection, posy, actions[selection]);
		attroff(A_REVERSE);
		
		wrefresh(menu);
				
		c = getch();
		switch (c){
			case 65 :	// up
				selection += -1+(!selection)*MENULEN;
				break;
			case 66 :	// down
				selection += 1;
				selection %= MENULEN;
				break;
			case 9 :
			case 10 :
			case 32 :
			case 67 :
				return selection;

			case 127 :		//DEBUG
				return 127;
			default:
				break;
		}

	}
	return 127;
}