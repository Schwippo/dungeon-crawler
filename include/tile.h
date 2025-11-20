#ifndef TILE_H
#define TILE_H

#include "character.h"
#include <string>

class Character;

// abstract class Tile mit Events
class Tile {
protected:
    std::string texture; // Basistextur
    Character* character; // Figur auf der Kachel / wenn nicht: nullptr
    const int row;
    const int column;

    // Konstruktor protected, damit nur Unterklassen erzeugt werden
    Tile(std::string tex, int r, int c)
        : texture(std::move(tex)), character(nullptr), row(r), column(c) {}

public:
    virtual ~Tile() = default;

    // Anzeigename: wenn Figur auf Kachel, dann deren Textur, wenn nicht: eigene
    virtual std::string getTexture() const;

    bool hasCharacter() const;
    Character* getCharacter() const;
    void setCharacter(Character* c);

    int getRow() const;
    int getColumn() const;

    // true, wenn Bewegung erfolgreich (inkl. enter/ leave)
    bool moveTo(Tile* destTile, Character* who);

    // Event beim Verlassen
    // In P1 immer true
    virtual bool onLeave(Tile* destTile, Character* who);

    // Event beim Betreten (erlaubt? -> alternativee Zielkachel)
    // Portal nutzt alternative Zielkachel, sonst nullptr
    virtual std::pair<bool, Tile*> onEnter(Character* who) = 0;
};



#endif //TILE_H
