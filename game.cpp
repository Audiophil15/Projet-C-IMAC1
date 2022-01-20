#include <iostream>
#include <ncurses.h>

#include "map.h"
#include "player.h"
#include "pokemon.h"
#include "pokedex.h"
#include "fight.h"
#include "ui.h"

int main(){

	// Creates pointers to place windows of ncurses in
	window_ wgame = initWindow(LINES, COLS, 0, 0);

	// inits the screen with the whole term as a window
	wgame.w = initscr();

	// First refresh allows curs_set() to work
	refresh();
	noecho();
	curs_set(0);

	// Rand seed init
	srand(time(NULL));

	// Init of the sides of the map, then the map itself is initialised and zeroed
	int mapxsize = 9*LINES/10;
	int mapysize = 9*COLS/10;
	map_ b = initMap(mapxsize, mapysize);

	/////////
	///////// Splash Screen
	/////////
	
	// Creates a player and puts it in the map
	// Get player's name
	char nom[15];
	msgbox(wgame, "Bonjour, je suis le Professeur Okitac.", LINES/2, COLS/2-25);
	msgbox(wgame, "Je ne crois pas te connaitre, comment t'appelles-tu ?", LINES/2+1, COLS/2-25, 0);
	// msgbox(wgame, "", LINES/2+2, COLS/2-25, 0); //Just to move the cursor to the line below
	curs_set(1);
	echo();
	mvgetnstr(LINES/2+2, COLS/2-25, nom, 14);
	noecho();
	curs_set(0);
	
	// player_ p = initPlayer((char*)"Philippe", &b, b.height/2, b.width/2);
	player_ p = initPlayer(nom, &b, b.height/2, b.width/2);

	// Adds the first pokemon to the player's team
	addPokeTeam(&p, initPokemon(PIKACHU));

	// First refresh of the map to see it when starting
	refreshMap(wgame.w, b);

	// Will receive the code returned by getch();
	int c = 0;

	// encounter ?
	int e;
	// encounter prbability
	int ep = 20;

	// Beginning of the game, stops when all species have been encountered, or when X is hit
	while (!pokedexFull(p.pokedex) && getFirstAliveIndex(p)!=-1 && c!=120){
		c = getch();
		
		// 410 is the "screen resize" code
		if (c==410){
			clear();
		}

		// Moves the player if c is the code of an arrow
		movePlayer(&p, &b, c);
		
		refreshMap(wgame.w, b);

		// DEBUG
		// Shows pokedex on screen
		if (c==112){
			char nana[2];
			int pmenusx = LINES/2;
			int pmenusy = COLS/3;
			int pmenuposx = LINES/4;
			int pmenuposy = COLS/3;
			WINDOW* pausemenu = derwin(wgame.w, pmenusx, pmenusy, pmenuposx, pmenuposy);
			wclear(wgame.w);
			for (int i = 0; i < p.pokedex.size; i++){
				sprintf(nana, "%d", p.pokedex.knownSpecies[i]);
				mvprintw(pmenuposx, pmenuposy+i, nana);
			}
			wrefresh(wgame.w);
			getch();
		
		} else {
			// Approx. one chance in ep of triggering an encounter
			e = rand()%ep;
			if (!e){
				pokemon_ wild = initPokemon((species)(rand()%PKDXS));
				fight(wgame, &p, &wild);
				clear();
				refreshMap(wgame.w, b);
			}
		}
	}

	if (pokedexFull(p.pokedex)){
		msgbox(wgame, "Felicitations, vous avez complete le pokedex !", LINES/2, COLS/2-23);
		getch();
		//Fin Reussie
	}

	if (getFirstAliveIndex(p)==-1){
		msgbox(wgame, "Vous n'avez plus de pokemon en forme !", LINES/2, COLS/2-19);
		msgbox(wgame, "Game Over", LINES/2+1, COLS/2-5, 0);
		getch();
	}

	// Free allocated memory
	delMap(b);
	delTeam(p.team);

	// Closes ncurses
	endwin();
}