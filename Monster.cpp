/* 
 * File:   Monster.cpp
 * Author: aris
 * 
 * Created on 20 Ιανουάριος 2011, 6:44 μμ
 */
#define MAX_HEALTH 300
#define MAX_MAGIC 300
#define MAX_DAMAGE 100
#define MAX_DEFENCE 50
#define MAX_AVOID_CHANCE 75 // %

#include <stdlib.h>
#include <math.h>
#include <iostream>
using std::cout;
using std::endl;

#include "Monster.h"
#include "Hero.h"

Monster::Monster(int level) {
    if (level < 1)
        level = 1;
    else if (level > 5)
        level = 5;
    
    char name[][15] = {"Charmalaine", "Eadro", "Gruumsh", "Hruggek", "Ilsensine",
        "Jubilex", "Kurtulmak", "Laduguer", "Loagzed", "Lolth", "Maglubiyet",
        "Merrshaulk", "Orcus", "Sekolah", "Semuanya", "Tiamat", "Vaprak",
        "Yeenoghu", "Aasterinian", "Bagrivyek"};
    int n = rand() % 20;
    SetName(name[n]);

    // Set random type and appropriate initial values
    int rt = rand() % 3;
    switch (rt) {
        case '0':
            mt = Dragon;
            break;
        case 1:
            mt = Exoskeleton;
            break;
        case 2:
            mt = Spirit;
            break;
    }
    st = Healthy;

    SetLevel(level);

    // Initialize attributes
    rounds = 0;
    decreaseAvoidChance = 0;
    decreaseDamage = 0;
    decreaseDefence = 0;
    SetAttributes(level);

    // Set random amount of money
    int m = ((rand() % 10) + 10) * level; // 10 to 20 * level
    SetMoney(m);
}

Monster::Monster(const Monster& orig) {
}

Monster::~Monster() {
}

string Monster::GetName() const {
    string name, type, status;
    switch (mt) {
        case Dragon:
            type = "Dragon";
            break;
        case Exoskeleton:
            type = "Exoskeleton";
            break;
        case Spirit:
            type = "Spirit";
            break;
    }
    switch (st) {
        case Living::Healthy:
            status = "Healthy";
            break;
        case Living::Spelled:
            status = "Spelled";
            break;
        case Living::Dead:
            status = "Dead";
            break;
    }
    name = Living::GetName() + " (" + type + ", " + status + ")";
    return name;
}

int Monster::GetAvoidChance() const {
    float calc = avoidChance;

    if (GetStatus() == Monster::Spelled)
        calc = avoidChance * (100 - decreaseAvoidChance) / 100;
    // E.g avoidChance = 20%. decreaseAvoidChance = 10%
    // We return 20 * (100 - 10)/100 = 20 * 90 / 100 = 1800 / 100 = 18
    return calc;
}

int Monster::GetDamage() const {
    float _damage;
    float hp = (float) GetHealth() / (float) GetMaxHealth(); // Health percent

    if (GetStatus() == Living::Healthy)
        _damage = damage * hp;
    else if (GetStatus() == Living::Spelled)
        _damage = (damage - decreaseDamage) * hp;

    if (_damage > 0)
        return (int) ceil(_damage);
    else
        return 0;
}

int Monster::GetDefence() const {
    float _defence;
    float hp = (float) GetHealth() / (float) GetMaxHealth(); // Health percent

    if (GetStatus() == Living::Healthy)
        _defence = defence * hp;
    else if (GetStatus() == Living::Spelled)
        _defence = (defence - decreaseDefence) * hp;

    if (_defence > 0)
        return (int) ceil(_defence);
    else
        return 0;
}

void Monster::Resurrect() {
    SetStatus(Living::Healthy);
    SetHealth(GetMaxHealth() / 2);
}

Monster::monster_t Monster::GetType() const {
    return mt;
}

//void Monster::SetStatus(status_t stat) {
//    st = stat;
//}

int Monster::Attack(Living* defender) {
    Hero* victim = (Hero*) defender; // Defender is a hero
    int protection = victim->GetProtection();
    int attackDamage; // Calculate damage

    // Attacker damage = his damage - victim's protection
    attackDamage = GetDamage() - protection;

    if (GetStatus() == Living::Spelled) {
        rounds--;
        if (rounds == 0)
            SetStatus(Living::Healthy);
    }
    if (attackDamage > 0) {
        victim->DecreaseHealth(attackDamage);
        return attackDamage;
//        if (victim->GetHealth() == 0)
//            victim->SetStatus(Living::Dead);
    }

    return 0;
}

