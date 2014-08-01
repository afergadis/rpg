/* 
 * All includes and fuctions defenitions
 */

#ifndef MAIN_H
#define	MAIN_H

// Include C++ headers
#include <cstdlib>
#include <cstring> // For strcmp function
#include <stdio.h>
#include <string>
using std::string;

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
using std::streamsize;

#include<limits>

#include "Hero.h"
#include "Monster.h"
#include "Market.h"
#include "Group.h"
#include "Tile.h"

/*
 * Usefull functions
 */

Living* SelectGroupMember(Group &aGroup);

/*
 * Our heroes enter a market to buy items or spells.
 */
void EnterMarket(Group &aGroup);

/*
 * Use a weapon from inventory and put the holding one back
 */
void EquipWeapon(Hero* aHero);
void EquipArmor(Hero* aHero);
Item* Unequip(Hero* aHero);

/*
 * Use potion. Consume a potion and add health and magic to player stats
 */
void UsePotion(Hero* aHero);

/*
 * Functions that handle attacks of heros and monsters
 * Returns:
 *   true : Heros won
 *   false: Monsters won
 */
bool Battle(Group& Party);

/*
 * Help functions in Library.cpp
 */
// Waits Enter to continue
void Wait();

// Prompt a string, give a default answer and return user answer
char ReadChar(const char* prompt, char defaultAnswer);

// Clear the screen
void ClearScreen();

#endif	/* MAIN_H */

