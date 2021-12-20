#include <iostream>
#include <ncurses.h>

#include "map.h"
#include "player.h"
#include "pokemon.h"

int main(){

	// Creates pointers to place windows of ncurses in
	WINDOW *win, *menu;

	// inits the screen with the whole term as a window
	win = initscr();

	// First refresh allows curs_set() to work
	refresh();
	noecho();
	curs_set(0);

	// Rand seed init
	srand(time(NULL));

	// Init of the sides of the map, then the map itself is initialised and zeroed
	int mapxsize = 3*LINES/4;
	int mapysize = 3*COLS/4;
	map_ b = initMap(mapxsize, mapysize);
	
	// Creates a player and puts it in the map
	player p = initPlayer("Philippe", &b, b.height/2, b.width/2);
	addPokeTeam(&p, initPokemon(&b, position_{0,0}, PIKACHU));

	// First refresh of the map to see it when starting
	refreshMap(win, b);

	// Will receive the code returned by getch();
	int c = 0;

	// encounter ?
	int e;

	// Beginning of the game, stop when all species have been encountered, or when Backspace is hit
	while (!pokedexFull(p.pokedex) && c!=127){
		c = getch();
		
		// 410 is the "screen resize" code
		if (c==410){
			clear();
		}

		// Move the player if c is the code of an arrow
		movePlayer(&p, &b, c);
		
		e = rand()%20;
		if (!e){
			clear();
			pokemon_ poke = initPokemon(&b, position_{0,0}, (species)(rand()%4+1));
			int end = 0;




			while (!end){
				char ally[35];

				int fightWinSizex = min(COLS, LINES)/2;
				int fightWinSizey = fightWinSizex*3;
				int fightwinposx = (LINES-fightWinSizex)/2;
				int fightwinposy = (COLS-fightWinSizey)/2;

				int enemyposx = fightwinposx+1;
				int enemyposy = fightwinposy+10;
				int allyposx = fightwinposx+fightWinSizex-1-fightWinSizex/2;
				int allyposy = fightwinposy+fightWinSizey-1-fightWinSizey/4;

				int menuposx = allyposx+3;
				int menuposy = fightwinposy+3;
				int menusizex = fightwinposx+fightWinSizex-menuposx;
				int menusizey = fightWinSizey-6;


				b.win = derwin(win, fightWinSizex+2, fightWinSizey+2, fightwinposx-1, fightwinposy-1);
				box(b.win, ACS_VLINE, ACS_HLINE);
			
				int teamindex = 0;

				mvprintw(enemyposx, enemyposy, "%s", poke.name);
				mvprintw(enemyposx+1, enemyposy, "PV : %d/%d", poke.pv, poke.pvmax);

				if (!p.team.nbpkmn){
					sprintf(ally, "%s", "Vous n'avez pas de Pokemon !");
					mvprintw(allyposx, allyposy-5, ally);
				} else {
					sprintf(ally, "%s", p.team.pokemons[teamindex]);
					mvprintw(allyposx, allyposy, ally);
					mvprintw(allyposx+1, allyposy, "PV : %d/%d", poke.pv, poke.pvmax);
				}

				menu = derwin(win, menusizex, menusizey, menuposx, menuposy);
				box(menu, ACS_VLINE, ACS_HLINE);
				wrefresh(menu);
				// mvprintw(menuposx, menuposy, );



				if(getch()==127){
					end = 1;
				}
				wrefresh(b.win);
			}
			
			clear();
		}
		refreshMap(win, b);
		
	}

	// Closes ncurses
	endwin();
}