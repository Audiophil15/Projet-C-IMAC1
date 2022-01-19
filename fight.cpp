#include <iostream>
#include <ncurses.h>
#include <unistd.h>

#include "pokemon.h"
#include "player.h"
#include "fight.h"
#include "ui.h"


void fight(WINDOW* win, player_* p, pokemon_* enemy){
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

	wfight.w = derwin(win, wfight.sx+2, wfight.sy+2, wfight.posx-1, wfight.posy-1);
	wmenu.w = derwin(win, wmenu.sx, wmenu.sy, wmenu.posx-2, wmenu.posy-4);
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


	char const * actions[] = {"Attaque", "Pokemon", "Capture", "Potion", "Fuite"};
	int menulen = 5;
	int tmpindex;//, teamindex = 0;
	int blockenemy;	// Allows to block the enemy's attack when quitting the "change pokemon" menu without changing
	int choice;		// What action is chosen
	char msg [100];	// Used to print message
	pokemon_ * ally = &(p->team.pokemons[getFirstAliveIndex(*p)]); // Just a shortcut to avoid to many memory access

	// end = 1 : victory; end = 2 : defeat; end = 3 : flee
	int end=0;
	while (end == 0 && choice != 120){ //DEBUG

		blockenemy = 0;
		// box(fight, ACS_VLINE, ACS_HLINE);

		pkmnInfoDisplay(wfight, enemyposx, enemyposy, *enemy);
		pkmnInfoDisplay(wfight, allyposx, allyposy, *ally);	
		
		do{
			choice = menulist(wmenu, actions, menulen);
		}while(choice==-1);

		switch (choice){
			case 0:
				// Attaque				
				end = animationAllyAttack(wfight, wmenu, ally, enemy, enemyposx, enemyposy, allyposx, allyposy);
				// sprintf(msg, "%s attaque !", ally->name);
				// msgbox(msgwin, msg);
				// // sleep(1); // REMETTRE
				// attack(ally, enemy);
				// pkmnInfoDisplay(wfight, enemyposx, enemyposy, *enemy);
				// wrefresh(wfight.w);
				// // sleep(1); // REMETTRE
				// if (isdead(*enemy)){
				// 	end = 1;
				// 	sprintf(msg, "%s a perdu !", enemy->name);
				// 	msgbox(msgwin, msg);
				// }
				break;
			case 1:
				// Changer de pokemon
				blockenemy = !(changePokemon(wmenu, p, &ally));
				// tmpindex = pokemonlist(wmenu, *p);
				// if (tmpindex != -1){ // If the user doesn't quit the menu, updates the pokemon index in the team
				// 	teamindex = tmpindex;
				// 	ally = &(p->team.pokemons[teamindex]);
				// } else {
				// 	blockenemy = 1;
				// }
				break;
	
			case 2:
				// Capture
				end = animationCapture(wmenu, p, *enemy);
				// if (p->pokeballs){
				// 	p->pokeballs -= 1;
				// 	if (1){
				// 	// if (!(rand()%4)){ //DEBUG
				// 		end = 2;
				// 		learn(enemy->s, &(p->pokedex));
				// 		if (!addPokeTeam(p, *enemy)){
				// 			sprintf(msg, "%s a ete capture !", enemy->name);
				// 			msgbox(msgwin, msg);
				// 		} else {
				// 			sprintf(msg, "%s a ete capture !", enemy->name);
				// 			msgbox(msgwin, msg);
				// 			msgbox(msgwin, "L'equipe est pleine, il a ete envoye", 1, 0, 0);
				// 			msgbox(msgwin, "sur votre PC.", 2, 0, 0);
				// 		}
				// 		// sleep(1); // REMETTRE
				// 	} else {
				// 		msgbox(msgwin, "Capture ratee !");
				// 		// sleep(1); // REMETTRE
				// 	}
				// }
				break;

			case 3:
				// Potion
				animationPotion(wfight, wmenu, p, ally, enemyposx, enemyposy);
				// if (p->potions){
				// 	p->potions -= 1;
				// 	sprintf(msg, "%s utilise une potion !", p->name);
				// 	msgbox(msgwin, msg);
				// 	// wrefresh(msgwin.w);
				// 	// sleep(1); // REMETTRE
				// 	ally->pv = min(ally->pv+20, ally->pvmax);
				// 	pkmnInfoDisplay(wfight, allyposx, allyposy, *ally);	
				// 	wrefresh(wfight.w);
				// } else {
				// 	msgbox(msgwin, "Plus de potions !");
				// 	// sleep(1); // REMETTRE
				// }
				break;

			case 4:
				// Fuite
				end = escape(wmenu);
				// if (rand()%3){
				// 	end = 3;
				// 	msgbox(wmenu, "Vous prenez la fuite !");
				// } else {
				// 	msgbox(wmenu, "Fuite impossible !");
				// 	// sleep(1); // REMETTRE
				// }
				break;
			
			default:
				break;
		}

		if (end == 0 && !blockenemy){
			end = animationEnemyAttack(wfight, wmenu, p, &ally, enemy, allyposx, allyposy);
			// sprintf(msg, "%s sauvage attaque !", enemy->name);
			// msgbox(wmenu, msg);
			// // sleep(1); // REMETTRE
			// attack(enemy, ally);
			// pkmnInfoDisplay(wfight, allyposx, allyposy, *ally);	
			// // wrefresh(wfight.w);
			// // sleep(1); // REMETTRE
			// if (isdead(*ally)){
			// 	sprintf(msg, "%s est KO, il ne peut plus combattre", ally->name);
			// 	msgbox(wmenu, msg);
			// 	choice=menulist(wmenu, actionsko, 2, 1,0);
			// 	if (choice==0) {

			// 	}



			// }
		}

		wrefresh(wfight.w);
	}

	wrefresh(wfight.w);
	sleep(1); // REMETTRE

}


