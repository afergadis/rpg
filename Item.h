/* 
 * File:   Item.h
 *
 * Defines a generic item.
 */

#ifndef ITEM_H
#define	ITEM_H

#include <string>
using std::string;

class Item {
public:
    enum item_t {Undefined, Weapon, Armor, Potion};
    Item(); // Default Constructor
    Item(const Item *newItem); // Copy constructor
    Item(const Item& orig); // Copy constructor
    Item(string n, int c, int l); // Constructor with members initialization
    virtual ~Item();
    Item& operator=(const Item &other); // Assigment

    string GetName() const;
    void SetName(const string &aName);

    int GetCost() const;
    void SetCost(int c);

    int GetLevel() const;
    void SetLevel(int l);

    item_t GetType() const;
    void SetType(item_t aType);

    virtual void DisplayInfo();
private:
    string name; // Το όνομα του αντικειμένου
    int cost; // Κόστος απόκτισης
    int level; // Επίπεδο για χρήση του
    item_t it;
};

#endif	/* ITEM_H */

