#include "main.h"
//#include "Hero.h"
//
//#include <iostream>
//using std::cin;
//using std::cout;
//using std::endl;
//
//extern char ReadChar(const char* prompt, char defaultAnswer);

void EquipWeapon(Hero* aHero) {
//    cout << aHero->GetName() << endl;
    // Inventory empty?
    if (aHero->Inventory.Items() == 0) {
        cout << "Empty inventory. Must buy some weapons first." << endl;
        return;
    }

    // Weapons on inventory?
    if (aHero->Inventory.Weapons() == 0) {
        cout << "You are not carring any weapons." << endl;
        return;
    }

    // Holding 2 weapons or 2 hand weapon?
    Weapon *left, *right;
    left = aHero->GetLeftHandWeapon();
    right = aHero->GetRightHandWeapon();
    if (left != 0 && right != 0)
        if (left->bothHands) {
            cout << "You don't have free hand. You must unequip first." << endl;
            return;
        }

    int choise;
    while (true) { // Choose weapon from inventory loop
        // Display inventory to choose
        cout << aHero->GetName() << endl;
        aHero->Inventory.DisplayWeapons();
        cout << "Give the item position of weapon to use (0 to exit): ";
        cin >> choise;
        cin.ignore(); // Ignore new line character
        if (choise == 0)
            return; // Exit function

        // Our list of weapons isn't in continues numbers,
        // so we examine if the choise is realy a weapon
        if (aHero->Inventory.GetItemType(choise) != Item::Weapon)
            cout << "Bad choise. Try again." << endl;
        else
            break; // Choise made
    }

    Weapon* choosedWeapon = (Weapon*) aHero->Inventory.Remove(choise);
    // If choosed weapon uses both hands and user hands aren't empty, must unequip first.
    if (choosedWeapon->bothHands && (right != 0 || left != 0)) { // Holding one weapon
        cout << "You choosed both hands weapon but your hands aren't free. Uneqiup first." << endl;
        // Put weapon back to inventory
        aHero->Inventory.Add(choosedWeapon);
        delete choosedWeapon;
        return;
    }

    // Choosed weapon uses both hands and both hands are free
    if (choosedWeapon->bothHands) {
        cout << "Holding: " << choosedWeapon->GetName();
        aHero->SetLeftHandWeapon(choosedWeapon);
        aHero->SetRightHandWeapon(choosedWeapon);
        delete choosedWeapon; // Set*Weapon copies argument
        return;
    }

    // Find an empty hand to put on.
    if (right == 0) {
        aHero->SetRightHandWeapon(choosedWeapon);
        cout << "Right hand: " << choosedWeapon->GetName() << endl;
    } else {
        aHero->SetLeftHandWeapon(choosedWeapon);
        cout << "Left hand: " << choosedWeapon->GetName() << endl;
    }
}

void EquipArmor(Hero* aHero) {
    // Inventory empty?
    if (aHero->Inventory.Items() == 0) {
        cout << "Empty inventory. Must buy some weapons first." << endl;
        return;
    }

    // Armors on inventory?
    if (aHero->Inventory.Armors() == 0) {
        cout << "You are not carring any armor." << endl;
        return;
    }

    int choise;
    while (true) { // Choose armor from inventory loop
        // Display inventory to choose
        cout << aHero->GetName() << endl;
        aHero->Inventory.DisplayArmors();
        cout << "Give the item position of armor to use (0 to exit): ";
        cin >> choise;
        cin.ignore(); // Ignore new line character
        if (choise == 0)
            return; // Exit function

        // Our list of armors isn't in continues numbers,
        // so we examine if the choise is realy an armor
        if (aHero->Inventory.GetItemType(choise) != Item::Armor)
            cout << "Bad choise. Try again." << endl;
        else
            break; // Choise made
    }

    Armor* choosedArmor = (Armor*) aHero->Inventory.Remove(choise);
    // Check level
    if (choosedArmor->GetLevel() > aHero->GetLevel()) {
        cout << "You don't have the right level to wear " << choosedArmor->GetName() << endl;
        // Put armor back
        aHero->Inventory.Add(choosedArmor);
        delete choosedArmor;
        return;
    }
    // If hero doesn't wear any armor
    if (aHero->GetArmor() == 0) {
        aHero->SetArmor(choosedArmor);
        cout << "Now you are wearing " << choosedArmor->GetName() << endl;
    }
    else {
        cout << "You put " << aHero->GetArmor()->GetName() << " into inventory "
                << "and wear " << choosedArmor->GetName() << endl;
        aHero->Inventory.Add(aHero->GetArmor()); // Put wearing armor on inventory
        aHero->SetArmor(choosedArmor);
    }

    delete choosedArmor;
    return;
}
