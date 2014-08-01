/* 
 * 
 */

#define INVENTORY_ITEMS 10

#define MAX_HEALTH 300
#define MAX_MAGIC 300
#define MAX_STRENGTH 100
#define MAX_DEXTERITY 100
#define MAX_AGILITY 100

#define WARRIOR_MAX_HEALTH_PERCENT 1
#define SORCERER_MAX_HEALTH_PERCENT 0.7
#define PALLADIN_MAX_HEALTH_PERCENT 1

#define WARRIOR_MAX_MAGIC_PERCENT 0.5 // Warrior can reach magic power to MAX_MAGIC / 2
#define SORCERER_MAX_MAGIC_PERCENT 1
#define PALLADIN_MAX_MAGIC_PERCENT 0.75 // Paladin can reach to 2/3 of MAX_MAGIC

#define WARRIOR_MAX_STRENGTH_PERCENT 1
#define SORCERER_MAX_STRENGTH_PERCENT 0.7
#define PALLADIN_MAX_STRENGTH_PERCENT 1

#define WARRIOR_MAX_DEXTERITY_PERCENT 0.7
#define SORCERER_MAX_DEXTERITY_PERCENT 1
#define PALLADIN_MAX_DEXTERITY_PERCENT 1

#define WARRIOR_MAX_AGILITY_PERCENT 1
#define SORCERER_MAX_AGILITY_PERCENT 1
#define PALLADIN_MAX_AGILITY_PERCENT 0.7

#include <stdlib.h>
#include <math.h>
#include <iostream>
using std::cout;
using std::cin;
using std::endl;

#include <iomanip>
using std::setw;
using std::setiosflags;
using std::ios;

#include "Hero.h"
#include "Monster.h"

// Initializing static member: money
int Hero::money = 50;

Hero::Hero() {
    // Random name and type
    char name[][15] = {"Abbathor", "Brandobaris", "Cyrrollalee", "Dumathoin",
        "Ehlonna", "Gadhelyn", "Heironeous", "Pelor", "Urogalan", "Hruggek"};
    int n = rand() % 10;
    SetName(name[n]);

    int t = rand() % 3;
    switch (t) {
        case 0:
            ht = Warrior;
            break;
        case 1:
            ht = Palladin;
            break;
        case 2:
            ht = Sorcerer;
            break;
    };
    st = Living::Healthy;

    magicPower = 0;
    experience = 1;
    SetAttributes(1); // Initial values for level 1

    for (int i = 0; i < maxSpells; i++)
        spellList[i] = 0; // An empty spell list

    // Give something to start with
    switch (ht) {
        case Warrior:
            leftHand = new Weapon("Rusty Dager", 0, 1, 2, false);
            rightHand = 0;
            wearingArmor = 0;
            break;
        case Palladin:
            rightHand = 0;
            leftHand = 0;
            wearingArmor = new Armor("Cloth", 10, 1, 1);
            break;
        case Sorcerer:
            rightHand = 0;
            leftHand = 0;
        {
            Potion* hp = new Potion("Small Heal Potion", 5, 1, 10, 0);
            Potion* mp = new Potion("Small Magic Potion", 5, 1, 0, 10);
            Inventory.Add(hp);
            Inventory.Add(mp);
            delete hp; // Inventory's Add has copied item
            delete mp;
        }
            break;
    }
}

Hero::Hero(string n, hero_t type) : Living(n) {
    SetName(n);
    SetType(type);
    st = Living::Healthy;

    magicPower = 0;
    experience = 1;
    SetAttributes(1); // Initial values for level 1

    for (int i = 0; i < maxSpells; i++)
        spellList[i] = 0; // An empty spell list

    // Give something to start with
    switch (ht) {
        case Warrior:
            leftHand = new Weapon("Rusty Dager", 0, 1, 2, false);
            rightHand = 0;
            wearingArmor = 0;
            break;
        case Palladin:
            rightHand = 0;
            leftHand = 0;
            wearingArmor = new Armor("Cloth", 10, 1, 1);
            break;
        case Sorcerer:
            rightHand = 0;
            leftHand = 0;
        {
            Potion* hp = new Potion("Small Heal Potion", 5, 1, 10, 0);
            Potion* mp = new Potion("Small Magic Potion", 5, 1, 0, 10);
            Inventory.Add(hp);
            Inventory.Add(mp);
            delete hp;
            delete mp;
        }
            break;
    }
}

