/* 
 *
 */

#ifndef GROUP_H
#define	GROUP_H

#include "Living.h"

/*
 * Holds a group of Living "objects" as hero's and monsters
 */
class Group {
public:
    enum group_t {Heros, Monsters}; // Declares the type of group members
    // n: The number of members
    Group(int n = 3, group_t type = Group::Heros);
    Group(const Group& orig);
    virtual ~Group();

    int Size() const; // Return the number of members
    group_t Type() const; // Return the type of the group
    void Info();

    // Handle functions
    bool Add(Living* member);
    Living* Remove(int index); // Remove by index
    Living* Remove(Living* member); // Remove by object
    Living* Member(int index); // Returns a pointer to selected group member
    Living* NextMember(); // Using an index to loop through members
    Living* PrevMember();
    void IncreaseHealth(); // Increase health amount of members by their level
    void DecreaseHealth();
    void IncreaseMagic();
    void DecreaseMagic();
    void Resurrect(); // Bring dead members back to life!
private:
    group_t gt;
    Living** members;
    int index; // Index to loop through members
    int count; // Count members
    int capacity; // The capacity of the group
};

#endif	/* GROUP_H */

