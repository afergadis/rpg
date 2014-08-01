#include "main.h"

//#include "Hero.h"
//
//#include <iostream>
//using std::cin;
//using std::cout;
//using std::endl;
//
//extern char ReadChar(const char* prompt, char defaultAnswer);

void UsePotion(Hero* aHero) {
    // Check if hero has any potion
    if (aHero->Inventory.Potions() == 0) {
        cout << aHero->GetName() << " doesn't have any potions." << endl;
        return;
    }

    int choise;
    aHero->Inventory.DisplayPotions();
    while (true) {
        cout << "Choose potion and give the corresponding number (0 to exit): ";
        cin >> choise;
        cin.ignore();
        if (choise == 0)
            break; // Exit loop

        const Potion* selected = (Potion*) aHero->Inventory.Examine(choise);
        if (selected == 0)
            cout << "Bad choise! Try again." << endl;
        else if (aHero->UsePotion(choise) == false) { // Something went wrong
            // Examine selected item
            if (selected->GetLevel() > aHero->GetLevel())
                cout << aHero->GetName() << " doesn't have the right level." << endl;
            else if (selected->GetType() != Item::Potion)
                cout << "Not a potion! Try again." << endl;
        } else {
            cout << aHero->GetName() << " consumed " << selected->GetName() << endl;
            break; // Consumed.
        }
    }
}