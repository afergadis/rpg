/* 
 * File:   Potion.h
 * 
 * Derive from class Item.
 * Defines the item type: Potion
 */

#ifndef POTION_H
#define	POTION_H

#include "Item.h"

class Potion : public Item {
public:
    Potion();
    Potion(Item i, int hp, int mp);
    Potion(Potion* otherPotion);
    Potion(string n, int c, int l, int hp, int mp);
    Potion(const Potion& orig);
    virtual ~Potion();

    void CreatePotion(string n, int c, int l, int hp, int mp);

    int GetHealthPower() const;
    void SetHealthPower(int hp);

    int GetMagicPower() const;
    void SetMagicPower(int mp);

    void DisplayInfo();
private:
    int healthPower; // ζωτική ενέργεια
    int magicPower; // μαγινή ενέργεια
};

#endif	/* POTION_H */