Hero::Hero(const Hero& orig) {
}

Hero::~Hero() {
    delete rightHand;
    delete leftHand;
    delete wearingArmor;
    for (int i = 0; i < 2; i++)
        if (spellList[i])
            delete spellList[i]; // Delete allocated memory for spell
}

string Hero::GetName() const {
    string name, type, status;
    switch (ht) {
        case Hero::Warrior:
            type = "Warrior";
            break;
        case Hero::Sorcerer:
            type = "Sorcerer";
            break;
        case Hero::Palladin:
            type = "Palladin";
            break;
    }
    switch (GetStatus()) {
        case Living::Healthy:
            status = "Healthy";
            break;
        case Living::Spelled:
            status = "Spelled";
            break;
        case Living::Dead:
            status = "Dead";
            break;
    }
    name = Living::GetName() + " (" + type + ", " + status + ")";
    return name;
}

int Hero::GetMagic() const {
    return magicPower;
}

int Hero::GetMaxMagic() const {
    return maxMagicPower;
}

int Hero::GetStrength() const {
    //TODO: Sum weapons
    return strength;
}

int Hero::GetDexterity() const {
    return dexterity;
}

int Hero::GetAgility() const {
    return agility;
}

int Hero::GetExperience() const {
    return experience;
}

Hero::hero_t Hero::GetType() const {
    return ht;
}


int Hero::GetMoney() {
    return money;
}

void Hero::SetType(hero_t aType) {
    ht = aType;
}

void Hero::SetMagic(int amount) {
    if (amount >= 0)
        magicPower = amount;
}

void Hero::Resurrect() {
    Living::SetStatus(Living::Healthy);
    SetHealth(GetMaxHealth() / 2);
    SetMagic(GetMaxMagic() / 2);
}

void Hero::SetMaxMagic(int mp) {
    if (mp >= 0)
        maxMagicPower = mp;
}

void Hero::SetAttributes(int level) {
    float lp; // Level percent
    switch (level) {
        case 1:
            lp = 0.1;
            break;
        case 2:
            lp = 0.2;
            break;
        case 3:
            lp = 0.4;
            break;
        case 4:
            lp = 0.7;
            break;
        default:
            lp = 1;
            break;
    }

    switch (ht) { // Hero type
        case Warrior:
            SetMaxHealth(MAX_HEALTH * WARRIOR_MAX_HEALTH_PERCENT * lp);
            IncreaseHealth(MAX_HEALTH * WARRIOR_MAX_HEALTH_PERCENT * lp);
            SetMaxMagic(MAX_MAGIC * WARRIOR_MAX_MAGIC_PERCENT * lp);
            IncreaseMagic(MAX_MAGIC * WARRIOR_MAX_MAGIC_PERCENT * lp);
            strength = MAX_STRENGTH * WARRIOR_MAX_STRENGTH_PERCENT * lp;
            dexterity = MAX_DEXTERITY * WARRIOR_MAX_DEXTERITY_PERCENT * lp;
            agility = MAX_AGILITY * WARRIOR_MAX_AGILITY_PERCENT * lp;
            break;
        case Palladin:
            SetMaxHealth(MAX_HEALTH * PALLADIN_MAX_HEALTH_PERCENT * lp);
            IncreaseHealth(MAX_HEALTH * PALLADIN_MAX_HEALTH_PERCENT * lp);
            SetMaxMagic(MAX_MAGIC * PALLADIN_MAX_MAGIC_PERCENT * lp);
            IncreaseMagic(MAX_MAGIC * PALLADIN_MAX_MAGIC_PERCENT * lp);
            strength = MAX_STRENGTH * PALLADIN_MAX_STRENGTH_PERCENT * lp;
            dexterity = MAX_DEXTERITY * PALLADIN_MAX_DEXTERITY_PERCENT * lp;
            agility = MAX_AGILITY * PALLADIN_MAX_AGILITY_PERCENT * lp;
            break;
        case Sorcerer:
            SetMaxHealth(MAX_HEALTH * SORCERER_MAX_HEALTH_PERCENT * lp);
            IncreaseHealth(MAX_HEALTH * SORCERER_MAX_HEALTH_PERCENT * lp);
            SetMaxMagic(MAX_MAGIC * SORCERER_MAX_MAGIC_PERCENT * lp);
            IncreaseMagic(MAX_MAGIC * SORCERER_MAX_MAGIC_PERCENT * lp);
            strength = MAX_STRENGTH * SORCERER_MAX_STRENGTH_PERCENT * lp;
            dexterity = MAX_DEXTERITY * SORCERER_MAX_DEXTERITY_PERCENT * lp;
            agility = MAX_AGILITY * SORCERER_MAX_AGILITY_PERCENT * lp;
            break;
    }
}

