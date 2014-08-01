/* 
 * File:   Weapon.h
 *
 * Derive from class Item.
 * Defines the item type: Weapon
 */

#ifndef WEAPON_H
#define	WEAPON_H

#include "Item.h"

class Weapon : public Item {
public:
    Weapon();
    Weapon(Item i, int d, bool bh); // Create a weapon from an existing item.
    Weapon(string n, int c, int l, int d, bool bh);
    Weapon(const Weapon* otherWeapon); // Copy constructor
    Weapon(const Weapon& orig); // Copy constructor
    virtual ~Weapon();

    void CreateWeapon(string n, int c, int l, int d, bool bh); // Avoid calling every set function

    int GetDamage() const;
    void SetDamage(int d);

    void DisplayInfo();
    bool bothHands; // Αν χρειάζεται και τα δύο χέρια για χρήση
private:
    int damage; // Ζημιά που προκαλεί
};

#endif	/* WEAPON_H */

