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
	enemyposx = 1;
	enemyposy = 10;
	// Bottom Right
	allyposx = wfight.sx/2-2;
	allyposy = 3*wfight.sy/4-5;

	char const * actions[] = {"Attaque", "Pokemon", "Sac", "Fuite"};
	int menulen = 4;
	int blockenemy;	// Allows to block the enemy's attack when quitting the "change pokemon" menu without changing
	int choice;		// What action is chosen
	pokemon_ * ally = &(p->team.pokemons[getFirstAliveIndex(*p)]); // Just a shortcut to avoid to many memory access

	// end = 1 : victory; end = 2 : defeat; end = 3 : flee
	int end=0;
	while (end == 0){

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
				pkmnInfoDisplay(wfight, allyposx, allyposy, *ally);	
				break;
			// Cases 2 and 3 need to be merged in one "Inventory"/"Bag"
			case 2:
				// Capture
				// end = 2 if capture is successful
				switch(bagMenu(wmenu, *p)){
					case 0:
						animationPotion(wmenu, p, ally, 0);
						pkmnInfoDisplay(wfight, allyposx, allyposy, *ally);	
						break;
					case 1:
						end = animationCapture(wmenu, p, *enemy, 0);
						break;
					case 2:
						animationPotion(wmenu, p, ally, 1);
						pkmnInfoDisplay(wfight, allyposx, allyposy, *ally);	
						break;
					case 3:
						end = animationCapture(wmenu, p, *enemy, 1);
						break;
					case -1:
						blockenemy = 1;
					default :
						break;
				}
				// end = animationCapture(wmenu, p, *enemy);
				break;
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

	if (end == 1 && rand()%10>3){
		findItems(wmenu, p);
	}
}

// Actions

void attack(pokemon_* attacker, pokemon_* defender){
	/* He doesn't protec but... he attak */
	if (atkCoeff(*attacker, *defender)){
		defender->pv = max(0, defender->pv-max(attacker->atq*atkCoeff(*attacker, *defender)+rand()%7-3-defender->def, 1));
	}
}

void findItems(window_ w, player_* p){
	int qty = rand()%3+1;
	int item = rand()%4;
	char msg[40];
	p->bag[item].qty += qty;
	switch (item){
	case 0:
		sprintf(msg, "Vous avez obtenu %d Potion !", qty);
		break;
	case 1:
		sprintf(msg, "Vous avez obtenu %d Pokeball !", qty);
		break;
	case 2:
		sprintf(msg, "Vous avez obtenu %d Super Potion !", qty);
		break;
	case 3:
		sprintf(msg, "Vous avez obtenu %d Super Ball !", qty);
		break;
	default:
		break;
	}
	msgbox(w, msg);
	sleep(2);
}