void Hero::IncreaseExperience(int amount) {
    if (amount > 0)
        experience += amount;
    // Define level from experience. Μαζί αυξάνει και το maxHealthPower
    if (experience > 999) {
        SetLevel(5);
        SetAttributes(5);
    } else if (experience > 599) {
        SetLevel(4);
        SetAttributes(4);
    } else if (experience > 299) {
        SetLevel(3);
        SetAttributes(3);
    } else if (experience > 99) {
        SetLevel(2);
        SetAttributes(2);
    }
}

// When we increase a characteristic, we check not to overcome it's level max value

void Hero::IncreaseMagic(int amount) {
    if (amount > 0) {
        if (magicPower + amount > maxMagicPower)
            magicPower = maxMagicPower;
        else
            magicPower += amount;
    }
}

void Hero::DecreaseMagic(int amount) {
    if (amount > 0) {
        if (magicPower - amount < 0)
            magicPower = 0;
        else
            magicPower -= amount;
    }
}

void Hero::IncreaseStrength(int amount) {
    if (amount > 0)
        strength += amount;
}

void Hero::IncreaseDexterity(int amount) {
    if (amount > 0)
        dexterity += amount;
}

void Hero::IncreaseAgility(int amount) {
    if (amount > 0)
        agility += amount;
}

int Hero::IncreaseMoney(int amount) {
    if (amount > 0)
        money += amount;
    return money;
}

int Hero::DecreaseMoney(int amount) {
    if (amount > 0) {
        if (money - amount < 0)
            money = 0;
        else
            money -= amount;
    }

    return money;
}

bool Hero::Buy(Item* newItem) {
    // Can we afford to buy?
    if (newItem->GetCost() > GetMoney())
        return false; // NO!

    // Is there space into inventory?
    if (!Inventory.Add(newItem)) // Fail trying to put newItem into inventory (full)
        return false; // Inventory full
    else // Inventory not full
        DecreaseMoney(newItem->GetCost()); // Pay for it

    return true; // Item buyed!
}

bool Hero::Sell(int itemIndex) {
    Item* itemToSell = Inventory.Remove(itemIndex);
    if (itemToSell == 0) // No item in itemIndex possition of inventory
        return false; // No sale!
    else
        IncreaseMoney(itemToSell->GetCost() / 2); // Sell in half price

    return true; // Same made!
}

int Hero::GetDamage() {
    // Calculate damage using strength, dexterity, agility, and weapons.
    float damage = strength;
    float hp = (float) GetHealth() / (float) GetMaxHealth(); // Health Percent
    // Full health give 100% of damage. Otherwise calculate percentance

    Weapon* left = GetLeftHandWeapon();
    Weapon* right = GetRightHandWeapon();

    // Do we hold any weapon?
    if (left == 0 && right == 0)
        return (int) damage * hp; // Minimum damage = strength (bare hands) * health percent

    // if the weapon uses both hands, then take the damage from one of them
    if (left != 0 && right != 0) { // Holding two weapons
        if (left->bothHands) // Is it a both hand weapon?
            damage += left->GetDamage(); // Yes. Add damage once
        else
            damage += left->GetDamage() + right->GetDamage(); // Add damage from both weapons
    } else if (left == 0 && right != 0)
        damage += right->GetDamage();
    else if (left != 0 && right == 0)
        damage += left->GetDamage();

    return (int) ceil(damage * hp); // Returns the smallest integral value that is not less than x
}

int Hero::GetProtection() {
    float protection;
    float hp = GetHealth() / GetMaxHealth(); // Health Percent
    if (wearingArmor != 0)
        protection = wearingArmor->GetProtection();

    // Add an amount from agility
    protection *= (float) agility / 50.0 + 1;
    return (int) ceil(protection * hp);
}

Weapon* Hero::GetLeftHandWeapon() const {
    return leftHand;
}

