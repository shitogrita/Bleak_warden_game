#include "monster.h"
#include <iostream>
#include <vector>
#include <memory>

size_t currentMonsterIndex = 0;

inline const std::vector<MonsterType> MonsterOrder = {
    MonsterType::Goblin,
    MonsterType::Skeleton,
    MonsterType::Slime,
    MonsterType::Ghost,
    MonsterType::Golem,
    MonsterType::Dragon
};


std::unique_ptr<Monster> spawnNextMonster() {
    if (currentMonsterIndex >= MonsterOrder.size()) return nullptr;

    MonsterType type = MonsterOrder[currentMonsterIndex];
    currentMonsterIndex++;

    auto monster = std::make_unique<Monster>(createMonster(type));
    return monster;
}

void printMonsterInfo(const Monster& m) {
    std::cout << "MONSTER: " << monsterName(m.type) << std::endl;
    std::cout << "HP: " << m.hp << "/" << m.maxHp << std::endl;
    std::cout << "STRENGTH: " << m.strength << std::endl;
    std::cout << "DEX: " << m.dex << std::endl;
    std::cout << "ENDU: " << m.endu << std::endl;
    auto weapon_info = weapon->id; std::cout << weapon_info << std::endl;

}
