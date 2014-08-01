/* 
 * 
 */

#include <stdio.h>

#include "Group.h"
#include "Hero.h"
#include "Monster.h"

Group::Group(int n, group_t type) {
    count = 0;
    capacity = n;
    index = 0;
    gt = type;

    // Allocate memory for an array of *capacity* pointers to items
    members = new Living*[capacity];
    // Initialize each pointer to 0 (NULL)
    for (int i = 0; i < capacity; i++) {
        members[i] = 0;
    }
}

Group::Group(const Group& orig) {
}

Group::~Group() {
    // Delete all pointers of the array
    for (int i = 0; i < count; i++) {
        delete members[i];
    }
    // Delete the array
    delete [] members;
}

int Group::Size() const {
    return count;
}

Group::group_t Group::Type() const {
    return gt;
}

bool Group::Add(Living* member) {
    // Check member pointer
    if (member == 0)
        return false; // Nothing to add

    // Check if there is room for a new member
    for (int i = 0; i < capacity; i++)
        if (members[i] == 0) {
            // What group are we?
            switch (gt) {
                case Group::Heros:
                {
                    // Cast member to Hero
                    Hero* heroMember = (Hero*) member;
                    members[i] = heroMember; // Point to new member
                }
                    break;
                case Group::Monsters:
                {
                    Monster* monsterMember = (Monster*) member;
                    members[i] = monsterMember;
                }
                    break;
            }
            count++;
            return true; // Member added
        }
    return false;
}

Living* Group::Remove(int index) {
    // User uses numbers 1..n
    if (members[index - 1] == 0) // Trying to remove a non existing member
        return 0;

    Living* memberToReturn = members[index - 1]; // Point to member
    members[index - 1] = 0; // Array pointer points to 0 (member removed)
    count--; // -1 members

    return memberToReturn; // Return pointer to member
}

Living* Group::Remove(Living* member) {
    if (member == 0) // Searching for NULL
        return 0;

    for (int i = 0; i < capacity; i++) // Search for member
        if (members[i] == member) { // Found
            members[i] = 0; // Remove from members list
            count--;
            return member; // Return the searched member
        }

    return 0; // Not found
}

Living* Group::Member(int index) {
    return members[index - 1];
}

Living* Group::NextMember() {
    if (count == 0)
        return 0; // No group members

    // Loop through not null and not dead members
    for (int i = index; i < capacity + index; i++) {
        int mid = i % capacity; // member id
        if (members[mid] != 0)
            if (members[mid]->GetStatus() != Living::Dead) {
                index = mid + 1;
                if (index == capacity)
                    index = 0;
                return members[mid];
            }
    }

    // Loop through members didn't return anything, so no live member
    return 0;
}

void Group::IncreaseHealth() {
    for (int i = 0; i < capacity; i++)
        if (members[i] != 0) {
            int amount = members[i]->GetLevel();
            members[i]->IncreaseHealth(amount);
        }
}

void Group::DecreaseHealth() {
    for (int i = 0; i < capacity; i++)
        if (members[i] != 0) {
            int amount = members[i]->GetLevel();
            members[i]->DecreaseHealth(amount);
        }
}

void Group::IncreaseMagic() {
    if (gt == Group::Monsters)
        return; // Monsters doesn't have magic

    Hero* heroMember = 0;
    for (int i = 0; i < capacity; i++)
        if (members[i] != 0) {
            heroMember = (Hero*) members[i];
            int amount = heroMember->GetLevel();
            heroMember->IncreaseMagic(amount);
        }
}

void Group::DecreaseMagic() {
    if (gt == Group::Monsters)
        return; // Monsters doesn't have magic

    Hero* heroMember = 0;
    for (int i = 0; i < capacity; i++)
        if (members[i] != 0) {
            heroMember = (Hero*) members[i];
            int amount = heroMember->GetLevel();
            heroMember->DecreaseMagic(amount);
        }
}

