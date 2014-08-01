/* 
 *
 */

#ifndef MONSTER_H
#define	MONSTER_H

#include "Living.h"

class Monster : public Living {
public:
    enum monster_t {
        Dragon, Exoskeleton, Spirit
    };
    Monster(int level = 1);
    Monster(const Monster& orig);
    virtual ~Monster();

    string GetName() const;
    int GetDamage() const;
    int GetDefence() const;
    int GetAvoidChance() const;
//    status_t GetStatus() const;
//    void SetStatus(status_t stat);
    monster_t GetType() const;
    void Resurrect();

    int Attack(Living* defender);

    // Spell effects
    void SpellDamage(int amount);
    void SpellDefence(int amount);
    void SpellAvoidChance(float amount);
    void SpellRounds(int amount);

    void DisplayInfo() const;
private:
    void SetAttributes(int level);

    monster_t mt; // Monster type
    status_t st; // Healthy or spelled
    int damage; // damage can cause
    int defence; // An defense amount that is reduced from the damage it takes
    float avoidChance; // The chance to avoid an attack;

    // Effects from spell
    int rounds;
    int decreaseDamage;
    int decreaseDefence;
    int decreaseAvoidChance;
};

#endif	/* MONSTER_H */

