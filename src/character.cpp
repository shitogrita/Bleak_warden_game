#include "character.h"
#include <iostream>
#include <cstdlib>

void Character::restore() {
    hp = maxHp;
}

Character rand_stats() {
    Character hero;
    hero.strength = 1 + rand() % 3;
    hero.dex = 1 + rand() % 3;
    hero.endu = 1 + rand() % 3;
    hero.level = 0;
    return hero;
}

void Character::printInfo(const Character& hero) {
    std::cout << "HP: " << hero.hp << std::endl;
    std::cout << "STRENGTH: " << hero.strength << std::endl;
    std::cout << "DEX: " << hero.dex << std::endl;
    std::cout << "ENDD: " << hero.endu << std::endl;
    std::cout << "LEVEL: " << hero.level << std::endl;
    std::cout << "MAXHP: " << maxHp << std::endl;
    auto weapon_info = weapon->id;
    std::cout << weapon_info << std::endl;

}

Character createCharacter() {


    auto type = ClassType::Rogue;
    /* логика ввода */
    Character hero = rand_stats();
    hero.classType = type; // ?

    switch (type) {
        case ClassType::Rogue:  // Разбойник
            hero.weapon = std::make_unique<Weapon>(WeaponRegistry.at("dagger"));
            hero.maxHp = 4 + hero.endu;
            std::cout << "created hero with this chars: " << std::endl;
            hero.printInfo(hero);
            break;

        case ClassType::Warrior:  // Воин
            hero.weapon = std::make_unique<Weapon>(WeaponRegistry.at("sword"));
            hero.maxHp = 5 + hero.endu;
            break;

        case ClassType::Barbarian:  // Варвар
            hero.weapon = std::make_unique<Weapon>(WeaponRegistry.at("club"));
            hero.maxHp = 6 + hero.endu;
            break;
    }
    hero.hp = hero.maxHp;
    return hero;
}

// он повышает уровень, его здоровье восстанавливается до максимума и
// ему предлагается заменить его текущее оружие на то, что выпало из монстра.

bool checkDex(Character& hero, Monster& m) {
    return hero.dex > m.dex;
}

bool checkStrength(Character& hero, Monster& m) {
    return hero.strength > m.strength;
}

void levelUp(Character& hero, std::unique_ptr<Weapon> droppedWeapon) {
    hero.level++;
    hero.restore();

    switch (hero.classType) {
        case ClassType::Rogue:
            if (hero.level == 1) {
                if (checkDex) {hero.strength ++;} // +
                // скрытая атака
                // эффект в бою: +1 урон если dex > dex цели
            } else if (hero.level == 2) { // +
                hero.dex += 1;
            } else if (hero.level == 3) {
                // тут надо менять боевку оснвоную и счетчик на количесвто кругов боя и выволдить ак лдругую функцию
                // яд (урон накапливается каждый ход)
            }
            break;

        case ClassType::Warrior:
            if (hero.level == 1) {
                /* if (firstAttack() == 0) {
                    // firstAttack = hero.strength + 2; // ?
                // порыв к действию (первый ход урон *2)
                } */
            } else if (hero.level == 2) {
                 /* if (checkStrength(hero, )) {
                     hero.hp += 3;
                     // щит (-3 урона, если сила > атакующего)
                    } */
            } else if (hero.level == 3) {
                hero.strength += 1;
            }
            break;

        case ClassType::Barbarian:
            /*if (hero.level == 1) {
               if (fisrtAttack && c < 3) {
                    c += 1;
                    void attack() + 2 ;
               }
                // ярость (+2 урона первые 3 хода, потом -1)
            } else if (hero.level == 2) {
                hero.hp += hero.endu;
                // каменная кожа (урон уменьшается на endu)
            } else if (hero.level == 3) {
                hero.endu += 1;
            }
            break; */
    }
    if (droppedWeapon) {
        if (!hero.weapon || droppedWeapon->damage > hero.weapon->damage) {
            hero.weapon = std::move(droppedWeapon);
        }
    }
}








// добавить эффект идея гпт

void Character::addEffect(Effect e, int duration) {
    for (auto& eff : effects) {
        if (eff.type == e) {
            eff.duration = duration;
            return;
        }
    }
    effects.push_back({e, duration});
}

// убрать все эффекты
void Character::clearEffects() {
    effects.clear();
}

// модификация урона при атаке
int Character::applyAttackEffects(const Monster& defender, int baseDamage) {
    int dmg = baseDamage;

    for (auto& eff : effects) {
        switch (eff.type) {
            case Effect::Rage:
                if (eff.duration != 0) dmg += 2;
                else dmg -= 1;
                break;
            case Effect::HiddenStrike:
                if (dex > defender.dex) dmg += 1;
                break;
            default: break;
        }
    }
    return dmg;
}

// модификация урона при защите
int Character::applyDefenseEffects(const Monster& attacker, int incomingDamage) {
    int dmg = incomingDamage;

    for (auto& eff : effects) {
        switch (eff.type) {
            case Effect::Shield:
                if (strength > attacker.strength) dmg -= 3;
                break;
            default: break;
        }
    }
    return std::max(0, dmg);
}

// эффекты конца раунда
void Character::applyEndOfRound(Monster& m) {
    for (auto& eff : effects) {
        switch (eff.type) {
            case Effect::Poison:
                if (eff.duration != 0) {
                    m.hp -= 1; // отравление врага
                }
                break;
            default: break;
        }
    }

    // уменьшаем таймеры
    for (auto& eff : effects) {
        if (eff.duration > 0) eff.duration--;
    }

    // чистим истёкшие эффекты
    effects.erase(
        std::remove_if(effects.begin(), effects.end(),
                       [](const ActiveEffect& e) { return e.duration == 0; }),
        effects.end()
    );
}