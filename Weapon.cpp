/* 
 * File:   Weapon.cpp
 * Methods of class Weapon
 */
#include <iostream>
using std::cout;
using std::endl;

#include "Weapon.h"

Weapon::Weapon() {
    damage = 0;
    bothHands = false;
    SetType(Item::Weapon);
}

Weapon::Weapon(const Weapon* otherWeapon) {
    SetName(otherWeapon->GetName());
    SetCost(otherWeapon->GetCost());
    SetLevel(otherWeapon->GetLevel());
    SetType(Item::Weapon);
    damage = otherWeapon->GetDamage();
    bothHands = otherWeapon->bothHands;
}

Weapon::Weapon(const Weapon& orig) {
    SetName(orig.GetName());
    SetCost(orig.GetCost());
    SetLevel(orig.GetLevel());
    SetType(orig.GetType());
    damage = orig.GetDamage();
    bothHands = orig.bothHands;
}

Weapon::Weapon(Item i, int d, bool bh) : Item(i) {
    damage = d;
    bothHands = bh;
    SetType(Item::Weapon);
}

Weapon::Weapon(string n, int c, int l, int d, bool bh) : Item(n, c, l) {
    damage = d;
    bothHands = bh;
    SetType(Item::Weapon);
}

Weapon::~Weapon() {
}

int Weapon::GetDamage() const {
    return damage;
}

void Weapon::SetDamage(int d) {
    if (d > 0)
        damage = d;
}

void Weapon::CreateWeapon(string n, int c, int l, int d, bool bh) {
    SetName(n);
    SetCost(c);
    SetLevel(l);
    SetDamage(d);
    SetType(Item::Weapon);
    bothHands = bh;
}

void Weapon::DisplayInfo() {
    //cout << "WEAPON: ";
    Item::DisplayInfo();
    cout << ", Damage: " << damage;
    if (bothHands)
        cout << ", Needs both hands";
}
