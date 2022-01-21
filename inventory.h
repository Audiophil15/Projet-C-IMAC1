#ifndef INVENTORY_H
#define INVENTORY_H

// Potions, Pokeballs, Super Potions, Super Ball
#define INVENTSIZE 4

typedef struct{
	char const * name;
	int qty;
} item_;

typedef item_* inventory_;

inventory_ initInventory();

#endif