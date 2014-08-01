/* 
 * 
 */
#include <iostream>
using std::cout;
using std::endl;

#include "Armor.h"

Armor::Armor() {
    protection = 0;
    SetType(Item::Armor);
}

Armor::Armor(Item i, int p) : Item(i) {
    protection = p;
    SetType(Item::Armor);
}

Armor::Armor(const Armor& orig) {
    SetName(orig.GetName());
    SetCost(orig.GetCost());
    SetLevel(orig.GetLevel());
    SetType(orig.GetType());
    SetProtection(orig.GetProtection());
}

Armor::Armor(const Armor* otherArmor) {
    SetName(otherArmor->GetName());
    SetCost(otherArmor->GetCost());
    SetLevel(otherArmor->GetLevel());
    SetType(otherArmor->GetType());
    SetProtection(otherArmor->GetProtection());
}

Armor::Armor(string n, int c, int l, int p) : Item(n, c, l) {
    protection = p;
    SetType(Item::Armor);
}

Armor::~Armor() {
}

int Armor::GetProtection() const {
    return protection;
}

void Armor::SetProtection(int p) {
    if (p > 0)
        protection = p;
}

void Armor::CreateArmor(string n, int c, int l, int p) {
    SetName(n);
    SetCost(c);
    SetLevel(l);
    SetProtection(p);
    SetType(Item::Armor);
}

void Armor::DisplayInfo() {
    Item::DisplayInfo();
    cout << ", Protection: " << protection;
}
