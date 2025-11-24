#include "../include/tile.h"

std::string Tile::getTexture() const {
    if (character)
        return character->getTexture();
    return texture;
}

bool Tile::hasCharacter() const { return character != nullptr; }

Character* Tile::getCharacter() const { return character; }
void Tile::setCharacter(Character* c) { character = c; }

int Tile::getRow() const { return row; }
int Tile::getColumn() const { return column; }

bool Tile::moveTo(Tile *destTile, Character *who) {
    if (!destTile || !who) return false;

    // 1) can tile be left?
    if (!onLeave(destTile, who))
        return false;

    // 2) ask if dest. tile can be entered
    auto[canEnter, teleportTile] = destTile->onEnter(who);
    if (!canEnter) return false;

    Tile* finalTile = teleportTile ? teleportTile : destTile;

    // 3) change: save character on new tile
    // clear old tile
    this->setCharacter(nullptr);

    // set new tile
    finalTile->setCharacter(who);

    // character notices where he stands
    who->setTile(finalTile);
    return true;
}

bool Tile::onLeave(Tile* /*destTile*/, Character* /*who*/) {
    // in P1 always true -> tile can always be left
    return true;
}