Weapon* Hero::SetLeftHandWeapon(Weapon* newWeapon) {
    Weapon* previous;

    if (newWeapon == 0 && leftHand == 0) // No new weapon and not holding one
        return 0;

    if (newWeapon == 0 && leftHand != 0) { // Drop left hand weapon
        previous = new Weapon(leftHand);
        delete leftHand;
        leftHand = 0;
        return previous;
    }

    if (newWeapon != 0 && leftHand == 0) { // Put new weapon and return 0
        if (newWeapon->GetType() != Item::Weapon) // No weapon item
            return 0;
        leftHand = new Weapon(newWeapon);
        return 0;
    }

    if (newWeapon != 0 && leftHand != 0) { // Keep new and return old
        if (newWeapon->GetType() != Item::Weapon) // No weapon item
            return 0;
        previous = new Weapon(leftHand);
        delete leftHand;
        leftHand = new Weapon(newWeapon);
        return previous;
    }
    return 0; // Missed any combination?
}

Weapon* Hero::GetRightHandWeapon() const {
    return rightHand;
}

// Return's the weapon that was on right hand, if any...

Weapon* Hero::SetRightHandWeapon(Weapon* newWeapon) {
    Weapon* previous;

    if (newWeapon == 0 && rightHand == 0) // No new weapon and not holding one
        return 0;

    if (newWeapon == 0 && rightHand != 0) { // Drop right hand weapon
        previous = new Weapon(rightHand);
        delete rightHand;
        rightHand = 0;
        return previous;
    }

    if (newWeapon != 0 && rightHand == 0) { // Put new weapon and return 0
        if (newWeapon->GetType() != Item::Weapon) // No weapon item
            return 0;
        rightHand = new Weapon(newWeapon);
        return 0;
    }

    if (newWeapon != 0 && rightHand != 0) { // Keep new and return old
        if (newWeapon->GetType() != Item::Weapon) // No weapon item
            return 0;
        previous = new Weapon(rightHand);
        delete rightHand;
        rightHand = new Weapon(newWeapon);
        return previous;
    }
    return 0; // Missed any combination?
}

Armor* Hero::GetArmor() const {
    return wearingArmor;
}

Armor* Hero::SetArmor(Armor* newArmor) {
    Armor* previous;

    if (newArmor == 0 && wearingArmor == 0)
        return 0;

    if (newArmor == 0 && wearingArmor != 0) {
        previous = new Armor(wearingArmor);
        delete wearingArmor;
        wearingArmor = 0;
        return previous;
    }

    if (newArmor != 0 && wearingArmor == 0) {
        if (newArmor->GetType() != Item::Armor) // Not an armor
            return 0;
        wearingArmor = new Armor(newArmor);
        return 0;
    }

    if (newArmor != 0 && wearingArmor != 0) {
        previous = new Armor(wearingArmor);
        delete wearingArmor;
        wearingArmor = new Armor(newArmor);
        return previous;
    }

    return 0; // Missed any combination?
}

// Return false if selected item isn't potion

bool Hero::UsePotion(int invIndex) {
    Potion* selection = (Potion*) Inventory.Examine(invIndex);
    if (selection == 0) // Not an item at all
        return false;

    if (selection->GetType() != Item::Potion) // Not a potion
        return false;

    if (selection->GetLevel() > GetLevel()) // Potion level > player level
        return false;

    IncreaseHealth(selection->GetHealthPower());
    IncreaseMagic(selection->GetMagicPower());
    // Potion consumed. Remove it from inventory
    Inventory.Remove(invIndex);
    return true;
}

bool Hero::LearnSpell(Spell* newSpell) {
    // If it is a unkown spell, learn it.
    for (int i = 0; i < maxSpells; i++) {
        if (spellList[i] == 0) {
            spellList[i] = new Spell(newSpell); // Copy spell to spell list
            return true;
        } else if (spellList[i]->GetName() == newSpell->GetName())
            return false; // Known spell
    }
    return false;
}

void Hero::DisplaySpellList() {
    if (spellList[0] == 0) {
        cout << "  NONE" << endl;
        return;
    }

    for (int i = 0; i < maxSpells; i++)
        if (spellList[i]) {
            cout << i + 1 << ": ";
            spellList[i]->DisplayInfo();
        }
}

/*
 * Return's the damage of spell
 * Error codes:
 *  -1: Parameter victim is null
 *  -2: Error spell index
 *  -3: Caster hasn't the right level
 *  -4: Victim is in effect of a previous spell
 *  -5: Caster hasn't enough magic power
 */
