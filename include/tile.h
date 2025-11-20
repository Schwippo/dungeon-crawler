#ifndef TILE_H
#define TILE_H

#include "character.h"
#include <string>

class Character;

class Tile {
protected:
    std::string texture;
    Character* character;
    const int row;
    const int column;

    // constructor is protected -> only lowerclass can call
    Tile(std::string tex, int r, int c)
        : texture(std::move(tex)), character(nullptr), row(r), column(c) {}

public:
    virtual ~Tile() = default;

    virtual std::string getTexture() const;

    bool hasCharacter() const;
    Character* getCharacter() const;
    void setCharacter(Character* c);

    int getRow() const;
    int getColumn() const;

    // true if movement with success (incl. enter/ leave)
    bool moveTo(Tile* destTile, Character* who);

    // Event on leave
    virtual bool onLeave(Tile* destTile, Character* who);

    // Event on enter (allowed? -> alternative dest. floor)
    // Portal uses alternative dest. floor, else nullptr
    virtual std::pair<bool, Tile*> onEnter(Character* who) = 0;
};



#endif //TILE_H
