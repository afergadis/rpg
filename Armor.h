/* 
 * File:   Armor.h
 * 
 * Derive from class Item.
 * Defines the item type: Armor
 */

#ifndef ARMOR_H
#define	ARMOR_H

#include "Item.h"

class Armor : public Item {
public:
    Armor();
    Armor(Item i, int p);
    Armor(const Armor* otherArmor);
    Armor(string n, int c, int l, int p);
    Armor(const Armor& orig);
    virtual ~Armor();

    void CreateArmor(string n, int c, int l, int p);

    int GetProtection() const;
    void SetProtection(int p);

    void DisplayInfo();
private:
    int protection;
};

#endif	/* ARMOR_H */

