#include <iostream>
#include <ncurses.h>

#include "board.h"
#include "player.h"
#include "pokemon.h"

int main(){

	WINDOW *win, *menu;

	srand(time(NULL));

	board b = initBoard(15, 30);
	player p = initPlayer("Philippe", &b, b.height/2, b.width/2);
	
	pokemon pikachu = initPokemon("Pikachu", &b, position{0,0}, 50, 10, 10, ELEK, PIKACHU);
	pokemon salameche = initPokemon("Salameche", &b, position{12, 2}, 50, 10, 10, FEU, SALAMECHE);
	pokemon carapuce = initPokemon("Carapuce", &b, position{5,25}, 50, 10, 10, EAU, CARAPUCE);
	pokemon bulbizarre = initPokemon("Bulbizarre", &b, position{12,28}, 50, 10, 10, PLANTE, BULBIZARRE);
	

	win = initscr();

	refreshBoard(win, b);

	int c = 0;
	while (c!=127){
		c = getch();
		
		// 410 is the "screen resize" code
		if (c==410){
			clear();
		}

		movePlayer(&p, &b, c);
		refreshBoard(win, b);

	}

	endwin();
}