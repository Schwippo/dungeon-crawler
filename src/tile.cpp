#include "../include/tile.h"

std::string Tile::getTexture() const {
    if (character) {
        extern const std::string& getCharacterTexture(const Character*);
        // P1: return tile
        // no character: 'X'
    }
    return character ? std::string("X") : texture;
}

bool Tile::hasCharacter() const { return character != nullptr; }

Character* Tile::getCharacter() const { return character; }
void Tile::setCharacter(Character* c) { character = c; }

int Tile::getRow() const { return row; }
int Tile::getColumn() const { return column; }

bool Tile::moveTo(Tile *destTile, Character *who) {
    if (!destTile || !who)
        return false;

    // 1) can tile be left?
    if (!onLeave(destTile, who))
        return false;

    // 2) ask if dest. tile can be entered
    auto[ok, altTile] = destTile->onEnter(who);
    if (!ok) return false;

    Tile* entered = altTile ? altTile : destTile;

    // 3) change: move character from 'this' to 'entered'
    if (this->character == who) {
        this->character = nullptr;
    }
    entered->setCharacter(who);

    // character notices where he stands
    who->setTile(entered);
    return true;
}

bool Tile::onLeave(Tile* /*destTile*/, Character* /*who*/) {
    // in P1 always true
    return true;
}
