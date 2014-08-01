/*
 * This file implements the logic of a market.
 * Hero(s) can buy items and spells or sell items.
 */
#include "main.h"

void EnterMarket(Group &heroParty) {
    Hero* Player = 0; // Who buys or sells
    Market MarketPlace;

    if (heroParty.Size() == 1) // Only one hero in party
        Player = (Hero*) heroParty.Member(1);
    else {
        cout << "\nPlease select a hero...\n";
        Player = (Hero*) SelectGroupMember(heroParty); // Select a hero to act
        cout << "Selected Hero: " << Player->GetName() << endl;
    }

    Wait();

    bool exitMarket = false;
    while (!exitMarket) {
        bool buy, sell, spell;
        buy = sell = spell = false;
        ClearScreen();
        cout << "M A R K E T   P L A C E" << endl;
        cout << "Selected Hero: " << Player->GetName() << endl << endl;
        cout << "What would you like to do?" << endl;
        char responce = ReadChar("[B]uy\n"
                "[S]ell items\n"
                "[L]earn spells\n"
                "Select another [H]ero\n"
                "E[x]it?\n>Choose", 'X');
        switch (responce) {
            case 'B':
                buy = true;
                break;
            case 'S':
                sell = true;
                break;
            case 'L':
                spell = true;
                break;
            case 'H':
            {
                if (heroParty.Size() == 1)
                    cout << "You've got only one!\n";
                else {
                    Player = (Hero*) SelectGroupMember(heroParty);
                    cout << "Selected Hero:\n";
                    Player->DisplayShortInfo();
                }
                Wait();
            }
                break;
            case 'X': // default responce
                exitMarket = true;
                break;
        } // End responce to buy / sell question
        while (buy) { // Buying loop
            bool onlyInventory = false;
            ClearScreen();
            cout << "B U Y I N G   M O D E" << endl;
            cout << "Selected Hero: " << Player->GetName() << endl << endl;
            responce = ReadChar("You can buy\n"
                    "[W]eapon\n"
                    "[A]rmor\n"
                    "[P]otion\n"
                    "Or\n"
                    "Display your [I]nventory\n"
                    "Select another [H]ero\n"
                    "E[x]it?\n"
                    ">Choose", 'X');
            switch (responce) {
                case 'W':
                    MarketPlace.DisplayWeapons();
                    break;
                case 'A':
                    MarketPlace.DisplayArmory();
                    break;
                case 'P':
                    MarketPlace.DisplayPotions();
                    break;
                case 'I':
                    cout << Player->GetName() << endl;
                    Player->Inventory.DisplayInfo();
                    onlyInventory = true;
                    Wait();
                    break;
                case 'H':
                {
                    if (heroParty.Size() == 1)
                        cout << "You've got only one!\n";
                    else {
                        Player = (Hero*) SelectGroupMember(heroParty);
                        cout << "Selected Hero: " << Player->GetName() << endl;
                    }
                    onlyInventory = true;
                    Wait();
                    // Not the best solution! We don't want market to display
                    // items to choose. We bypass this as if user had selected
                    // to display inventory, which skips item selection.
                }
                    break;
                case 'X':
                    buy = false;
                    break;
            }
            cout << endl;
            if (!buy) // User choosed to exit
                break;
            if (!onlyInventory) { // User didn't choose inventory
                cout << "Your money: " << Player->GetMoney() << " gold coins." << endl;
                cout << "Choose item and give the corresponding number (0 to exit): ";
                int choise;
                cin >> choise;
                cin.ignore(); // Ignore new line character
                if (choise == 0)
                    break; // Exit buy loop
                Item* itemToBuy = MarketPlace.GetItem(responce, choise);
                if (itemToBuy == 0)
                    cout << "Bad choise. Try again." << endl;
                else {
                    if (Player->Buy(itemToBuy)) // If there is room in inventory and enough money...
                        cout << "Thanks!" << endl; // Transaction made
                    else // Transaction failed, but why?
                        if (Player->GetMoney() < itemToBuy->GetCost()) // not enought money
                        cout << "Sorry. You haven't enough money." << endl;
                    else // Inventory is full
                        cout << "Your inventory is full. Try sell something first." << endl;
                }
                cout << "Your money: " << Player->GetMoney() << " gold coins." << endl;
                Wait();
            }
        } // End of buy loop

        ClearScreen();
        while (sell) { // Selling loop
            ClearScreen();
            cout << "S E L L I N G   M O D E" << endl;
            cout << "Selected Hero: " << Player->GetName() << endl << endl;
            responce = ReadChar("\nYou can\n"
                    "Display your [I]nventory to choose item\n"
                    "Or\n"
                    "Select another [H]ero\n"
                    "E[x]it\n"
                    ">Choose", 'X');
            switch (responce) {
                case 'I':
                    cout << Player->GetName() << endl;
                    Player->Inventory.DisplayInfo();
                    break;
                case 'H':
                {
                    if (heroParty.Size() == 1)
                        cout << "You've got only one!\n";
                    else {
                        Player = (Hero*) SelectGroupMember(heroParty);
                        cout << "Selected Hero: " << Player->GetName() << endl;                        //                        Player->DisplayShortInfo();
                        Player->Inventory.DisplayInfo();
                    }
                }
                    break;
                case 'X':
                    sell = false;
                    break;
            }
            if (!sell) // User choosed to exit
                break;
            cout << endl;
            cout << "Your money: " << Player->GetMoney() << " gold coins." << endl;
            cout << "Choose item and give the corresponding number (0 to exit): ";
            int choise;
            cin >> choise;
            cin.ignore(); // Ignore new line character
            if (choise == 0)
                break; // Exit sell loop
            if (Player->Sell(choise)) // If there is item in inventory...
                cout << "Thanks!" << endl;
            else
                cout << "Bad choise. Try again." << endl;
            Wait();
        } // End of sell loop

        ClearScreen();
        while (spell) {
            ClearScreen();
            cout << "L E A R N I N G   S P E L L   M O D E" << endl;
            cout << "Selected Hero: " << Player->GetName() << endl << endl;
            responce = ReadChar("You can\n"
                    "Display [L]ist of Spells\n"
                    "Select another [H]ero\n"
                    "E[x]it\n"
                    ">Choose", 'X');
            switch (responce) {
                case 'L':
                    MarketPlace.DisplaySpells();
                    break;
                case 'H':
                {
                    if (heroParty.Size() == 1)
                        cout << "You've got only one!\n";
                    else {
                        Player = (Hero*) SelectGroupMember(heroParty);
                        cout << "Selected Hero: " << Player->GetName();
                    }
                }
                    break;
                case 'X':
                    spell = false;
                    break;
            }

            if (!spell) // User choosed to exti
                break;

            cout << "Choose spell and give the corresponding number (0 to exit): ";
            int choise;
            cin >> choise;
            cin.ignore(); // Ignore new line character
            if (choise == 0)
                break; // Exit learn spell loop

            Spell* spellToLearn = MarketPlace.GetSpell(choise);
            if (spellToLearn == 0)
                cout << "Bad choise! Try again." << endl;
            else {
                // Does hero has the right level?
                if (spellToLearn->GetLevel() > Player->GetLevel())
                    cout << Player->GetName() << " doesn't have the right level." << endl;
                    // Can we afford for the spell?
                else if (Player->GetMoney() >= spellToLearn->GetCost())
                    // The Living::LearnSpell method doesn't handle money,
                    // so we have to do it here.
                    if (Player->LearnSpell(spellToLearn)) { // Try to learn spell
                        cout << "Congratulation! " << Player->GetName() << " just learned the spell." << endl;
                        // Decrease money with the cost of spell
                        Player->DecreaseMoney(spellToLearn->GetCost());
                    } else // if we got a false, we already know the spell
                        cout << "Hey, " << Player->GetName() << " already knows this spell!" << endl;
                else
                    cout << Player->GetName() << " doesn't have the money to buy this spell." << endl;
            }
            Wait();
        } // End of learn spell loop
    }
}