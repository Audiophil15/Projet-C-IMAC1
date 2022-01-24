#ifndef FIGHT_H
#define FIGHT_H

#include <ncurses.h>
#include "pokemon.h"
#include "ui.h"

void fight(window_ win, player_* p, pokemon_* enemy);

// Actions
void attack(pokemon_* attacker, pokemon_* defender);
int isdead(pokemon_ poke);
void findItems(window_ w, player_* p);
int changePokemon(window_ wmenu, player* p, pokemon_** ally);
int escape(window_ wmenu);

//Animations
void animationAtkEffect(window_ w, pokemon_ atk, pokemon_ def);
int animationAllyAttack (window_  gwin, window_ msgwin, pokemon_* attacker, pokemon_* defender, int targetposx, int targetposy, int attackerposx, int attackerposy) ;
int animationEnemyAttack(window_ wfight, window_ wmenu, player* p, pokemon_** ally, pokemon_* enemy, int allyposx, int allyposy);
int animationCapture(window_ msgwin, player* p, pokemon_ poke, int ballIndex);
void animationPotion (window_ msgwin, player_* p, pokemon_* poke, int potionIndex);

#endif