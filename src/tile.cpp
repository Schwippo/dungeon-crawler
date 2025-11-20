#include "../include/tile.h"

std::string Tile::getTexture() const {
    if (character) {
        extern const std::string& getCharacterTexture(const Character*);
        // Für P1 nur Rückgabe der Kachel
        // Wenn keine Figur: Platzhalter 'X'
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

    // 1) Darf aktuelle Kachel verlassen werden?
    if (!onLeave(destTile, who))
        return false;

    // 2) Zielkachel fragen, ob sie betreten werden darf
    auto[ok, altTile] = destTile->onEnter(who);
    if (!ok) return false;

    Tile* entered = altTile ? altTile : destTile;

    // 3) Zustandswechsel: Character von 'this' nach 'entered' bewegen
    if (this->character == who) {
        this->character = nullptr;
    }
    entered->setCharacter(who);

    // Character muss merken wo er jetzt steht
    who->setTile(entered);
    return true;
}

bool Tile::onLeave(Tile* /*destTile*/, Character* /*who*/) {
    // in P1 immer true
    return true;
}
