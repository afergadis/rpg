#include "main.h"

void Wait() {
    cout << endl;
    cout << "Press [Enter] to continue...";
    cin.ignore();
    fputs("\033[A\033[2K", stdout); // Erase the line: Press [Enter] to continue...
}

char ReadChar(const char* prompt, char defaultAnswer) {
    cout << prompt << ": [" << (char) toupper(defaultAnswer) << "] ";

    string s;
    getline(cin, s);
    cout << endl;

    if (s[0] == '\0')
        return toupper(defaultAnswer);

    return toupper(s[0]);
}

void ClearScreen() {
    for (int i = 0; i < 25; i++) // Erase 24 lines
        fputs("\033[A\033[2K", stdout);
}