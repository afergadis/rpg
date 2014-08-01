/* 
 * 
 */

#include <ctime>
#include <iostream>
using std::cout;

#include <iomanip>
using std::setw;
using std::setiosflags;
using std::ios;

#include "Living.h"
#include "Item.h"
#include "Weapon.h"

Living::Living() {
    name = "Undefined";
    st = Living::Healthy;
    level = 1;
    healthPower = 0;
    maxHealthPower = 0;
    money = 0;
}

Living::Living(string n) {
    name = n;
    st = Living::Healthy;
    level = 1;
    healthPower = 0;
    maxHealthPower = 0;
    money = 0;
}

Living::Living(const Living& orig) {
    name = orig.GetName();
    st = orig.GetStatus();
    level = orig.GetLevel();
    healthPower = orig.GetHealth();
    maxHealthPower = orig.GetMaxHealth();
    money = orig.GetMoney();
}

Living::Living(const Living* orig) {
    name = orig->GetName();
    st = orig->GetStatus();
    level = orig->GetLevel();
    healthPower = orig->GetHealth();
    maxHealthPower = orig->GetMaxHealth();
    money = orig->GetMoney();
}

Living::~Living() {
}

string Living::GetName() const {
    return name;
}

int Living::GetLevel() const {
    return level;
}

int Living::GetHealth() const {
    return healthPower;
}

int Living::GetMaxHealth() const {
    return maxHealthPower;
}

int Living::GetMoney() const {
    return money;
}

Living::status_t Living::GetStatus() const {
    return st;
}

void Living::SetName(string n) {
    name = n;
}

void Living::SetLevel(int l) {
    if (l > 0 && l < 6)
        level = l;
}

void Living::SetStatus(status_t status) {
    st = status;
}

void Living::IncreaseHealth(int h) {
    if (st == Living::Dead) // It's dead, don't increase health
        return;
    
    if (h > 0) {
        if (healthPower + h < maxHealthPower) // Increase to maxHealthPower
            healthPower += h;
        else
            healthPower = maxHealthPower;
    }
}

void Living::DecreaseHealth(int h) {
    if (h >= 0) {
        if (healthPower - h < 0) {
            healthPower = 0;    // 0 health power for dead living being
            SetStatus(Living::Dead);
        }
        else
            healthPower -= h;
    }
}

void Living::SetHealth(int hp) {
    if (hp >= 0)
        healthPower = hp;
}

void Living::SetMaxHealth(int mh) {
    if (mh >= 0)
        maxHealthPower = mh;
}

void Living::Resurrect() {
    healthPower = 1;
    SetStatus(Living::Healthy);
}

void Living::SetMoney(int amount) {
    if (amount >= 0)
        money = amount;
}

void Living::DisplayInfo() {
    cout << setiosflags(ios::left) << setw(15) << name
            << "\tLevel: " << level
            << "\tHealth: " << healthPower << "/" << maxHealthPower
            << "\tMoney: " << money;
}
