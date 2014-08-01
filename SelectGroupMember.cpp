#include "main.h"

Living* SelectGroupMember(Group &aGroup) { // Get a reference to the group
    int choise;
    Living *member = 0;

    // Display group info and let user select
    aGroup.Info();
    while (true) {
        cout << "Select member by it's number: ";
        cin >> choise;
        cin.ignore();
        member = aGroup.Member(choise);
        // Check if selected a member or null or the member is dead
        if (member == 0)
            cout << "Bad choise! Try again.\n";
        else if (member->GetStatus() == Living::Dead)
            cout << member->GetName() << " is dead!\n";
        else
            return member;
    }
}