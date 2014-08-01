/* 
 * 
 */

#include <iostream>
#include "Spell.h"
using namespace::std;

Spell::Spell() {
    name = "Undefined";
    cost = 0;
    level = 0;
    magicPower = 0;
    damage = 0;
    rounds = 0;
    decreaseDamage = 0;
    decreaseDefense = 0;
    decreaseAvoidChance = 0;
}

Spell::Spell(const Spell* otherSpell) {
    decreaseAvoidChance = otherSpell->GetAvoidChanceEffect();
    cost = otherSpell->GetCost();
    damage = otherSpell->GetDamage();
    decreaseDefense = otherSpell->GetDefenceEffect();
    level = otherSpell->GetLevel();
    magicPower = otherSpell->GetMagicPower();
    name = otherSpell->GetName();
    rounds = otherSpell->GetRounds();
    decreaseDamage = otherSpell->GetDamageEffect();
}

Spell::Spell(const Spell& orig) {
    name = orig.GetName();
    cost = orig.GetCost();
    level = orig.GetLevel();
    magicPower = orig.GetMagicPower();
    damage = orig.GetDamage();
    rounds = orig.GetRounds();
    decreaseDamage = orig.GetDamageEffect();
    decreaseDefense = orig.GetDefenceEffect();
    decreaseAvoidChance = orig.GetAvoidChanceEffect();
}

Spell::~Spell() {
}

void Spell::CreateSpell(string n, int c, int l, int mp, int d, int r, int dam, int def, int av) {
    SetName(n);
    SetCost(c);
    SetLevel(l);
    SetMagicPower(mp);
    SetDamage(d);
    SetRounds(r);
    SetDamageEffect(dam);
    SetDefenceEffect(def);
    SetAvoidChanceEffect(av);
}

float Spell::GetAvoidChanceEffect() const {
    return decreaseAvoidChance;
}

void Spell::SetAvoidChanceEffect(float a) {
    if (a > 0)
        decreaseAvoidChance = a;
}

int Spell::GetCost() const {
    return cost;
}

void Spell::SetCost(int c) {
    if (c > 0)
        cost = c;
}

int Spell::GetDamage() const {
    return damage;
}

void Spell::SetDamage(int d) {
    if (d > 0)
        damage = d;
}

int Spell::GetDefenceEffect() const {
    return decreaseDefense;
}

void Spell::SetDefenceEffect(int d) {
    if (d > 0)
        decreaseDefense = d;
}

int Spell::GetLevel() const {
    return level;
}

void Spell::SetLevel(int l) {
    if (l > 0)
        level = l;
}

int Spell::GetMagicPower() const {
    return magicPower;
}

void Spell::SetMagicPower(int mp) {
    if (mp > 0)
        magicPower = mp;
}

string Spell::GetName() const {
    return name;
}

void Spell::SetName(string n) {
    name = n;
}

int Spell::GetRounds() const {
    return rounds;
}

void Spell::SetRounds(int r) {
    if (r > 0)
        rounds = r;
}

int Spell::GetDamageEffect() const {
    return decreaseDamage;
}

void Spell::SetDamageEffect(int s) {
    if (s > 0)
        decreaseDamage = s;
}

void Spell::DisplayInfo() {
    cout << name << endl;
    cout << "  Cost: " << cost;
    cout << ", Level: " << level;
    cout << ", Consumes Magic: " << magicPower;
    cout << ", Causes Damage: " << damage;
    cout << ", Effects " << rounds << " round" << (rounds == 1 ? "" : "s");
    cout << endl;
    cout << "  Decreases enemy's Damage by " << decreaseDamage;
    cout << ", Defense by " << decreaseDefense;
    cout << ", Avoid Chance by " << decreaseAvoidChance << "%";
    cout << endl;
}