int changePokemon(window_ wmenu, player* p, pokemon_** ally){
	/* Allows to change the pokemon, and checks if the pokemon has been changed, used together with blockenemy variable to simulate a possibility not to change the pokemon without skipping its turn*/
	int tmpindex = pokemonMenu(wmenu, *p);
	if (tmpindex != -1){ // If the user doesn't quit the menu, updates the pokemon index in the team
		*ally = &(p->team.pokemons[tmpindex]);
		return 1;
	} else {
		return 0;
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

// Animations

int animationAllyAttack(window_  gwin, window_ wmenu, pokemon_* ally, pokemon_* enemy, int targetposx, int targetposy, int allyposx, int allyposy) {
	/* Creates the animation of text and health bar/numbers on the ally attack */

// Attaque	
	char msg [40];			
	sprintf(msg, "%s attaque !", ally->name);
	msgbox(wmenu, msg);
	sleep(1);
	attack(ally, enemy);
	pkmnInfoDisplay(gwin, targetposx, targetposy, *enemy);
	sleep(1);
	animationAtkEffect(wmenu, *ally, *enemy);
	if (isdead(*enemy)){
		sprintf(msg, "%s a perdu !", enemy->name);
		msgbox(wmenu, msg);
		sleep(2);
		return 1;
	}
	return 0;
}

int animationEnemyAttack(window_ wfight, window_ wmenu, player* p, pokemon_** ally, pokemon_* enemy, int allyposx, int allyposy){
	/* Creates the animation of text and health bar/numbers on the enemy attack */

	char msg[65];
	int choice;
	char const * actionsko[]={"Changer de pokemon","uir le combat"};
	sprintf(msg, "%s sauvage attaque !", enemy->name);
	msgbox(wmenu, msg);
	sleep(1);
	attack(enemy, *ally);
	pkmnInfoDisplay(wfight, allyposx, allyposy, **ally);	
	sleep(1);
	animationAtkEffect(wmenu, *enemy,**ally);
	if (isdead(**ally)){
		sprintf(msg, "%s est KO, il ne peut plus combattre", (*ally)->name);
		msgbox(wmenu, msg);
		sleep(2);
		if (getFirstAliveIndex(*p)!=-1){
			do{
				choice=menulist(wmenu, actionsko, 2, 1, 0);
				// MUST be kept in THIS order, if the escape fails, the return value allows to fall in the cnage pokemon case
				if (choice==1) {
					if(escape(wmenu)){
						return 3;	// Return value for the successful escape
					} else {
						choice = 0;	// Falls to the pokemon choice
					}
				}
				if (choice==0) {
					while(changePokemon(wmenu, p, ally)==0){};
					sprintf(msg, "Go %s !", (*ally)->name);
					msgbox(wmenu, msg);
					sleep(1);
					return 0;
				}
			} while(choice==-1);
		} else {
			msgbox(wmenu, "Vous n'avez plus de pokemon en forme !");
			sleep(2);
			return -1;
		}
	}
	return 0;
}

int animationCapture(window_ msgwin, player* p, pokemon_ poke, int ballIndex) {
	/* Creates the animation for the capture and calls the functions used to update team if needed */

	// Capture
	char msg[75];
	char const * item[] = {"Pokeball", "Super Ball"};
	// p->bag[1] == Pokeballs, 3==Super Balls
	int index = ballIndex*2+1;
	if (p->bag[index].qty){
		p->bag[index].qty -= 1;
		sprintf(msg, "%s utilise une %s !", p->name, item[ballIndex]);
		msgbox(msgwin, msg);
		sleep(1); // For the suspens
		if ((rand()%101 > 10+poke.pv*60/poke.pvmax-ballIndex*30)){
			msgbox(msgwin, "Tadaa !", 0, strlen(msg)+1, 0);
			sleep(1);
			sprintf(msg, "%s a ete capture !", poke.name);
			msgbox(msgwin, msg);
			if (addPokeTeam(p, poke)){
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

void animationPotion (window_ msgwin, player_* p, pokemon_* poke, int potionIndex){
	/* Creates the animation for the potion and updates pokemon's pv */

	char msg[30];
	char const * item[] = {"Potion", "Super Potion"};
	// p->bag[1] == potion, 3==Super Potion
	int index = potionIndex*2;
	// p->bag[0] == Potions
	if (p->bag[index].qty){
		p->bag[index].qty -= 1;
		sprintf(msg, "%s utilise une %s !", p->name, item[potionIndex]);
		msgbox(msgwin, msg);
		sleep(1);
		poke->pv = min(poke->pv+20*(index==0)+50*(index==1), poke->pvmax);
		sleep(1);
	} else {
		msgbox(msgwin, "Vous n'avez plus de potions !");
		sleep(1);
	}
}

void animationAtkEffect(window_ w, pokemon_ atk, pokemon_ def){
	int atkcoeff = atkCoeff(atk, def);
	if (atkcoeff != 1){
		if (atkcoeff == 2){
			msgbox(w, "Super patate !");
		} else {	// atkcoeff == 0
			msgbox(w, "Aucune effet !");
		}
		sleep(2);
	}
}
