#include <stdlib.h>

#include "inventory.h"

char const * itemNames[] = {"Potion", "Pokeball", "Super Potion", "Super Ball"};
int quantities[] = {10, 20, 5, 5};

inventory_ initInventory(){
	inventory_ bag = (inventory_)malloc(sizeof(int)*INVENTSIZE);
	for (int i = 0; i < INVENTSIZE; i++){
		bag[i].name = itemNames[i];
		bag[i].qty = quantities[i];
	}
	return bag;
	
}
