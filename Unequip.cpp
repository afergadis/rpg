/*
 * This file implements the logic of droping a holding weapon.
 */
#include "main.h"

Item* Unequip(Hero* aHero) {
    char response;
    bool dropFromInventory = false;

    aHero->DisplayInfo();
    // If hero doesn't hold any weapon or not wear anything, return nothing
    Weapon *left = aHero->GetLeftHandWeapon();
    Weapon *right = aHero->GetRightHandWeapon();
    Armor* armor = aHero->GetArmor();
    if (left == 0 && right == 0 && armor == 0) {
        cout << "You don't hold or wear anything." << endl;
        response = ReadChar("Drop something from inventory? [Y]es, [N]o", 'N');
        switch (response) {
            case 'Y':
                dropFromInventory = true;
                break;
            default:
                return 0;
        }
    }

    int invEmptySlots = aHero->Inventory.Size() - aHero->Inventory.Items();
    if (invEmptySlots == 0) {
        // Drop weapon or drop inventory item
        cout << "No space on your inventory. You might want to drop something." << endl;
        dropFromInventory = true;
    }

    if (dropFromInventory == false) { // Put a holding item into inventory
        while (true) {
            response = ReadChar("Put on inventory [L]eft hand weapon, [R]ight hand, [A]rmor or [E]xit? ", 'E');
            switch (response) {
                case 'L':
                {
                    if (left == 0) {
                        cout << "You don't hold anything on your left hand." << endl;
                        return 0;
                    }
                    aHero->Inventory.Add(left);
                    cout << "You put " << left->GetName() << " into your inventory." << endl;
                    aHero->SetLeftHandWeapon(0);
                    if (right != 0 && right->bothHands) // Must reset right hand too
                        aHero->SetRightHandWeapon(0);
                    return 0;
                    break;
                }
                case 'R':
                {
                    if (right == 0) {
                        cout << "You don't hold anything on your right hand." << endl;
                        return 0;
                    }
                    aHero->Inventory.Add(right);
                    cout << "You put " << right->GetName() << " into your inventory." << endl;
                    aHero->SetRightHandWeapon(0);
                    if (right->bothHands) // Must reset left hand too
                        aHero->SetLeftHandWeapon(0);
                    return 0;
                    break;
                }
                case 'A':
                {
                    if (armor == 0) {
                        cout << "You don't wear any armor." << endl;
                        return 0;
                    }
                    aHero->Inventory.Add(armor);
                    cout << "You put " << armor->GetName() << " into your inventory." << endl;
                    aHero->SetArmor(0);
                    return 0;
                    break;
                }
                case 'E':
                    return 0;
                    break;
            } // End switch
        } // End while
    } // End if

    if (dropFromInventory) {
        aHero->Inventory.DisplayInfo();
        int choise;
        cout << "Give the item position to drop (0 to exit): ";
        cin >> choise;
        cin.ignore(); // Ignore new line
        if (choise == 0)
            return 0;

        // Give some info
        Item* dropped = aHero->Inventory.Remove(choise - 1);
        if (dropped != 0)
            cout << "You dropped " << dropped->GetName() << endl;

        // If choise doesn't point to a valid item, Remove function returns 0
        // So we return 0, otherwise, we return item.
        return dropped;
    }

    return 0; // Something went wrong? Shouldn't reach this line.
}

