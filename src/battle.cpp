#include "battle.h"
#include <iostream>
#include <cstdlib>

int firstAttack(Character& hero, Monster& m) { // менять на дул или так пока хз
    int val = 1 + rand() % (hero.dex + m.dex);
    if (val >= m.dex ) {
        return 0;
    }
    return 1;
}

bool checkFightOver(Character& hero, Monster& m) {
    if (hero.hp <= 0) {
        return true;
    }
    if (m.hp <= 0) {
        hero.hp = hero.maxHp;
        return true;
    }
    return false;
}

void attack(Character& attacker, Monster& defender) {
    int roll = 1 + rand() % (attacker.dex + defender.dex);
    if (roll <= defender.dex) {
        return;
    }

    int dmg = calculateDamage(attacker, defender);
    defender.hp -= dmg;
}

void attack(Monster& attacker, Character& defender) { // можеь менять тип что бы можно было сложить лол

    int roll = 1 + rand() % (attacker.dex + defender.dex);
    if (roll <= defender.dex) {
        return;
    }

    int dmg = calculateDamage(attacker, defender);
    defender.hp -= dmg;
}

/*
int applyAttackEffects(const Character& attacker, int baseDamage) {
    // пока эффекты отключены на 0 уровне
    if (attacker.level == 0) return baseDamage;

    int result = baseDamage;
    // пример: "Ярость" +2 урона
    // if (attacker.hasEffect("Rage")) result += 2;

    return result;
}

int applyDefenseEffects(const Character& defender, int damage) {
    if (defender.level == 0) return damage;

    int result = damage;
    // пример: "Щит" уменьшает урон на 1
    // if (defender.hasEffect("Shield")) result -= 1;

    return std::max(0, result); // урон не может быть отрицательным
}


int calculateDamage(const Character& attacker, const Monster& defender) {
    int baseDamage = attacker.weapon
        ? attacker.weapon->damage + attacker.strength
        : attacker.strength;

    int modified = attacker.applyAttackEffects(attacker, baseDamage);
    modified = attacker.applyDefenseEffects(defender, modified);

    return modified;
}

int calculateDamage(const Monster& attacker, const Character& defender) {
    int baseDamage = attacker.weapon
        ? attacker.weapon->damage + attacker.strength
        : attacker.strength;

    int modified = applyAttackEffects(attacker, baseDamage);
    modified = applyDefenseEffects(defender, modified);

    return modified;
}

*/


void lootDrop(Character& hero, Monster& m) {
    if (m.weapon) {
        hero.weapon = std::move(m.weapon);
    }
}

bool fight(Character& hero, Monster& m, int& rounds, int& kills) {

    // добавть количесво обзие жертв полрят  и круги в бою считаь чтот один круг это удар монстра и героя
    rounds = 0;

    int turn = firstAttack(hero, m);
    while (!checkFightOver(hero, m)) {
        if (turn == 0) {
            attack(hero, m);
            turn = 1;
        } else {
            attack(m, hero);
            turn = 0;
        }
        if (turn == 0) {
            rounds++;
        }
    }
    if (hero.hp > 0) {
        lootDrop(hero, m);
        kills++;
        return true;
    }
    return false;
}



int calculateDamage(const Character& attacker, const Monster& defender) { return 0; }
int calculateDamage(const Monster& attacker, const Character& defender) { return 0; }


