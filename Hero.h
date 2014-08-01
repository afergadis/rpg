/* 
 * File:   Hero.h
 * 
 * Derives from class Living
 * Defines the characteristic that make a living hero.
 */

#ifndef HERO_H
#define	HERO_H

#include "Living.h"
#include "Weapon.h"
#include "Armor.h"
#include "Potion.h"
#include "Inventory.h"
//#include "Monster.h"

class Hero : public Living {
public:
    enum hero_t { // Available hero types
        Warrior, Sorcerer, Palladin
    };
    Hero();
    Hero(string n, hero_t type); // Define name on construction
    Hero(const Hero& orig);
    virtual ~Hero();

    // Method to get "physical" characteristics
    string GetName() const;
    int GetMagic() const;
    int GetMaxMagic() const;
    int GetStrength() const;
    int GetDexterity() const;
    int GetAgility() const;
    int GetExperience() const;
    hero_t GetType() const;
//    status_t GetStatus() const;
    static int GetMoney();

    // Method to set hero type
    void SetType(hero_t aType);
    void SetStatus(status_t aStatus);
//    void SetMaxHealth(int level); // overrides Living::SetMaxHealth(int amount);
    void Resurrect();
    
    // Characteristics can increase or decrease
    void IncreaseMagic(int amount);
    void DecreaseMagic(int amount);
    void IncreaseStrength(int amount);
    void IncreaseDexterity(int amount);
    void IncreaseAgility(int amount);
    void IncreaseExperience(int amount);

    // Handling static member: money
    static int IncreaseMoney(int amount); // Change money by amount and return new sum
    static int DecreaseMoney(int amount);

    // Merchancy
    // Buy: Decrease money and put item into inventory
    bool Buy(Item *newItem);
    // Sell: Remove item from inventory and increase money
    bool Sell(int itemIndex);

    // Weapons handle
    Weapon* GetLeftHandWeapon() const;
    Weapon* GetRightHandWeapon() const;
    Armor* GetArmor() const;
    // Set*HandWeapon the weapon that hero holded.
    // New weapon goes on hand, last returned as pointer for any use.
    // E.g. It can be "left" on the ground and picked up later!
    Weapon* SetLeftHandWeapon(Weapon* newWeapon);
    Weapon* SetRightHandWeapon(Weapon* newWeapon);
    Armor* SetArmor(Armor* newArmor);

    // Potion consume
    bool UsePotion(int invIndex);

    // Spells handling
    bool LearnSpell(Spell* newSpell);
    int CastSpell(Living* victim, int spellIndex);
    void DisplaySpellList();

    int GetDamage(); // Calculate the damage of the hero on an attack
    int GetProtection(); // Protection decreases damage from enemy

    int Attack(Living* defender);
    void DisplayInfo(); // Display stats about health, magic, strength etc.
    void DisplayShortInfo();

    InventoryOfItems Inventory; // Hero's inventory of items.
private:
    void SetMaxMagic(int mp);
    void SetMagic(int mp);
    void SetAttributes(int level);

    hero_t ht;
    status_t st;
    // Characteristics
    int magicPower;
    int maxMagicPower;
    int strength;
    int dexterity;
    int agility;
    int experience; // We change level according to experience points
    static int money; // All heros share money

    // The items currently in use
    Weapon* leftHand;
    Weapon* rightHand;
    Armor* wearingArmor;

    // Spell List
    enum { // Using enum instead of const int
        maxSpells = 3
    };
    Spell* spellList[maxSpells];
};

#endif	/* HERO_H */

