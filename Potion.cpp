/* 
 * 
 */
#include <iostream>
using std::cout;
using std::endl;

#include "Potion.h"

Potion::Potion() {
    healthPower = 0;
    magicPower = 0;
    SetType(Item::Potion);
}

Potion::Potion(Item i, int hp, int mp) : Item(i) {
    healthPower = hp;
    magicPower = mp;
    SetType(Item::Potion);
}

Potion::Potion(const Potion& orig) {
    SetName(orig.GetName());
    SetCost(orig.GetCost());
    SetLevel(orig.GetLevel());
    SetType(orig.GetType());
    SetHealthPower(orig.GetHealthPower());
    SetMagicPower(orig.GetMagicPower());
}

Potion::Potion(Potion* otherPotion) {
    SetName(otherPotion->GetName());
    SetCost(otherPotion->GetCost());
    SetLevel(otherPotion->GetLevel());
    SetType(otherPotion->GetType());
    SetHealthPower(otherPotion->GetHealthPower());
    SetMagicPower(otherPotion->GetMagicPower());
}

Potion::Potion(string n, int c, int l, int hp, int mp) : Item(n, c, l) {
    healthPower = hp;
    magicPower = mp;
    SetType(Item::Potion);
}

Potion::~Potion() {
}

void Potion::CreatePotion(string n, int c, int l, int hp, int mp) {
    SetName(n);
    SetCost(c);
    SetLevel(l);
    healthPower = hp;
    magicPower = mp;
    SetType(Item::Potion);
}

int Potion::GetHealthPower() const {
    return healthPower;
}

void Potion::SetHealthPower(int hp) {
    if (hp >= 0)
        healthPower = hp;
}

int Potion::GetMagicPower() const {
    return magicPower;
}

void Potion::SetMagicPower(int mp) {
    if (mp >= 0)
        magicPower = mp;
}

void Potion::DisplayInfo() {
    Item::DisplayInfo();
    cout << ", Health " << healthPower;
    cout << ", Magic " << magicPower;
}
