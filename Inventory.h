/* 
 * File:   Inventory.h
 *
 * This class defines the inventory of a hero.
 * An inventory contains items.
 */

#ifndef INVENTORY_H
#define	INVENTORY_H

#include "Item.h"

class InventoryOfItems {
public:
    InventoryOfItems(int c = 10);
    ~InventoryOfItems();

    bool Add(Item* newItem);
    Item* Remove(int itemIndex);
    Item* Exchange(Item* itemToExchange, int invIndex);
    const Item* Examine(int invIndex);
    int Size() const;
    int Items() const;
    int Weapons() const; // Return the number of items per type
    int Armors() const;
    int Potions() const;
    Item::item_t GetItemType(int invIndex) const;

    void DisplayWeapons();
    void DisplayArmors();
    void DisplayPotions();
    void DisplayInfo();
private:
    Item** items;
    int itemCount;
    int capacity;
};

#endif	/* INVENTORY_H */

