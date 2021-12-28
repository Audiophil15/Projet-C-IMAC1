#include <iostream>
#include <ncurses.h>
#include <time.h>
#include <unistd.h>

#include "pokemon.h"
#include "map.h"
#include "player.h"
#include "fight.h"



void fight(WINDOW* win, player_* p){
	WINDOW *fight;
	clear();
	pokemon_ poke = initPokemon((species)(rand()%4+1));
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

		int menulen;
		char * actionsconst[] = {"Attaque", "Capture", "Fuite"};
		char** actions;
		int teamindex = 0;

		if (!p->team.nbpkmn){
			sprintf(ally, "%s", "Vous n'avez pas de Pokemon !");
			mvprintw(allyposx, allyposy-5, ally);
			
			actions = &(actionsconst[1]);
			menulen = 2;		
		
		} else {
			sprintf(ally, "%s", p->team.pokemons[teamindex]);
			mvprintw(allyposx, allyposy, ally);
			mvprintw(allyposx+1, allyposy, "PV : %d/%d", poke.pv, poke.pvmax);
		
			actions = actionsconst;
			menulen = 3;
		
		}
		
		end = menu(win, menuposx, menuposy, menusizex, menusizey, actions, menulen);

		wrefresh(fight);
	}
}

int menu(WINDOW* win, int posx, int posy, int sx, int sy, char ** actions, int menulength){
	WINDOW* menu;
	int selection = 0;
	int* tabmenuposx = (int*)malloc(sizeof(int)*menulength);
	for (int i = 0; i < menulength; i++){
		tabmenuposx[i] = posx+i;
	}
	int c = 0;

	char msg[50];

	while(c != 127){
		menu = derwin(win, sx, sy, posx-2, posy-4);
		box(menu, ACS_VLINE, ACS_HLINE);
		for (int i = 0; i < menulength; i++){
			mvprintw(tabmenuposx[i], posy, actions[i]);
		}
		attron(A_REVERSE);
		mvprintw(tabmenuposx[selection], posy, actions[selection]);
		attroff(A_REVERSE);
		
		wrefresh(menu);
				
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