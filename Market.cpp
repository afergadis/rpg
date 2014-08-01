/* 
 * 
 */

#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;
using std::setiosflags;
using std::ios;

#include "Market.h"

Market::Market() {
    numOfWeapons = 9;
    WeaponsList = new Weapon[numOfWeapons];
    //                          Name                Cost    Level   Damage  Both Hands
    WeaponsList[0].CreateWeapon("Rusty Dagger", 3, 1, 2, false);
    WeaponsList[1].CreateWeapon("Dagger", 15, 1, 4, false);
    WeaponsList[2].CreateWeapon("Hatchet", 40, 1, 8, false);
    WeaponsList[3].CreateWeapon("Bronze Sword", 100, 2, 15, false);
    WeaponsList[4].CreateWeapon("Battle Axe", 220, 2, 30, true);
    WeaponsList[5].CreateWeapon("Great Sword", 400, 3, 50, false);
    WeaponsList[6].CreateWeapon("Master Sword", 750, 3, 90, true);
    WeaponsList[7].CreateWeapon("XCalibur", 1700, 4, 150, true);
    WeaponsList[8].CreateWeapon("Sword of Legends", 4000, 5, 200, false);

    numOfArmory = 6;
    ArmorList = new Armor[numOfArmory];
    //                       Name               Cost    Level   Protection
    ArmorList[0].CreateArmor("Cloth", 10, 1, 1);
    ArmorList[1].CreateArmor("Leather", 50, 1, 3);
    ArmorList[2].CreateArmor("Chain Mail", 180, 2, 10);
    ArmorList[3].CreateArmor("Plate", 600, 3, 20);
    ArmorList[4].CreateArmor("Dragon Scale", 2000, 4, 50);
    ArmorList[5].CreateArmor("Legendary", 5000, 5, 100);

    numOfPotions = 9;
    PotionsList = new Potion[numOfPotions];
    //                          Name                    Cost    Level   Health  Magic
    PotionsList[0].CreatePotion("Small Heal Potion", 5, 1, 10, 0);
    PotionsList[1].CreatePotion("Large Heal Potion", 20, 2, 50, 0);
    PotionsList[2].CreatePotion("Elixer of Life", 100, 3, 100, 0);
    PotionsList[3].CreatePotion("Small Magic Potion", 5, 1, 0, 10);
    PotionsList[4].CreatePotion("Large Magic Potion", 20, 2, 0, 50);
    PotionsList[5].CreatePotion("Elixer of Magic", 100, 3, 0, 100);
    PotionsList[6].CreatePotion("Small Combined Potion", 25, 2, 10, 10);
    PotionsList[7].CreatePotion("Large Combined Potion", 50, 3, 40, 40);
    PotionsList[8].CreatePotion("Resurrection", 200, 5, 100, 100);

    numOfSpells = 3;
    SpellsList = new Spell[numOfSpells];
    //                        Name,             Cost    Level   Magic   Damage  Rounds  Damage- Defence- AvoidChance- (%)
    SpellsList[0].CreateSpell("Ice Spell", 50, 1, 20, 20, 2, 10, 5, 15);
    SpellsList[1].CreateSpell("Fire Spell", 60, 3, 50, 40, 3, 20, 10, 30);
    SpellsList[2].CreateSpell("Lighting Spell", 70, 4, 80, 50, 4, 25, 20, 50);
}

Market::Market(const Market& orig) {
}

Market::~Market() {
}

Item* Market::GetItem(char what, int which) {
    switch (what) { // What do you want to get?
        case 'W': case 'w':
            if (which > 0 && which <= numOfWeapons) {
                // User uses numbers 1..numOfWeapons
                // Make a copy of item in list
                Weapon* weaponToReturn = new Weapon(WeaponsList[which - 1]);
                return weaponToReturn;
            }
            break;
        case 'A': case 'a':
            if (which > 0 && which <= numOfArmory) {
                Armor* armorToReturn = new Armor(ArmorList[which - 1]);
                return armorToReturn;
            }
            break;
        case 'P': case 'p':
            if (which > 0 && which <= numOfPotions) {
                Potion* potionToReturn = new Potion(PotionsList[which - 1]);
                return potionToReturn;
            }
            break;
    }
    return 0;
}

Spell* Market::GetSpell(int which) {
    if (which > 0 && which <= numOfSpells) {
        Spell *spell = new Spell(SpellsList[which - 1]);
        return spell;
    }

    return 0;
}

void Market::DisplayItems() {
    DisplayWeapons();
    DisplayArmory();
    DisplayPotions();
    DisplaySpells();
}

void Market::DisplayWeapons() {
    for (int i = 0; i < numOfWeapons; i++) {
        cout << setiosflags(ios::right) << setw(2) << i + 1 << ": ";
        WeaponsList[i].DisplayInfo();
        cout << endl;
    }
}

void Market::DisplayArmory() {
    for (int i = 0; i < numOfArmory; i++) {
        cout << setiosflags(ios::right) << setw(2) << i + 1 << ": ";
        ArmorList[i].DisplayInfo();
        cout << endl;
    }
}

void Market::DisplayPotions() {
    for (int i = 0; i < numOfPotions; i++) {
        cout << setiosflags(ios::right) << setw(2) << i + 1 << ": ";
        PotionsList[i].DisplayInfo();
        cout << endl;
    }
}

void Market::DisplaySpells() {
    for (int i = 0; i < numOfSpells; i++) {
        cout << setiosflags(ios::right) << setw(2) << i + 1 << ": ";
        SpellsList[i].DisplayInfo();
        cout << endl;
    }
}