void Monster::SetAttributes(int level) {
    switch (mt) { // Attribute values by monster type
        case Dragon:
            switch (level) {
                case 1:
                {
                    SetMaxHealth(MAX_HEALTH * 0.1);
                    IncreaseHealth(MAX_HEALTH * 0.1);
                    damage = MAX_DAMAGE * 0.1; // 10% of max value
                    defence = MAX_DEFENCE * (rand() % (level * 10) + 1) / 100;
                    avoidChance = MAX_AVOID_CHANCE * (rand() % (level * 10) + 1) / 100;
//                    damage = MAX_DAMAGE * 0.09; // 10% of max value
//                    defence = MAX_DEFENCE * (rand() % (level * 9) + 1) / 100;
//                    avoidChance = MAX_AVOID_CHANCE * (rand() % (level * 9) + 1) / 100;
                    // Gives a value between 0% and 10% of max value
                    break;
                }
                case 2:
                {
                    SetMaxHealth(MAX_HEALTH * 0.2);
                    IncreaseHealth(MAX_HEALTH * 0.2);
                    damage = MAX_DAMAGE * 0.2; // 20% of max value
                    defence = MAX_DEFENCE * (rand() % (level * 10) + 1) / 100;
                    avoidChance = MAX_AVOID_CHANCE * (rand() % (level * 10) + 1) / 100;
                    // Gives a value between 10% and 20% of max value
                    break;
                }
                case 3:
                {
                    SetMaxHealth(MAX_HEALTH * 0.4);
                    IncreaseHealth(MAX_HEALTH * 0.4);
                    damage = MAX_DAMAGE * 0.4; // 40% of max value
                    defence = MAX_DEFENCE * (rand() % (level * 10) + 1) / 100;
                    avoidChance = MAX_AVOID_CHANCE * (rand() % (level * 10) + 1) / 100;
                    // Gives a value between 20% and 40% of max value
                    break;
                }
                case 4:
                {
                    SetMaxHealth(MAX_HEALTH * 0.7);
                    IncreaseHealth(MAX_HEALTH * 0.7);
                    damage = MAX_DAMAGE * 0.7; // 70% of max value
                    defence = MAX_DEFENCE * (rand() % (level * 10) + 1) / 100;
                    avoidChance = MAX_AVOID_CHANCE * (rand() % (level * 10) + 1) / 100;
                    // Gives a value between 40% and 70% of max value
                    break;
                }
                case 5:
                {
                    SetMaxHealth(MAX_HEALTH);
                    IncreaseHealth(MAX_HEALTH);
                    damage = MAX_DAMAGE; // max value
                    defence = MAX_DEFENCE * (rand() % (level * 10) + 1) / 100;
                    avoidChance = MAX_AVOID_CHANCE * (rand() % (level * 10) + 1) / 100;
                    // Gives a value between 70% and 100% of max value
                    break;
                }
            } // End Dragon Levels
            break;
        case Exoskeleton:
            switch (level) {
                case 1:
                {
                    SetMaxHealth(MAX_HEALTH * 0.1);
                    IncreaseHealth(MAX_HEALTH * 0.1);
                    damage = MAX_DAMAGE * (rand() % (level * 10) + 1) / 100;
                    defence = MAX_DEFENCE * 0.10; // 10% of max value
                    avoidChance = MAX_AVOID_CHANCE * (rand() % (level * 10) + 1) / 100;
                    // Gives a value between 0% and 10% of max value
                    break;
                }
                case 2:
                {
                    SetMaxHealth(MAX_HEALTH * 0.2);
                    IncreaseHealth(MAX_HEALTH * 0.2);
                    damage = MAX_DAMAGE * (rand() % (level * 10) + 1) / 100;
                    defence = MAX_DEFENCE * 0.2;
                    avoidChance = MAX_AVOID_CHANCE * (rand() % (level * 10) + 1) / 100;
                    // Gives a value between 10% and 20% of max value
                    break;
                }
                case 3:
                {
                    SetMaxHealth(MAX_HEALTH * 0.4);
                    IncreaseHealth(MAX_HEALTH * 0.4);
                    damage = MAX_DAMAGE * (rand() % (level * 10) + 1) / 100;
                    defence = MAX_DEFENCE * 0.4;
                    avoidChance = MAX_AVOID_CHANCE * (rand() % (level * 10) + 1) / 100;
                    // Gives a value between 20% and 40% of max value
                    break;
                }
                case 4:
                {
                    SetMaxHealth(MAX_HEALTH * 0.7);
                    IncreaseHealth(MAX_HEALTH * 0.7);
                    damage = MAX_DAMAGE * (rand() % (level * 10) + 1) / 100;
                    defence = MAX_DEFENCE * 0.7;
                    avoidChance = MAX_AVOID_CHANCE * (rand() % (level * 10) + 1) / 100;
                    // Gives a value between 40% and 70% of max value
                    break;
                }
                case 5:
                {
                    SetMaxHealth(MAX_HEALTH);
                    IncreaseHealth(MAX_HEALTH);
                    damage = MAX_DAMAGE * (rand() % (level * 10) + 1) / 100;
                    defence = MAX_DEFENCE;
                    avoidChance = MAX_AVOID_CHANCE * (rand() % (level * 10) + 1) / 100;
                    // Gives a value between 70% and 100% of max value
                    break;
                }
            } // End of Exoskeleton levels
            break;
        case Spirit:
            switch (level) {
                case 1:
                {
                    SetMaxHealth(MAX_HEALTH * 0.1);
                    IncreaseHealth(MAX_HEALTH * 0.1);
                    damage = MAX_DAMAGE * (rand() % (level * 10) + 1) / 100;
                    defence = MAX_DEFENCE * (rand() % (level * 10) + 1) / 100;
                    avoidChance = MAX_AVOID_CHANCE * 0.1;
                    // Gives a value between 1% and 10% of max value
                    break;
                }
                case 2:
                {
                    SetMaxHealth(MAX_HEALTH * 0.2);
                    IncreaseHealth(MAX_HEALTH * 0.2);
                    damage = MAX_DAMAGE * (rand() % (level * 10) + 1) / 100;
                    defence = MAX_DEFENCE * (rand() % (level * 10) + 1) / 100;
                    avoidChance = MAX_AVOID_CHANCE * 0.2;
                    // Gives a value between 10% and 20% of max value
                    break;
                }
                case 3:
                {
                    SetMaxHealth(MAX_HEALTH * 0.4);
                    IncreaseHealth(MAX_HEALTH * 0.4);
                    damage = MAX_DAMAGE * (rand() % (level * 10) + 1) / 100;
                    defence = MAX_DEFENCE * (rand() % (level * 10) + 1) / 100;
                    avoidChance = MAX_AVOID_CHANCE * 0.4;
                    // Gives a value between 20% and 40% of max value
                    break;
                }
                case 4:
                {
                    SetMaxHealth(MAX_HEALTH * 0.7);
                    IncreaseHealth(MAX_HEALTH * 0.7);
                    damage = MAX_DAMAGE * (rand() % (level * 10) + 1) / 100;
                    defence = MAX_DEFENCE * (rand() % (level * 10) + 1) / 100;
                    avoidChance = MAX_AVOID_CHANCE * 0.7;
                    // Gives a value between 40% and 70% of max value
                    break;
                }
                case 5:
                {
                    SetMaxHealth(MAX_HEALTH);
                    IncreaseHealth(MAX_HEALTH);
                    damage = MAX_DAMAGE * (rand() % (level * 10) + 1) / 100;
                    defence = MAX_DEFENCE * (rand() % (level * 10) + 1) / 100;
                    avoidChance = MAX_AVOID_CHANCE;
                    // Gives a value between 70% and 100% of max value
                    break;
                }
            } // End of Spirit levels
            break;
    }
}

void Monster::SpellAvoidChance(float amount) {
    decreaseAvoidChance = amount;
}

void Monster::SpellDamage(int amount) {
    decreaseDamage = amount;
}

void Monster::SpellDefence(int amount) {
    decreaseDefence = amount;
}

void Monster::SpellRounds(int amount) {
    rounds = amount;
}

void Monster::DisplayInfo() const {
    cout << GetName();

    if (st == Living::Spelled)
        cout << "\tSpelled for " << rounds << " more round" << (rounds == 1 ? ")" : "s)");
    cout << "\tHealth: " << GetHealth() << "/" << GetMaxHealth();
    cout << endl;
    cout << "  Level: " << GetLevel();
    cout << ", Damage: " << GetDamage();
    cout << ", Defence: " << GetDefence();
    cout << ", Avoid Chance: " << GetAvoidChance() << "%";
    //    cout << endl;
    cout << ", Money: " << GetMoney() << endl;
}