void Group::Resurrect() {
    // Find dead members
    bool dead = false; // Assume no dead member
    for (int i = 0; i < capacity; i++)
        if (members[i] == 0)
            continue;
        else if (members[i]->GetStatus() == Living::Dead) {
            dead = true;
            members[i]->Resurrect();
        }

    if (dead) // We had dead member. Resurrection cost half of money
        Hero::DecreaseMoney(Hero::GetMoney() / 2);
}

void Group::Info() {
    if (count == 0) {
        printf("Empty group.\n");
        return;
    }

    switch (gt) {
        case Group::Heros:
            printf("\nParty of Heros\n");
            printf("+--+--------------------+--+----------+--------+--------+--+----+----+----+----+\n");
            printf("|  |Name                |S |Type      |  Health|   Magic| L| Exp| Str| Dxt| Agl|\n");
            printf("+--+--------------------+--+----------+--------+--------+--+----+----+----+----+\n");
            break;
        case Group::Monsters:
            printf("\nGang of Monsters\n");
            printf("+--+------------------+--+-------------+--+--------+-------+--------+----------+\n");
            printf("|  |Name              |S |Type         | L|  Health| Damage| Defence| Avoid Ch.|\n");
            printf("+--+------------------+--+-------------+--+--------+-------+--------+----------+\n");
            break;
    }

    for (int i = 0; i < capacity; i++) {
        string mType; // Member type
        char mStatus = ' '; // Member status
        if (members[i] == 0)
            continue;
        if (gt == Group::Heros) {
            Hero* hero = (Hero*) members[i];
            switch (hero->GetType()) {
                case Hero::Warrior:
                    mType = "Warrior";
                    break;
                case Hero::Palladin:
                    mType = "Palladin";
                    break;
                case Hero::Sorcerer:
                    mType = "Sorcerer";
                    break;
            }
            switch (hero->GetStatus()) {
                case Living::Healthy:
                    mStatus = 'H';
                    break;
                case Living::Spelled:
                    mStatus = 'S';
                    break;
                case Living::Dead:
                    mStatus = 'D';
                    break;
            }
            printf("|%2d|%-19.19s |%1c |%-9.9s | %3d/%3d| %3d/%3d| %1d| %3d| %3d| %3d| %3d|\n",
                    i + 1, hero->Living::GetName().c_str(), mStatus, mType.c_str(),
                    hero->GetHealth(), hero->GetMaxHealth(),
                    hero->GetMagic(), hero->GetMaxMagic(),
                    hero->GetLevel(), hero->GetExperience(), hero->GetStrength(),
                    hero->GetDexterity(), hero->GetAgility()
                    );
        } else if (gt == Group::Monsters) {
            Monster* monster = (Monster*) members[i];
            switch (monster->GetType()) {
                case Monster::Dragon:
                    mType = "Dragon";
                    break;
                case Monster::Exoskeleton:
                    mType = "Exoskeleton";
                    break;
                case Monster::Spirit:
                    mType = "Spirit";
                    break;
            }
            switch (monster->GetStatus()) {
                case Living::Healthy:
                    mStatus = 'H';
                    break;
                case Living::Spelled:
                    mStatus = 'S';
                    break;
                case Living::Dead:
                    mStatus = 'D';
                    break;
            }
            printf("|%2d|%-17.17s |%1c |%-12.12s | %1d| %3d/%3d| %6d| %7d| %8d%|\n",
                    i + 1, monster->Living::GetName().c_str(), mStatus, mType.c_str(),
                    monster->GetLevel(), monster->GetHealth(), monster->GetMaxHealth(),
                    monster->GetDamage(), monster->GetDefence(), monster->GetAvoidChance()
                    );
        } // end if Group::Monsters
    } // end for
    switch (gt) {
        case Group::Heros:
            printf("+--+--------------------+--+----------+--------+--------+--+----+----+----+----+\n");
            break;
        case Group::Monsters:
            printf("+--+------------------+--+-------------+--+--------+-------+--------+----------+\n");
            printf("Legend:\n");
            printf("[S]tatus: [H]ealty, [S]pelled, [D]ead\n");
            break;
    }
}