int Hero::CastSpell(Living* victim, int spellIndex) {
    int i = spellIndex - 1; // User uses index numbers from 1..n, we use 0..n-1
    Monster* Victim = (Monster*) victim;
    if (Victim == 0)
        return -1; // Parameter victim is null

    if (i < 0 || i > maxSpells)
        return -2; // Error spell index

    if (GetLevel() < spellList[i]->GetLevel())
        return -3; // Caster hasn't the right level

    if (Victim->GetStatus() == Monster::Spelled)
        return -4; // Victim is in effect of a previous spell

    if (GetMagic() < spellList[i]->GetMagicPower())
        return -5; // Caster hasn't enough magic power

    Victim->SpellAvoidChance(spellList[i]->GetAvoidChanceEffect());
    Victim->SpellDamage(spellList[i]->GetDamageEffect());
    Victim->SpellDefence(spellList[i]->GetDefenceEffect());
    Victim->SpellRounds(spellList[i]->GetRounds());

    // Calculate the damage from the spell
    float spellDamage = spellList[i]->GetDamage();
    // Dexterity effects spell damage
    spellDamage *= (float) dexterity / 50.0 + 1;
    float mp = (float) GetMagic() / (float) GetMaxMagic(); // Magic percent

    // Decrease magic power
    DecreaseMagic(spellList[i]->GetMagicPower());
    return ceil(spellDamage * mp);
}

int Hero::Attack(Living* defender) {
    Monster *victim = (Monster*) defender;

    int heroDamage = GetDamage();
    int monsterDefence = victim->GetDefence();
    float monsterAvoidChance = victim->GetAvoidChance();

    // Calculate the chance victim to avoid attack
    // Get a random number between 1 - 100;
    float attackChance = rand() % 100 + 1;
    if (monsterAvoidChance >= attackChance)
        // monsterAvoidChance is a number between 1 - MAX_AVOID_CHANCE
        return 0; // Victim escaped attack!

    // Decrease victim health by heroDamage - monsterDefence
    int damage = heroDamage - monsterDefence;
    if (damage > 0) {
        victim->DecreaseHealth(damage);
        if (victim->GetHealth() == 0)
            victim->SetStatus(Living::Dead);
    }

    return damage;
}

void Hero::DisplayInfo() {
    // Output name and characteristics
    cout << GetName();
    cout << endl;
    cout << "\tExperience: " << GetExperience()
            << "\tLevel: " << GetLevel()
            //            << endl
            << "\tHealth: " << GetHealth() << "/" << GetMaxHealth()
            << "\tMana: " << GetMagic() << "/" << GetMaxMagic()
            << endl
            << "\tStrength: " << GetStrength()
            << "\tDexterity: " << GetDexterity()
            << "\tAgility: " << GetAgility()
            << endl
            << "\tMoney: " << money << " gold coins."
            << endl;
    // Output carring weapons
    if (rightHand != 0) {
        if (rightHand->bothHands) // Both hands weapon
            cout << "\tHands: " << rightHand->GetName() << ", Damage: " << rightHand->GetDamage();
        else {
            cout << "\tRight hand weapon: ";
            cout << rightHand->GetName() << ", Damage: " << rightHand->GetDamage() << endl;
            ;
        }
    } else
        cout << "\tRight hand weapon: Nothing" << endl;

    if (leftHand != 0) {
        if (leftHand->bothHands == false) {
            cout << "\tLeft hand weapon:  ";
            if (leftHand != 0)
                cout << leftHand->GetName() << ", Damage: " << leftHand->GetDamage() << endl;
        }
    } else
        cout << "\tLeft hand weapon:  Nothing" << endl;

    // Output armor info
    cout << "\tArmor: ";
    if (wearingArmor != 0)
        cout << wearingArmor->GetName() << ", Protection: " << wearingArmor->GetProtection();
    else
        cout << "None";
    cout << endl;
    cout << "Press [Enter] to display inventory...";
    cin.ignore();
    //    cout <<endl;
    Inventory.DisplayInfo();
    //    cout <<endl;
    cout << "Press [Enter] to display known spells...";
    cin.ignore();
    DisplaySpellList();
}

void Hero::DisplayShortInfo() {
    cout << GetName();
    cout << "\tHealth: " << GetHealth() << "/" << GetMaxHealth()
            << ", Mana: " << GetMagic() << "/" << GetMaxMagic()
            << endl
            << "  Level: " << GetLevel()
            << ", Damage: " << GetDamage()
            << ", Defence: " << GetProtection()
            << endl;
}