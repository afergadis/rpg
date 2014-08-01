/* 
 * Handles the game logic
 */

#include "main.h"
#include "Tile.h"
#include "Grid.h"

/*
 * MAIN
 */
int main(int argc, char** argv) {
    srand(time(0));

    Group Party; // Party of heros
    Hero *Player;

    int n = 1; // Members of hero's party
    char response;
    bool inLoop = true;

    // How many members?
    do {
        cout << "How many members? (min 1, max 3). Enter: ";
        cin >> n;
        cin.ignore();
    } while (n != 1 && n != 2 && n != 3);

    while (n-- > 0) {
        response = ReadChar("Create [R]andom or [U]ser defined hero?", 'R');
        switch (response) {
            case 'R':
                Player = new Hero();
                Player->DisplayShortInfo();
                break;
            case 'U':
            {
                string name;
                Hero::hero_t ht;
                cout << "Give name: ";
                cin >> name;
                cin.ignore();
                response = ReadChar("Select race: [W]arrior, [P]alladin, [S]orcerer", 'W');
                switch (response) {
                    case 'W':
                        ht = Hero::Warrior;
                        break;
                    case 'P':
                        ht = Hero::Palladin;
                        break;
                    case 'S':
                        ht = Hero::Sorcerer;
                        break;
                }
                Player = new Hero(name, ht);
            }
                break;
            default:
                cout << "Bad choice. Try again." << endl;
        }
        Party.Add(Player);
    }
    Party.Info();

    // Create the Grid
    Grid WorldMap;
    Tile* CurrentPos = WorldMap.GetTile();
    CurrentPos->Enter();

    inLoop = true;
    while (inLoop) {
        Wait();
        ClearScreen();
        WorldMap.DisplayCurrentPossition();
        switch (CurrentPos->GetType()) {
            case Tile::Common:
            {
                response = ReadChar("You can move\n"
                        "\t[N]orth\n"
                        "\t[E]ast\n"
                        "\t[S]outh\n"
                        "\t[W]est\n"
                        "Or you can\n"
                        "\tE[q]uip weapon\n"
                        "\tEquip a[r]mor\n"
                        "\t[U]nequip\n"
                        "\t[C]onsume potion\n"
                        "\tDisplay selected [p]layer info\n"
                        "\tChange Selected [h]ero\n"
                        "\tDisplay par[t]y info\n"
                        "\tDipslay [M]ap\n"
                        "\tE[x]it Game?\n"
                        "> Choose", 'T');
                ClearScreen();
                switch (response) {
                    case 'N':
                        WorldMap.MoveN();
                        CurrentPos = WorldMap.GetTile();
                        Party.IncreaseHealth();
                        Party.IncreaseMagic();
                        break;
                    case 'E':
                        WorldMap.MoveE();
                        Party.IncreaseHealth();
                        Party.IncreaseMagic();
                        CurrentPos = WorldMap.GetTile();
                        break;
                    case 'S':
                        WorldMap.MoveS();
                        Party.IncreaseHealth();
                        Party.IncreaseMagic();
                        CurrentPos = WorldMap.GetTile();
                        break;
                    case 'W':
                        WorldMap.MoveW();
                        Party.IncreaseHealth();
                        Party.IncreaseMagic();
                        CurrentPos = WorldMap.GetTile();
                        break;
                    case 'Q':
                        EquipWeapon(Player);
                        break;
                    case 'R':
                        EquipArmor(Player);
                        break;
                    case 'U':
                        Unequip(Player);
                        break;
                    case 'C':
                        UsePotion(Player);
                        break;
                    case 'P':
                        Player->DisplayInfo();
                        //                        Wait();
                        break;
                    case 'H':
                        Player = (Hero*) SelectGroupMember(Party);
                        break;
                    case 'T':
                        Party.Info();
                        //                        Wait();
                        break;
                    case 'M':
                        WorldMap.DisplayGrid();
                        //                        Wait();
                        break;
                    case 'X':
                        inLoop = false;
                        break;
                }
            }
                break; // End Case Tile::Common
            case Tile::MarketPlace:
            {
                response = ReadChar("Enter mar[k]et\n"
                        "Or move\n"
                        "\t[N]orth\n"
                        "\t[E]ast\n"
                        "\t[S]outh\n"
                        "\t[W]est\n"
                        "Display [M]ap\n"
                        "E[x]it Game\n"
                        "> Choose", 'K');
                switch (response) {
                    case 'K':
                        ClearScreen();
                        EnterMarket(Party);
                        break;
                    case 'N':
                        WorldMap.MoveN();
                        CurrentPos = WorldMap.GetTile();
                        Party.IncreaseHealth();
                        Party.IncreaseMagic();
                        break;
                    case 'E':
                        WorldMap.MoveE();
                        CurrentPos = WorldMap.GetTile();
                        Party.IncreaseHealth();
                        Party.IncreaseMagic();
                        break;
                    case 'S':
                        WorldMap.MoveS();
                        CurrentPos = WorldMap.GetTile();
                        Party.IncreaseHealth();
                        Party.IncreaseMagic();
                        break;
                    case 'W':
                        WorldMap.MoveW();
                        CurrentPos = WorldMap.GetTile();
                        Party.IncreaseHealth();
                        Party.IncreaseMagic();
                        break;
                    case 'M':
                        WorldMap.DisplayGrid();
                        break;
                    case 'X':
                        inLoop = false;
                        break;
                }
            }
                break; // End Case Tile::MarketPlace
            case Tile::Hostile:
                cout << "You met some monsters. Engaging a battle!" << endl;
                if (Battle(Party) == false) { // We lost battle
                    cout << "We lost the battle!" << endl;
                    cout << "Starting again with half health, magic and money!" << endl;
                    cout << "Try harder next time..." << endl;
                    Wait();
                    WorldMap.GotoXY(0, 0); // Go to starting point
                    CurrentPos = WorldMap.GetTile();
                    CurrentPos->SetType(Tile::Common); // Clear tile so we won't find enemies there
                    Party.Resurrect();
                } else // Clear tile
                    CurrentPos->SetType(Tile::Common);
                break;
        }
    }

    return 0;
}
