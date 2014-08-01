/* 
 * 
 */

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::endl;

#include <cstdlib>

#include "Tile.h"

Tile::Tile() {
    tt = Tile::Common;
    msg = "";
    revealed = false;
}

Tile::Tile(string s, tile_t type) {
    tt = type;
    msg = s;
    revealed = false;
}

Tile::Tile(const Tile& orig) {
}

Tile::~Tile() {
}

void Tile::SetMessage(string s) {
    msg = s;
}

string Tile::GetMessage() const {
    return msg;
}

void Tile::SetType(tile_t type) {
    tt = type;
}

Tile::tile_t Tile::GetType() const {
    return tt;
}

char Tile::GetMark() const {
    if (!revealed)
        return '?';

    char mark;
    switch (tt) {
        case Tile::Unavailable:
            mark = 'U';
            break;
        case Tile::MarketPlace:
            mark = 'M';
            break;
        default:
            mark = ' ';
            break;
    }
    return mark;
}

Tile::tile_t Tile::Enter() {
    revealed = true;

    int hostile = rand() % 5; // 20% chance to be a hostile

    if (tt != Tile::Unavailable && tt != Tile::MarketPlace) {
        if (hostile > 0)  // value of 0 is for hostile tile
            SetType(Tile::Common);
        else
            SetType(Tile::Hostile);
    }

    cout << msg << endl; // Inform user
    return tt;
}

void Tile::Exit() { // Nothing happens now here. Placeholder for future use...
}