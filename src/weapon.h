#pragma once
#include "weapons.h"
#include <unordered_map>
#include <string>

enum class DamageType { Slashing, Piercing, Blunt };

struct Weapon {
    std::string id;
    int damage = 0;
    DamageType type;
};

inline const std::unordered_map<std::string, Weapon> WeaponRegistry = {
    {"sword",  {"sword",  "Меч",     3, DamageType::Slashing}},
    {"club",   {"club",   "Дубина",  3, DamageType::Blunt}},
    {"dagger", {"dagger", "Кинжал",  2, DamageType::Piercing}},
    {"axe",    {"axe",    "Топор",   4, DamageType::Slashing}},
};

