#include <iostream>
#include <ncurses.h>
#include <unistd.h>
#include <string.h>

#include "pokemon.h"
#include "player.h"
#include "fight.h"
#include "ui.h"


void fight(window_ win, player_* p, pokemon_* enemy){
	clear();

	// Init of the winodws that will show the fight interface and the menus/messages respectively
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

	wfight.w = derwin(win.w, wfight.sx+2, wfight.sy+2, wfight.posx-1, wfight.posy-1);
	wmenu.w = derwin(win.w, wmenu.sx, wmenu.sy, wmenu.posx-2, wmenu.posy-4);
	box(wfight.w, ACS_VLINE, ACS_HLINE);
	
	// Position of the ally and enemy's info
	int enemyposx;
	int enemyposy;
	int allyposx;
	int allyposy;

	// Up Left Corner
	enemyposx = wfight.posx+1;
	enemyposy = wfight.posy+10;
	// Bottom Right
	allyposx = wfight.posx+wfight.sx/2-2;
	allyposy = wfight.posy+3*wfight.sy/4-5;


	char const * actions[] = {"Attaque", "Pokemon", "Sac", "Fuite"};
	int menulen = 4;
	int tmpindex;//, teamindex = 0;
	int blockenemy;	// Allows to block the enemy's attack when quitting the "change pokemon" menu without changing
	int choice;		// What action is chosen
	char msg [100];	// Used to print message
	pokemon_ * ally = &(p->team.pokemons[getFirstAliveIndex(*p)]); // Just a shortcut to avoid to many memory access

	// end = 1 : victory; end = 2 : defeat; end = 3 : flee
	int end=0;
	while (end == 0 && choice != 120){ //120 = x // DEBUG

		// Used to bypass enemy's turn
		blockenemy = 0;

		pkmnInfoDisplay(wfight, enemyposx, enemyposy, *enemy);
		pkmnInfoDisplay(wfight, allyposx, allyposy, *ally);	
		
		do{
			choice = menulist(wmenu, actions, menulen);
		}while(choice==-1);

		switch (choice){
			case 0:
				// Attack
				// end = 1 if enemy is K.O.
				end = animationAllyAttack(wfight, wmenu, ally, enemy, enemyposx, enemyposy, allyposx, allyposy);
				break;
			case 1:
				// Allows to bypass enemy's turn if the player just goes back in the menu
				blockenemy = !(changePokemon(wmenu, p, &ally));
				break;
	
			// Cases 2 and 3 need to be merged in one "Inventory"/"Bag"
			case 2:
				// Capture
				// end = 2 if capture is successful
				switch(bagMenu(wmenu, *p)){
					case 0:
						animationPotion(wfight, wmenu, p, ally, allyposx, allyposy);
						break;
					case 1:
						end = animationCapture(wmenu, p, *enemy);
						break;
					case -1:
						blockenemy = 1;
					default :
						break;
				}
				// end = animationCapture(wmenu, p, *enemy);
				break;

			// case 3:
			// 	// Potion
			// 	animationPotion(wfight, wmenu, p, ally, allyposx, allyposy);
			// 	break;

			case 3:
				// Escape
				// end = 3 if escape if successful
				end = escape(wmenu);
				break;
			
			default:
				break;
		}

		// Enemy's turn
		if (end == 0 && !blockenemy){
			// end = -1 if all allies pokemon are K.O.
			end = animationEnemyAttack(wfight, wmenu, p, &ally, enemy, allyposx, allyposy);
		}
	}

	if (end == 1 && rand()%2){
		int qty = rand()%2+1;
		if (rand()%2){
			p->bag[0].qty += qty;
			sprintf(msg, "Vous obtenez %d pokeball", qty);
		} else {
			p->bag[1].qty += qty;
			sprintf(msg, "Vous obtenez %d potion", qty);
		}
		msgbox(wmenu, msg);
	}
}

void attack(pokemon_* attacker, pokemon_* defender){
	/* He doesn't protec but... he attak */
	defender->pv = max(0, defender->pv-max(attacker->atq*atkCoeff(*attacker, *defender)-defender->def, 0));
}

int isdead(pokemon_ poke){
	/*So sad (?)*/
	return poke.pv==0;
}

int changePokemon(window_ wmenu, player* p, pokemon_** ally){
	int tmpindex = pokemonMenu(wmenu, *p);
	if (tmpindex != -1){ // If the user doesn't quit the menu, updates the pokemon index in the team
		*ally = &(p->team.pokemons[tmpindex]);
		return 1;
	} else {
		return 0;
	}
}

