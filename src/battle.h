#pragma once
#include "character.h"
#include "monster.h"

int firstAttack(Character& hero, Monster m);
bool fight(Character& hero, Monster m); // сама драка
void lootDrop(Character& hero, const Monster& m); // оружие после падение привыйграще

void attack(Monster& attacker, Character& defender);
void attack(Character& attacker, Monster& defender);

int calculateDamage(const Character& attacker, const Monster& defender);
int calculateDamage(const Monster& attacker, const Character& defender);


bool checkGameState(Character& hero, Monster m);