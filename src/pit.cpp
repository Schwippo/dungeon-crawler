#include "../include/pit.h"
#include "../include/ramp.h"
# include "../include/character.h"

Pit::Pit(int r, int c) : Tile("_", r, c) {}

std::pair<bool, Tile*> Pit::onEnter(Character* who) {
    if(who) {
        who->setTile(nullptr); // character sneaks into tile
    }
    setCharacter(nullptr);
    return {true, nullptr};
}

bool Pit::onLeave(Tile* dest, Character* who) {
    // can only be left to pit or ramp
    return dynamic_cast<Pit*>(dest) || dynamic_cast<Ramp*>(dest);
}