int animationAllyAttack(window_  gwin, window_ msgwin, pokemon_* ally, pokemon_* enemy, int targetposx, int targetposy, int allyposx, int allyposy) {
// Attaque	
	char msg [30];			
	int atkcoeff;
	sprintf(msg, "%s attaque !", ally->name);
	msgbox(msgwin, msg);
	sleep(1);
	attack(ally, enemy);
	pkmnInfoDisplay(gwin, targetposx, targetposy, *enemy);
	sleep(1);
	atkcoeff = atkCoeff(*ally, *enemy);
	if (atkcoeff == 2){
		msgbox(msgwin, "Super patate !");
	} else if (atkcoeff == 0){
		msgbox(msgwin, "Aucune effet !");
	}
	sleep(2);
	if (isdead(*enemy)){
		sprintf(msg, "%s a perdu !", enemy->name);
		msgbox(msgwin, msg);
		return 1;
	}
	return 0;
}

int animationEnemyAttack(window_ wfight, window_ wmenu, player* p, pokemon_** ally, pokemon_* enemy, int allyposx, int allyposy){
	char msg[50];
	int choice, atkcoeff;
	char const * actionsko[]={"changer de pokemon","fuir le combat"};
	sprintf(msg, "%s sauvage attaque !", enemy->name);
	msgbox(wmenu, msg);
	sleep(1);
	attack(enemy, *ally);
	pkmnInfoDisplay(wfight, allyposx, allyposy, **ally);	
	sleep(1);
	atkcoeff = atkCoeff(*enemy, **ally);
	if (atkcoeff == 2){
		msgbox(wmenu, "Super patate !");
	} else if (atkcoeff == 0){
		msgbox(wmenu, "Aucune effet !");
	}
	sleep(2);
	if (isdead(**ally)){
		sprintf(msg, "%s est KO, il ne peut plus combattre", (*ally)->name);
		msgbox(wmenu, msg);
		sleep(1);
		if (getFirstAliveIndex(*p)!=-1){
			choice=menulist(wmenu, actionsko, 2, 1, 0);
			if (choice!=-1) {
				changePokemon(wmenu, p, ally);
				sprintf(msg, "Go %s !", (*ally)->name);
				msgbox(wmenu, msg);
				sleep(1);
				return 0;
			} else {
				return escape(wmenu);
			}
		} else {
			msgbox(wmenu, "Vous n'avez plus de pokemon en forme !");
			sleep(2);
			return -1;
		}
	}
	return 0;
}

int animationCapture(window_ msgwin, player* p, pokemon_ poke) {
	// Capture
	char msg[30];
	// p->bag[1] == Pokeballs
	if (p->bag[1].qty){
		p->bag[1].qty -= 1;
		sprintf(msg, "%s utilise une pokeball !", p->name);
		msgbox(msgwin, msg);
		sleep(1); // For the suspens
		if ((rand()%101 > 10+poke.pv*60/poke.pvmax)){
			msgbox(msgwin, "Tadaa !", 0, strlen(msg)+1, 0);
			if (!addPokeTeam(p, poke)){
				sprintf(msg, "%s a ete capture !", poke.name);
				msgbox(msgwin, msg);
			} else {
				sprintf(msg, "%s a ete capture !", poke.name);
				msgbox(msgwin, msg);
				msgbox(msgwin, "L'equipe est pleine, il a ete envoye", 1, 0, 0);
				msgbox(msgwin, "sur votre PC.", 2, 0, 0);
			}
			sleep(1);
			return 2;
		} else {
			msgbox(msgwin, "Capture ratee !");
		}
	} else {
		sprintf(msg, "Vous n'avez plus de pokeball !", p->name);
		msgbox(msgwin, msg);
	}
	sleep(1);
	return 0;
}

void animationPotion (window_ gwin ,window_ msgwin, player_* p, pokemon_* poke, int pokeposx, int pokeposy){
	char msg[30];
	// p->bag[0] == Potions
	if (p->bag[0].qty){
		p->bag[0].qty -= 1;
		sprintf(msg, "%s utilise une potion !", p->name);
		msgbox(msgwin, msg);
		sleep(1);
		poke->pv = min(poke->pv+20, poke->pvmax);
		pkmnInfoDisplay(gwin, pokeposx, pokeposy, *poke);
		sleep(1);
	} else {
		msgbox(msgwin, "Vous n'avez plus de potions !");
		sleep(1);
	}
}

int escape(window_ wmenu){
	if (rand()%3){
		msgbox(wmenu, "Vous prenez la fuite !");
		sleep(1);
		return 3;
	}
	msgbox(wmenu, "Fuite impossible !");
	sleep(1);
	return 0;
}
