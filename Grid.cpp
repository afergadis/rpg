/* 
 * 
 */

#include <stdio.h>
#include <iostream>
using std::cout;
using std::endl;

#include "Grid.h"

/*
 *    +---+---+---+---+---+---+---+---+---+---+
 *  6 |   |   |   | M |   |   |   |   |   |   |
 *    +---+---+---+---+---+---+---+---+---+---+
 *  5 |   |   | U | U |   |   |   |   |   |   |
 *    +---+---+---+---+---+---+---+---+---+---+
 *  4 | M |   |   |   |   |   | U | U | U | U |
 *    +---+---+---+---+---+---+---+---+---+---+
 *  3 | U | U |   |   |   |   | U | M |   |   |
 *    +---+---+---+---+---+---+---+---+---+---+
 *  2 |   |   |   |   |   |   | U | U |   |   |
 *    +---+---+---+---+---+---+---+---+---+---+
 *  1 |   |   | U |   |   |   |   |   |   | U |
 *    +---+---+---+---+---+---+---+---+---+---+
 *  0 | S | M | U |   |   |   |   |   | U | U |
 *    +---+---+---+---+---+---+---+---+---+---+
 *      0   1   2   3   4   5   6   7   8   9
 */

Grid::Grid() {
    // Define markets
    Map[0][1].SetType(Tile::MarketPlace);
    Map[0][1].SetMessage("Market Place at square [0, 1]");
    Map[3][7].SetType(Tile::MarketPlace);
    Map[3][7].SetMessage("Market Place at square [3, 7]");
    Map[4][0].SetType(Tile::MarketPlace);
    Map[4][0].SetMessage("Market Place at square [4, 0]");
    Map[6][3].SetType(Tile::MarketPlace);
    Map[6][3].SetMessage("Market Place at square [6, 3]");
    // Define unavailable
    Map[0][2].SetType(Tile::Unavailable);
    Map[0][2].SetMessage("Can't walk there");
    Map[0][8].SetType(Tile::Unavailable);
    Map[0][8].SetMessage("Can't walk there");
    //    Map[0][9].SetType(Tile::Unavailable);
    //    Map[0][9].SetMessage("Can't walk there");
    Map[1][2].SetType(Tile::Unavailable);
    Map[1][2].SetMessage("Can't walk there");
    Map[1][9].SetType(Tile::Unavailable);
    Map[1][9].SetMessage("Can't walk there");
    Map[2][6].SetType(Tile::Unavailable);
    Map[2][6].SetMessage("Can't walk there");
    Map[2][7].SetType(Tile::Unavailable);
    Map[2][7].SetMessage("Can't walk there");
    Map[2][6].SetType(Tile::Unavailable);
    Map[2][6].SetMessage("Can't walk there");
    Map[3][0].SetType(Tile::Unavailable);
    Map[3][0].SetMessage("Can't walk there");
    Map[3][1].SetType(Tile::Unavailable);
    Map[3][1].SetMessage("Can't walk there");
    Map[3][6].SetType(Tile::Unavailable);
    Map[3][6].SetMessage("Can't walk there");
    Map[4][6].SetType(Tile::Unavailable);
    Map[4][6].SetMessage("Can't walk there");
    Map[4][7].SetType(Tile::Unavailable);
    Map[4][7].SetMessage("Can't walk there");
    Map[4][8].SetType(Tile::Unavailable);
    Map[4][8].SetMessage("Can't walk there");
    Map[4][9].SetType(Tile::Unavailable);
    Map[4][9].SetMessage("Can't walk there");
    Map[5][2].SetType(Tile::Unavailable);
    Map[5][2].SetMessage("Can't walk there");
    Map[5][3].SetType(Tile::Unavailable);
    Map[5][3].SetMessage("Can't walk there");

    // Starting position
    r = c = 0;
}

Grid::Grid(const Grid& orig) {
}

Grid::~Grid() {
}

bool Grid::MoveN() {
    if (r + 1 == Grid::rows)
        return false;

    // Try to enter the new tile
    Tile::tile_t tt = Map[r + 1][c].GetType();
    if (tt == Tile::Unavailable) {
        cout << Map[r + 1][c].GetMessage() << endl;
        Map[r + 1][c].revealed = true;
        return false;
    }

    // Exit from the previous tile
    Map[r][c].Exit();
    r++;
    // Enter the new one
    Map[r][c].Enter();
    return true;
}

bool Grid::MoveS() {
    if (r - 1 < 0)
        return false;

    // Try to enter the new tile
    Tile::tile_t tt = Map[r - 1][c].GetType();
    if (tt == Tile::Unavailable) {
        cout << Map[r - 1][c].GetMessage() << endl;
        Map[r - 1][c].revealed = true;
        return false;
    }

    // Exit from the previous tile
    Map[r][c].Exit();
    r--;
    // Enter the new one
    Map[r][c].Enter();
    return true;
}

bool Grid::MoveE() {
    if (c + 1 == Grid::cols)
        return false;

    // Try to enter the new tile
    Tile::tile_t tt = Map[r][c + 1].GetType();
    if (tt == Tile::Unavailable) {
        cout << Map[r][c + 1].GetMessage() << endl;
        Map[r][c + 1].revealed = true;
        return false;
    }

    // Exit from the previous tile
    Map[r][c].Exit();
    c++;
    // Enter the new one
    Map[r][c].Enter();
    return true;
}

bool Grid::MoveW() {
    if (c - 1 < 0)
        return false;

    // Try to enter the new tile
    Tile::tile_t tt = Map[r][c - 1].GetType();
    if (tt == Tile::Unavailable) {
        cout << Map[r][c - 1].GetMessage() << endl;
        Map[r][c - 1].revealed = true;
        return false;
    }

    // Exit from the previous tile
    Map[r][c].Exit();
    c--;
    // Enter the new one
    Map[r][c].Enter();
    return true;
}

bool Grid::GotoXY(int x, int y) {
    if (r >= 0 && r < Grid::rows && c >= 0 && c < Grid::cols) {
        Tile::tile_t tt = Map[r][c].GetType();
        if (tt != Tile::Unavailable) {
            r = x;
            c = y;
            return true;
        }
    }
    return false;
}

Tile* Grid::GetTile() {
    return &Map[r][c]; // Return current tile
}

void Grid::DisplayCurrentPossition() {
    cout << endl << "You are in [" << r << ", " << c << "] tile." << endl;
}

void Grid::DisplayGrid() {
    printf("    +---+---+---+---+---+---+---+---+---+---+\n");
    for (int i = Grid::rows - 1; i >= 0; i--) {
        printf(" %2d |", i);
        for (int j = 0; j < Grid::cols; j++) {
            if (i == r && j == c)
                printf("*%1c |", Map[i][j].GetMark()); // Mark current position
            else
                printf(" %1c |", Map[i][j].GetMark());
        }
        printf("\n");
    }
    printf("    +---+---+---+---+---+---+---+---+---+---+\n");
    printf("      0   1   2   3   4   5   6   7   8   9\n");
    printf("    Legend:\n");
    printf("    *: Your position.\n");
    printf("    ?: Places you haven't been yet.\n");
    printf("    U: Unavailable. You can't walk there.\n");
    printf("    M: Market Place.\n");
}