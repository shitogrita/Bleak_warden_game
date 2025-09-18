#pragma once
#include <memory>
#include <string>
#include <vector>
#include <algorithm>
#include "weapon.h"
#include "monster.h"

// типы классов
enum class ClassType { Warrior, Barbarian, Rogue };

// типы эффектов
enum class Effect {
    Rage,         // +2 урона первые 3 хода, потом -1
    Shield,       // -3 урона если сила > атакующего
    Poison,       // урон 1 в конце каждого круга
    HiddenStrike  // +1 урона если dex > цели
};

// активный эффект с таймером
struct ActiveEffect {
    Effect type;
    int duration; // -1 = бесконечно, >0 = количество раундов
};

struct Character {
    std::string name;
    ClassType classType;

    int strength = 0;
    int dex = 0;
    int endu = 0;

    int level = 0;
    int hp = 0;
    int maxHp = 0;

    std::unique_ptr<Weapon> weapon;
    std::vector<ActiveEffect> effects; // активные эффекты

    void restore();
    void addEffect(Effect e, int duration = -1);
    void clearEffects();
    int applyAttackEffects(const Monster& defender, int baseDamage);
    int applyDefenseEffects(const Monster& attacker, int incomingDamage);
    void applyEndOfRound(Monster& m);
};


void levelUp(Character& hero, std::unique_ptr<Weapon> droppedWeapon);

Character rand_stats();

Character createCharacter();
