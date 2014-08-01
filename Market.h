/* 
 *
 */

#ifndef MARKET_H
#define	MARKET_H

#include "Item.h"
#include "Weapon.h"
#include "Armor.h"
#include "Potion.h"
#include "Spell.h"

class Market {
public:
    Market();
    Market(const Market& orig);
    virtual ~Market();

    Item* GetItem(char what, int which);
    Spell* GetSpell(int which);

    void DisplayItems(); // όλα τα αντικείμενα
    void DisplayWeapons();
    void DisplayArmory();
    void DisplayPotions();
    void DisplaySpells();
private:
    int numOfWeapons;
    int numOfArmory;
    int numOfPotions;
    int numOfSpells;
    Weapon* WeaponsList;
    Armor *ArmorList;
    Potion *PotionsList;
    Spell *SpellsList;
};

#endif	/* MARKET_H */

