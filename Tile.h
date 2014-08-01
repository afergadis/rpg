/* 
 *
 */

#ifndef TILE_H
#define	TILE_H

#include <string>
using std::string;

class Tile {
public:

    enum tile_t {
        Common, // Nothing special here
        MarketPlace, // Group enters a market
        Unavailable, // Can't walk here
        Hostile // Enemies!
    };
    Tile();
    Tile(string s, tile_t type);
    Tile(const Tile& orig);
    virtual ~Tile();

    string GetMessage() const;
    void SetMessage(string s);

    tile_t GetType() const;
    void SetType(tile_t type);

    char GetMark() const; // Returns a character that marks tile in DisplayGrid

    tile_t Enter();
    void Exit();

    bool revealed; // No visited tiles aren't revealed
private:

    tile_t tt; // Tile type
    string msg;
};

#endif	/* TILE_H */

