/* 
 * Defines the grid (map) of the game
 */

#ifndef GRID_H
#define	GRID_H

#include "Tile.h"

class Grid {
public:
    Grid();
    Grid(const Grid& orig);
    virtual ~Grid();
    
    // Move in map
    bool MoveN(); // North
    bool MoveS(); // South
    bool MoveE(); // East
    bool MoveW(); // West
    bool MoveNE(); // Northeast
    bool MoveNW(); // Northwest
    bool MoveSE(); // Southeast
    bool MoveSW(); // Southwest

    bool GotoXY(int x, int y);

    Tile* GetTile();

    void DisplayCurrentPossition();
    void DisplayGrid();
private:
    enum {rows = 7, cols = 10};
    Tile Map[rows][cols];
    int r, c;
};

#endif	/* GRID_H */

/*
 *    +---+---+---+---+---+---+---+---+---+---+
 *  6 |   |   |   | M |   |   |   |   |   |   |
 *    +---+---+---+---+---+---+---+---+---+---+
 *  5 |   |   | U | U |   |   |   |   |   |   |
 *    +---+---+---+---+---+---+---+---+---+---+
 *  4 | M |   |   |   |   | U | U | U |   |   |
 *    +---+---+---+---+---+---+---+---+---+---+
 *  3 | U | U |   |   |   | U | M |   |   |   |
 *    +---+---+---+---+---+---+---+---+---+---+
 *  2 |   |   |   |   |   | U | U |   |   |   |
 *    +---+---+---+---+---+---+---+---+---+---+
 *  1 |   |   | U |   |   |   |   |   |   | U |
 *    +---+---+---+---+---+---+---+---+---+---+
 *  0 | S | M | U |   |   |   |   |   | U | U |
 *    +---+---+---+---+---+---+---+---+---+---+
 *      0   1   2   3   4   5   6   7   8   9
 */