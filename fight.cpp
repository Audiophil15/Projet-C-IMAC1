#include <iostream>
#include <ncurses.h>
#include <unistd.h>

#include "pokemon.h"
#include "player.h"
#include "fight.h"
#include "ui.h"

void fight(WINDOW* win, player_* p, pokemon_* enemy){
	clear();

	WINDOW *fight;
	WINDOW* menu;

	int fightWinSizex;
	int fightWinSizey;
	int fightwinposx;
	int fightwinposy;
	int enemyposx;
	int enemyposy;
	int allyposx;
	int allyposy;
	int menuposx;
	int menuposy;
	int menusizex;
	int menusizey;

	fightWinSizex = min(COLS, LINES)/2;
	fightWinSizey = fightWinSizex*3;
	fightwinposx = (LINES-fightWinSizex)/2;
	fightwinposy = (COLS-fightWinSizey)/2;

	enemyposx = fightwinposx+1;
	enemyposy = fightwinposy+10;
	allyposx = fightwinposx+fightWinSizex/2-2;
	allyposy = fightwinposy+3*fightWinSizey/4-5;

	menuposx = fightwinposx+fightWinSizex/2+4;
	menuposy = fightwinposy+7;
	menusizex = fightwinposx+fightWinSizex-menuposx;
	menusizey = fightWinSizey-6;

	fight = derwin(win, fightWinSizex+2, fightWinSizey+2, fightwinposx-1, fightwinposy-1);
	box(fight, ACS_VLINE, ACS_HLINE);
	menu = derwin(win, menusizex, menusizey, menuposx-2, menuposy-4);

	char const * actions[] = {"Attaque", "Capture", "Potion", "Fuite"};
	int menulen = 4;
	int teamindex = 0;
	int choice;
	char msg [30];
	pokemon_ * ally = &(p->team.pokemons[teamindex]);

	// end = 1 : victory; end = 2 : defeat; end = 3 : flee
	int end=0;
	while (end == 0 && choice != 127){

		// box(fight, ACS_VLINE, ACS_HLINE);

		pkmnInfoDisplay(enemyposx, enemyposy, *enemy);
		pkmnInfoDisplay(allyposx, allyposy, *ally);	
		
		choice = menulist(menu, menuposx, menuposy, menusizex, menusizey, actions, menulen);


		switch (choice){
			case 0:
				// Attaque
				sprintf(msg, "%s attaque !", ally->name);
				msgbox(menu, menuposx, menuposy, msg);
				sleep(1);
				attack(ally, enemy);
				pkmnInfoDisplay(enemyposx, enemyposy, *enemy);
				wrefresh(fight);
				sleep(1);
				if (isdead(*enemy)){
					end = 1;
					sprintf(msg, "%s a perdu !", enemy->name);
					msgbox(menu, menuposx, menuposy, msg);
				}
				break;
			case 1:
				// Capture
				p->pokeballs -= 1;
				if (!(rand()%4)){
					end = 2;
					addPokeTeam(p, *enemy);
					sprintf(msg, "%s a ete capture !", enemy->name);
					msgbox(menu, menuposx, menuposy, msg);
					sleep(1);
				} else {
					msgbox(menu, menuposx, menuposy, "Capture ratee !");
					sleep(1);
				}
				break;

			case 2:
				// Potion
				if (p->potions>0){
					p->potions -= 1;
					sprintf(msg, "%s utilise une potion !", p->name);
					msgbox(menu, menuposx, menuposy, msg);
					wrefresh(menu);
					sleep(1);
					ally->pv = min(ally->pv+20, ally->pvmax);
					pkmnInfoDisplay(allyposx, allyposy, *ally);	
					wrefresh(fight);
				} else {
					msgbox(menu, menuposx, menuposy, "Plus de potions !");
					sleep(1);
				}
				break;

			case 3:
				// Fuite
				if (rand()%3){
					end = 3;
					msgbox(menu, menuposx, menuposy, "Vous prenez la fuite !");
				} else {
					msgbox(menu, menuposx, menuposy, "Fuite impossible !");
					sleep(1);
					wclear(menu);
				}
				break;
			
			default:
				break;
		}

		if (end == 0){
			sprintf(msg, "%s attaque !", enemy->name);
			msgbox(menu, menuposx, menuposy, msg);
			sleep(1);
			attack(enemy, ally);
			pkmnInfoDisplay(allyposx, allyposy, *ally);	
			wrefresh(fight);
			sleep(1);
			if (isdead(*ally)){
			}
		}

		wrefresh(fight);
	}

	wrefresh(fight);
	sleep(1);

}



void attack(pokemon_* attacker, pokemon_* defender){
	defender->pv = max(0, defender->pv-max(attacker->atq-defender->def, 0));
}

int isdead(pokemon_ poke){
	return poke.pv==0;
}