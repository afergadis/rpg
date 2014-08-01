/*
 *
 */

#include "Inventory.h"
#include "Weapon.h"
#include "Armor.h"
#include "Potion.h"

#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;
using std::setiosflags;
using std::ios;

#include <string>

InventoryOfItems::InventoryOfItems(int cap) {
    itemCount = 0;
    capacity = cap;
    // Allocate memory for an array of *capacity* pointers to items
    items = new Item*[capacity];
    // Initialize each pointer to 0 (NULL)
    for (int i = 0; i < capacity; i++) {
        items[i] = 0;
    }
}

InventoryOfItems::~InventoryOfItems() {
    // Delete all pointers of the array
    for (int i = 0; i < itemCount; i++) {
        delete items[i];
    }
    // Delete the array
    delete [] items;
}

bool InventoryOfItems::Add(Item* newItem) {
    // If newItem is NULL, no need to put anything
    if (newItem == 0)
        return false;

    // Find an empty slot
    for (int i = 0; i < capacity; i++)
        if (items[i] == 0) { // empty
            switch (newItem->GetType()) { // Add an item according to it's type
                case Item::Weapon:
                {
                    /*
                     * newItem is a pointer to a Weapon.
                     * We cast it to get a pointer to that Weapon
                     */
                    Weapon* originalWeapon = (Weapon*) newItem;
                    /*
                     * We have to make a new weapon in order to copy the info
                     * from the original (newItem)
                     */
                    Weapon* newWeapon = new Weapon(originalWeapon);
                    /*
                     * Now we can put the copied weapon into inventory
                     */
                    items[i] = newWeapon;
                    itemCount++;
                    break;
                }
                case Item::Armor:
                {
                    Armor* originalArmor = (Armor*) newItem;
                    Armor* newArmor = new Armor(originalArmor);
                    items[i] = newArmor;
                    itemCount++;
                    break;
                }
                case Item::Potion:
                {
                    Potion* originalPotion = (Potion*) newItem;
                    Potion* newPotion = new Potion(originalPotion);
                    items[i] = newPotion;
                    itemCount++;
                    break;
                }
            }
            return true; // Success: added.
        }

    return false; // Full inventory
}

Item* InventoryOfItems::Remove(int itemIndex) {
    if (items[itemIndex - 1] == 0) // Trying to remove a non existing item
        return 0;
    else {
        Item* itemToReturn; // Return a pointer to the inventory item
        itemToReturn = items[itemIndex - 1]; // Points to the inventory item
        items[itemIndex - 1] = 0; // Doesn't point to an item any more
        itemCount--;
        return itemToReturn;
    }
}

Item* InventoryOfItems::Exchange(Item* itemToExchange, int invIndex) {
    // Exchange the item in invIndex position with itemToExchange
    Item* itemOnInventory = Remove(invIndex - 1);
    Add(itemToExchange);

    return itemOnInventory;
}

/*
 * Returns a pointer to the invIndex item in order to examine (get info from it)
 * The item remains on inventory and we don't want any modification.
 * So we return a const pointer to it.
 */
const Item* InventoryOfItems::Examine(int invIndex) {
    return items[invIndex - 1];
}

int InventoryOfItems::Size() const {
    return capacity;
}

int InventoryOfItems::Items() const {
    return itemCount;
}

int InventoryOfItems::Weapons() const {
    int count = 0;
    for (int i = 0; i < capacity; i++)
        if (items[i] != 0)
            if (items[i]->GetType() == Item::Weapon)
                count++;

    return count;
}

int InventoryOfItems::Armors() const {
    int count = 0;
    for (int i = 0; i < capacity; i++)
        if (items[i] != 0)
            if (items[i]->GetType() == Item::Armor)
                count++;

    return count;
}

int InventoryOfItems::Potions() const {
    int count = 0;
    for (int i = 0; i < capacity; i++)
        if (items[i] != 0)
            if (items[i]->GetType() == Item::Potion)
                count++;

    return count;
}

Item::item_t InventoryOfItems::GetItemType(int invIndex) const {
    if (items[invIndex - 1] == 0)
        return Item::Undefined;
    else
        return items[invIndex - 1]->GetType();
}

void InventoryOfItems::DisplayWeapons() {
    cout << "  WEAPONS" << endl;
    for (int i = 0; i < capacity; i++)
        if (items[i] != NULL)
            if (items[i]->GetType() == Item::Weapon) {
                cout << "    " << setiosflags(ios::right) << setw(2) << i + 1 << ": ";
                items[i]->DisplayInfo(); // Calls the Weapon::DisplayInfo()
                cout << endl;
            }
}

void InventoryOfItems::DisplayArmors() {
    cout << "  ARMORS" << endl;
    for (int i = 0; i < capacity; i++)
        if (items[i] != NULL)
            if (items[i]->GetType() == Item::Armor) { // and it is an armor
                cout << "    " << setiosflags(ios::right) << setw(2) << i + 1 << ": ";
                items[i]->DisplayInfo();
                cout << endl;
            }
}

void InventoryOfItems::DisplayPotions() {
    cout << "  POTIONS" << endl;
    for (int i = 0; i < capacity; i++)
        if (items[i] != NULL)
            if (items[i]->GetType() == Item::Potion) { // and it is a potion
                cout << "    " << setiosflags(ios::right) << setw(2) << i + 1 << ": ";
                items[i]->DisplayInfo();
                cout << endl;
            }
}

void InventoryOfItems::DisplayInfo() {
    cout << endl;
    cout << "  ----------------------------------" << endl;
    cout << "  Inventory (carrying " << itemCount << " of " << capacity << " items)" << endl;
    cout << "  ----------------------------------" << endl;

    DisplayWeapons();
    DisplayArmors();
    DisplayPotions();
}
