/* 
 * 
 */

#include <iostream>
using std::cout;

#include "Item.h"

Item::Item() {
    name = "Undefined";
    cost = 0;
    level = 0;
    it = Undefined;
}

Item::Item(string n, int c, int l) {
    name = n;
    cost = c;
    level = l;
    it = Undefined;
}

Item::Item(const Item* newItem) {
    SetName(newItem->GetName());
    SetCost(newItem->GetCost());
    SetLevel(newItem->GetLevel());
    SetType(newItem->GetType());
}

Item::Item(const Item& orig) {
    name = orig.name;
    cost = orig.cost;
    level = orig.level;
    it = orig.it;
}

Item::~Item() {
}

string Item::GetName() const {
    return name;
}

void Item::SetName(const string &aName) {
    name = aName;
}

int Item::GetCost() const {
    return cost;
}

void Item::SetCost(int c) {
    if (c > 0)
        cost = c;
}

int Item::GetLevel() const {
    return level;
}

void Item::SetLevel(int l) {
    if (l > 0)
        level = l;
}

Item::item_t Item::GetType() const {
    return it;
}

void Item::SetType(item_t aType) {
    it = aType;
}

void Item::DisplayInfo() {
    cout << name;
    cout << ", Level: " << level;
    cout << ", Cost (buy): " << cost;
}





