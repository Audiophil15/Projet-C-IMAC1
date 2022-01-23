#ifndef FIGHT_H
#define FIGHT_H

#include <ncurses.h>
#include "pokemon.h"
#include "ui.h"

void fight(window_ win, player_* p, pokemon_* enemy);
void attack(pokemon_* attacker, pokemon_* defender);
int isdead(pokemon_ poke);
int changePokemon(window_ wmenu, player* p, pokemon_** ally);
void animationAtkEffect(window_ w, pokemon_ atk, pokemon_ def);
int animationAllyAttack (window_  gwin, window_ msgwin, pokemon_* attacker, pokemon_* defender, int targetposx, int targetposy, int attackerposx, int attackerposy) ;
int animationEnemyAttack(window_ wfight, window_ wmenu, player* p, pokemon_** ally, pokemon_* enemy, int allyposx, int allyposy);
int animationCapture(window_ msgwin, player* p, pokemon_ poke);
void animationPotion (window_ gwin ,window_ msgwin, player_* p, pokemon_* poke, int pokeposx, int pokeposy);
int escape(window_ wmenu);

#endif