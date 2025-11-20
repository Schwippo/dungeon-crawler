#include "../include/pit.h"
# include "../include/character.h"
#include "../include/ramp.h"

Pit::Pit(int r, int c) : Tile(r, c) {
    texture = "_";
}

std::pair<bool, Tile*> Pit::onEnter(Character* who) {
    return {true, nullptr};
}

bool Pit::onLeave(Tile* dest, Character* who) {
    if(dynamic_cast<Pit*>(dest)) return true;
    if(dynamic_cast<Ramp*>(dest)) return true;
    return false;
}
