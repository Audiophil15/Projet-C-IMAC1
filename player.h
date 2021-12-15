#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "board.h"

using namespace std;

#define JOUEUR -1

typedef struct position{
	int x;
	int y;
} position;

typedef struct player{
	string name;
	position pos;
} player;

player initPlayer(string name, board*, int, int);
void movePlayer(player*, board*, char);

#endif