void attack(pokemon_* attacker, pokemon_* defender){
	/* He doesn't protec but... he attak */
	defender->pv = max(0, defender->pv-max(attacker->atq-defender->def, 0));
}

int isdead(pokemon_ poke){
	/*So sad (?)*/
	return poke.pv==0;
}

int changePokemon(window_ wmenu, player* p, pokemon_** ally){
	int tmpindex = pokemonlist(wmenu, *p);
	if (tmpindex != -1){ // If the user doesn't quit the menu, updates the pokemon index in the team
		*ally = &(p->team.pokemons[tmpindex]);
		return 1;
	} else {
		return 0;
	}
}

int animationAllyAttack(window_  gwin, window_ msgwin, pokemon_* attacker, pokemon_* defender, int targetposx, int targetposy, int attackerposx, int attackerposy) {
// Attaque	
	char msg [30];			
	sprintf(msg, "%s attaque !", attacker->name);
	msgbox(msgwin, msg);
	// sleep(1); // REMETTRE
	attack(attacker, defender);
	pkmnInfoDisplay(gwin, targetposx, targetposy, *defender);
	// wrefresh(gwin.w);
	// sleep(1); // REMETTRE
	if (isdead(*defender)){
		sprintf(msg, "%s a perdu !", defender->name);
		msgbox(msgwin, msg);
		return 1;
	}
	return 0;
}

// NE MARCHE PAAAAAAAAS Dans le cas ou le dernier pokemon non KO du joueur est battu
int animationEnemyAttack(window_ wfight, window_ wmenu, player* p, pokemon_** ally, pokemon_* enemy, int allyposx, int allyposy){
	char msg[50];
	int choice;
	char const * actionsko[]={"changer de pokemon","fuir le combat"};
	sprintf(msg, "%s sauvage attaque !", enemy->name);
	msgbox(wmenu, msg);
	// sleep(1); // REMETTRE
	attack(enemy, *ally);
	pkmnInfoDisplay(wfight, allyposx, allyposy, **ally);	
	// wrefresh(wfight.w);
	// sleep(1); // REMETTRE
	if (isdead(**ally)){
		sprintf(msg, "%s est KO, il ne peut plus combattre", (*ally)->name);
		msgbox(wmenu, msg);
		if (getFirstAliveIndex(*p)){
			choice=menulist(wmenu, actionsko, 2, 1,0);
			if (choice!=-1) {
				changePokemon(wmenu, p, ally);
				return 0;
			} else {
				return escape(wmenu);
			}
		} else {
			msgbox(wmenu, "Vous n'avez plus de pokemon en forme !");
			return -1;
		}
	}
	return 0;
}

int animationCapture(window_ msgwin, player* p, pokemon_ poke) {
	// Capture
	char msg[30];
	if (p->pokeballs){
		p->pokeballs -= 1;
		if (1){
		// if (!(rand()%4)){ //DEBUG
			learn(poke.s, &(p->pokedex));
			if (!addPokeTeam(p, poke)){
				sprintf(msg, "%s a ete capture !", poke.name);
				msgbox(msgwin, msg);
			} else {
				sprintf(msg, "%s a ete capture !", poke.name);
				msgbox(msgwin, msg);
				msgbox(msgwin, "L'equipe est pleine, il a ete envoye", 1, 0, 0);
				msgbox(msgwin, "sur votre PC.", 2, 0, 0);
			}
			sleep(1); // REMETTRE
			return 2;
		} else {
			msgbox(msgwin, "Capture ratee !");
			sleep(1); // REMETTRE
		}
	}
	return 0;
}

void animationPotion (window_ gwin ,window_ msgwin, player_* p, pokemon_* poke, int pokeposx, int pokeposy){
	char msg[30];
	if (p->potions){
		p->potions -= 1;
		sprintf(msg, "%s utilise une potion !", p->name);
		msgbox(msgwin, msg);
		// wrefresh(msgwin.w);
		sleep(1); // REMETTRE
		poke->pv = min(poke->pv+20, poke->pvmax);
		pkmnInfoDisplay(gwin, pokeposx, pokeposy, *poke);
			
		// wrefresh(gwin.w);
	} else {
		msgbox(msgwin, "Plus de potions !");
		sleep(1); // REMETTRE
	}
}

int escape(window_ wmenu){
	if (rand()%3){
		msgbox(wmenu, "Vous prenez la fuite !");
		return 3;
	}
	msgbox(wmenu, "Fuite impossible !");
	sleep(1); // REMETTRE
	return 0;
}
