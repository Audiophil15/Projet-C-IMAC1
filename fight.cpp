#include <iostream>
#include <ncurses.h>
#include <unistd.h>

#include "pokemon.h"
#include "player.h"
#include "fight.h"
#include "ui.h"

void fight(WINDOW* win, player_* p, pokemon_* enemy){
	clear();

	window_ wfight;
	wfight.sx = min(COLS, LINES)/2;
	wfight.sy = wfight.sx*3;
	wfight.posx = (LINES-wfight.sx)/2;
	wfight.posy = (COLS-wfight.sy)/2;
	
	window_ wmenu;
	wmenu.sx = wfight.sx/2-4;
	wmenu.sy = wfight.sy-6;
	wmenu.posx = wfight.posx+wfight.sx/2+4;
	wmenu.posy = wfight.posy+7;
	
	int enemyposx;
	int enemyposy;
	int allyposx;
	int allyposy;

	enemyposx = wfight.posx+1;
	enemyposy = wfight.posy+10;
	allyposx = wfight.posx+wfight.sx/2-2;
	allyposy = wfight.posy+3*wfight.sy/4-5;

	wfight.w = derwin(win, wfight.sx+2, wfight.sy+2, wfight.posx-1, wfight.posy-1);
	wmenu.w = derwin(win, wmenu.sx, wmenu.sy, wmenu.posx-2, wmenu.posy-4);
	box(wfight.w, ACS_VLINE, ACS_HLINE);

	char * actions[] = {"Attaque", "Pokemon", "Capture", "Potion", "Fuite"};
	int menulen = 5;
	int teamindex = 0;
	int choice; 0;
	char msg [100];
	pokemon_ * ally = &(p->team.pokemons[teamindex]);

	// end = 1 : victory; end = 2 : defeat; end = 3 : flee
	int end=0;
	while (end == 0 && choice != 127){

		// box(fight, ACS_VLINE, ACS_HLINE);

		pkmnInfoDisplay(enemyposx, enemyposy, *enemy);
		pkmnInfoDisplay(allyposx, allyposy, *ally);	
		
		choice = menulist(wmenu, actions, menulen);


		switch (choice){
			case 0:
				// Attaque				
				sprintf(msg, "%s attaque !", ally->name);
				msgbox(wmenu, msg);
				// sleep(1); // REMETTRE
				attack(ally, enemy);
				pkmnInfoDisplay(enemyposx, enemyposy, *enemy);
				wrefresh(wfight.w);
				// sleep(1); // REMETTRE
				if (isdead(*enemy)){
					end = 1;
					sprintf(msg, "%s a perdu !", enemy->name);
					msgbox(wmenu, msg);
				}
				break;
			case 1:
				// Changer de pokemon
				teamindex = pokemonlist(wmenu, *p);
				ally = &(p->team.pokemons[teamindex]);
				break;
	
			case 2:
				// Capture
				p->pokeballs -= 1;
				if (1){
				// if (!(rand()%4)){
					end = 2;
					learn(enemy->s, &(p->pokedex));
					if (!addPokeTeam(p, *enemy)){
						sprintf(msg, "%s a ete capture !", enemy->name);
						msgbox(wmenu, msg);
					} else {
						sprintf(msg, "%s a ete capture !", enemy->name);
						msgbox(wmenu, msg);
						msgbox(wmenu, "L'equipe est pleine, il a ete envoye", 1, 0, 0);
						msgbox(wmenu, "sur votre PC.", 2, 0, 0);
					}
					// sleep(1); // REMETTRE
				} else {
					msgbox(wmenu, "Capture ratee !");
					// sleep(1); // REMETTRE
				}
				getch();
				break;

			case 3:
				// Potion
				if (p->potions>0){
					p->potions -= 1;
					sprintf(msg, "%s utilise une potion !", p->name);
					msgbox(wmenu, msg);
					// wrefresh(wmenu.w);
					// sleep(1); // REMETTRE
					ally->pv = min(ally->pv+20, ally->pvmax);
					pkmnInfoDisplay(allyposx, allyposy, *ally);	
					wrefresh(wfight.w);
				} else {
					msgbox(wmenu, "Plus de potions !");
					// sleep(1); // REMETTRE
				}
				break;

			case 4:
				// Fuite
				if (rand()%3){
					end = 3;
					msgbox(wmenu, "Vous prenez la fuite !");
				} else {
					msgbox(wmenu, "Fuite impossible !");
					// sleep(1); // REMETTRE
					wclear(wmenu.w);
				}
				break;
			
			default:
				break;
		}

		if (end == 0){
			sprintf(msg, "%s sauvage attaque !", enemy->name);
			msgbox(wmenu, msg);
			// sleep(1); // REMETTRE
			attack(enemy, ally);
			pkmnInfoDisplay(allyposx, allyposy, *ally);	
			wrefresh(wfight.w);
			// sleep(1); // REMETTRE
			if (isdead(*ally)){

			}
		}

		wrefresh(wfight.w);
	}

	wrefresh(wfight.w);
	// sleep(1); // REMETTRE

}



void attack(pokemon_* attacker, pokemon_* defender){
	defender->pv = max(0, defender->pv-max(attacker->atq-defender->def, 0));
}

int isdead(pokemon_ poke){
	return poke.pv==0;
}