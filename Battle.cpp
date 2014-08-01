#include "main.h"

//void CreateEnemies(Group* Gang, int members, int maxlevel);
void HeroAttack(Hero* attacker, Monster* victim);
bool SpellAttack(Hero* caster, Monster* victim);
void MonsterAttack(Hero* victim, Monster* attacker);

bool Battle(Group& Party) {
    char response;
    bool heroTurn = true;
    bool battleOver = false;
    Hero* Player = 0;
    Monster* Opponent = 0;

    // Find hero's min level
    int minlevel = 10;
    for (int i = 1; i <= Party.Size(); i++) {
        Player = (Hero*) Party.Member(i);
        if (minlevel > Player->GetLevel())
            minlevel = Player->GetLevel();
    }
    // Create a random number of monsters, no more monsters than heros
    int n = rand() % Party.Size() + 1;
    // Create a gang of monsters to fight
    Group Gang(n, Group::Monsters);
    // Make some monsters to add in gang
    for (int i = 0; i < n; i++) {
        Opponent = new Monster(minlevel);
        Gang.Add(Opponent);
    }
    Gang.Info();
    Wait();

    Player = (Hero*) Party.NextMember();
    // In battle rounds all party members fight by turn. User doesn't select,
    // but he selects victim from the Gang members.
    while (!battleOver) {
        ClearScreen();
        while (heroTurn) {
            cout << "\nB A T T L E   M O D E\n";
            cout << endl << "Selected Hero: " << Player->GetName() << endl << endl;
            response = ReadChar("[A]ttack\n"
                    "Cast [s]pell\n"
                    "[C]onsume potion\n"
                    "E[q]uip weapon\n"
                    "Equip a[r]mor\n"
                    "[U]equip\n"
                    "Display selected [p]layer info\n"
                    "Display par[t]y stats\n"
                    "Display monsters [g]ang stats\n"
                    ">Choose", 'A');
            ClearScreen();
            switch (response) {
                case 'A':
                    if (Gang.Size() > 1)
                        Opponent = (Monster*) SelectGroupMember(Gang);
                    else
                        Opponent = (Monster*) Gang.NextMember();
                    //                    cout << Player->GetName() << " vs " << Opponent->GetName() << endl;
                    HeroAttack(Player, Opponent);
                    cout << "\n>>Info after your attack:\n";
                    Opponent->DisplayInfo();
                    //                    Wait();
                    //                    ClearScreen();
                    heroTurn = false;
                    break;
                case 'S':
                    if (Gang.Size() > 1)
                        Opponent = (Monster*) SelectGroupMember(Gang);
                    else
                        Opponent = (Monster*) Gang.NextMember();
                    if (SpellAttack(Player, Opponent))
                        heroTurn = false;
                    break;
                case 'C':
                    if (Player->Inventory.Potions() > 0) {
                        UsePotion(Player); // Calls UsePotion function for Player, to select a potion
                        //                        heroTurn = false;
                    } else
                        cout << Player->GetName() << " has no potions." << endl;
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
                case 'P':
                    Player->DisplayInfo();
                    break;
                case 'T':
                    Party.Info();
                    Wait();
                    break;
                case 'G':
                    Gang.Info();
                    Wait();
                    break;
                default:
                    cout << "Bad choise! Try again.\n\n";
                    break;
            }
        }
        if (Opponent->GetStatus() == Monster::Dead) {
            cout << endl << Player->GetName() << " killed " << Opponent->GetName() << "!" << endl;
            // Get money from killed monster
            Hero::IncreaseMoney(Opponent->GetMoney());
            cout << "You've got " << Opponent->GetMoney() << " gold coins!\n";
            // Remove monster from gang
            Gang.Remove(Opponent);
            if (Gang.Size() == 0)  // No more monsters to fight!
                battleOver = true;
        }

        Wait();
        // Monster's turn
        if (!battleOver) {
            Opponent = (Monster*) Gang.NextMember();
            //            cout << Opponent->GetName() << " vs " << Player->GetName() << endl;
            MonsterAttack(Player, Opponent);
            cout << "\n>>Info after monster's attack:\n";
            Player->DisplayShortInfo();
            if (Player->GetStatus() == Hero::Dead)
                cout << endl << Opponent->GetName() << " killed your hero " << Player->GetName() << "!" << endl;

            //            Wait();
            //            ClearScreen();

            battleOver = true; // We assume that battle is over
            // We DON'T remove dead heros from party. The ressurect!
            // If there is a alive member in party group, the battle is not over
            for (int i = 1; i <= Party.Size(); i++)
                if (Party.Member(i)->GetStatus() != Living::Dead) {// We have an alive member
                    battleOver = false;
                    break; // exit for loop
                }
            if (battleOver)
                return false; // We lost!
            
            Wait();
            ClearScreen();
        }

        heroTurn = true;
        Player = (Hero*) Party.NextMember();
        // Hero and monster restore some health and magic according to their level
        Party.IncreaseHealth();
        Party.IncreaseMagic();
        Gang.IncreaseHealth();
    }
    return true;
}

void HeroAttack(Hero* attacker, Monster* victim) {
    int attackDamage;

    cout << attacker->GetName() << " vs " << victim->GetName() << endl;
    attackDamage = attacker->Attack(victim);
    if (attackDamage <= 0) {
        cout << endl;
        cout << victim->GetName() << " escaped attack!" << endl;
        return;
    }

    cout << "\tManaged a hit of " << attackDamage
            << " health points" << endl;

    // Increase experience by attack damage
    attacker->IncreaseExperience(attackDamage);
}

void MonsterAttack(Hero* victim, Monster* attacker) {
    int attackDamage;

    cout << attacker->GetName() << " vs " << victim->GetName() << endl;
    attackDamage = attacker->Attack(victim);
    if (attackDamage <= 0) {
        cout << endl;
        cout << victim->GetName() << " escaped attack!" << endl;
        return;
    }

    cout << "\tManaged a hit of " << attackDamage
            << " health points" << endl;
}

// Return true if spell casted

bool SpellAttack(Hero* caster, Monster* victim) {
    // Choose a spell
    int choise;

    while (true) {
        caster->DisplaySpellList();
        cout << "Choose a spell and give it's corresponding number (0 to exit): ";
        cin >> choise;
        cin.ignore();
        if (choise == 0)
            return false; // No spell casted

        int result = caster->CastSpell(victim, choise);
        switch (result) {
            case -1:
                cout << "Something went wrong! No monster selected!\n";
                return false;
            case -2:
                cout << "Bad choise! Try again.\n";
                break;
            case -3:
                cout << "You don't have the right level to cast this spell\n";
                break;
            case -4:
                cout << victim->GetName() << " is in effect of a previous spell\n";
                return false;
            case -5:
                cout << endl << caster->GetName() << " hasn't enough magic power to cast this spell\n";
                break;
            default:
                victim->SetStatus(Monster::Spelled);
                victim->DecreaseHealth(result);
                caster->IncreaseExperience(result);
                cout << caster->GetName() << " casted spell for damage "
                        << result << " health points to " << victim->GetName() << endl;
                return true;
        }
    }
}