/* 
 * File:   Living.h
 * 
 * Define a generic living being.
 */

#ifndef LIVING_H
#define	LIVING_H

#include <string>
using std::string;

#include "Weapon.h"
#include "Armor.h"
#include "Spell.h"

class Living {
public:
    enum status_t {
        Healthy, Spelled, Dead
    };

    Living();
    Living(string n);
    Living(const Living& orig);
    Living(const Living* orig);
    virtual ~Living();

    virtual string GetName() const;
    void SetName(string n);

    status_t GetStatus() const;
    void SetStatus(status_t status);

    int GetLevel() const;
    void SetLevel(int l);

    int GetHealth() const;
    int GetMaxHealth() const;
    void IncreaseHealth(int h);
    void DecreaseHealth(int h);
    void SetHealth(int hp);
    virtual void SetMaxHealth(int mh);
    // Heros and monsters have their logic to set max health
    // depending on hero and monster types.
    virtual void Resurrect();

    int GetMoney() const;
    void SetMoney(int amount);

    virtual void DisplayInfo();
private:
    status_t st;
    string name;
    int level;
    int healthPower;
    int maxHealthPower; // Max health power per level.
    int money; // Monsters also have money. They are income for heros!
};

#endif	/* LIVING_H */

