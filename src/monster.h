#pragma once
#include "weapon.h"
#include "weapons_registry.h"
#include <memory>
#include <string>
#include <unordered_map>

enum class MonsterType {
    Goblin,
    Skeleton,
    Slime,
    Ghost,
    Golem,
    Dragon
};

struct Monster { // актуальный монстр игры (изменяется хр)
    MonsterType type;

    int strength = 0;
    int dex = 0;
    int endu = 0;

    int hp = 0;
    int maxHp = 0;

    std::unique_ptr<Weapon> weapon;
};

struct MonsterTemplate { // тип монстра
    int hp;
    int strength;
    int dex;
    int endu;
    std::string weaponId;
};

inline const std::unordered_map<MonsterType, MonsterTemplate> MonsterRegistry = {
    {MonsterType::Goblin,   {5, 1, 1, 1, "dagger"}},
    {MonsterType::Skeleton, {10, 2, 2, 1, "club"}},
    {MonsterType::Slime,    {8, 1, 3, 2, "spear"}},
    {MonsterType::Ghost,    {6, 1, 3, 1, "sword"}},
    {MonsterType::Golem,    {10, 3, 1, 3, "axe"}},
    {MonsterType::Dragon,   {20, 3, 3, 3, "legendary_sword"}}
};

inline Monster createMonster(MonsterType type) { // обявление вне клааса (фаьрика функция)
    const auto& tmpl = MonsterRegistry.at(type);

    Monster m;
    m.type     = type;
    m.hp       = tmpl.hp;
    m.maxHp    = tmpl.hp;
    m.strength = tmpl.strength;
    m.dex      = tmpl.dex;
    m.endu     = tmpl.endu;
    m.weapon   = std::make_unique<Weapon>(WeaponRegistry.at(tmpl.weaponId));

    return m;
}

inline std::string monsterName(MonsterType type) {
    switch (type) {
        case MonsterType::Goblin:   return "Гоблин";
        case MonsterType::Skeleton: return "Скелет";
        case MonsterType::Slime:    return "Слайм";
        case MonsterType::Ghost:    return "Призрак";
        case MonsterType::Golem:    return "Голем";
        case MonsterType::Dragon:   return "Дракон";
    }
}
