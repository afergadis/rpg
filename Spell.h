/* 
 *
 */

#ifndef SPELL_H
#define	SPELL_H

#include <string>
using std::string;

class Spell {
public:
    Spell();
    Spell(const Spell* otherSpell);
    Spell(const Spell& orig);
    virtual ~Spell();
    
    void CreateSpell(string n, int c, int l, int mp, int d, int r, int ds, int dd, int da);

    string GetName() const;
    void SetName(string n);

    int GetCost() const;
    void SetCost(int c);

    int GetLevel() const;
    void SetLevel(int l);

    int GetMagicPower() const;
    void SetMagicPower(int mp);

    int GetDamage() const;
    void SetDamage(int d);

    int GetRounds() const;
    void SetRounds(int r);

    int GetDamageEffect() const;
    void SetDamageEffect(int amount);

    int GetDefenceEffect() const;
    void SetDefenceEffect(int amount);

    float GetAvoidChanceEffect() const;
    void SetAvoidChanceEffect(float amount);
    
    void DisplayInfo();
private:
    string name; 
    int cost; 
    int level;
    int magicPower; // magic power to cast spell
    int damage; // damage effect
    
    // Effect for victim
    int rounds; // For how many battle rounds spell effects
    int decreaseDamage; // Decrease victim's attributes
    int decreaseDefense;
    float decreaseAvoidChance;
};

#endif	/* SPELL_H */

