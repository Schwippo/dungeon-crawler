#include "../include/pit.h"
#include "../include/ramp.h"
# include "../include/character.h"

Pit::Pit(int r, int c) : Tile("_", r, c) {}

std::pair<bool, Tile*> Pit::onEnter(Character* who) {
    return {true, nullptr}; // can always be entered
}

bool Pit::onLeave(Tile* dest, Character* who) {
    // can only be left to pit or ramp
    if(dynamic_cast<Pit*>(dest)) return true;
    if(dynamic_cast<Ramp*>(dest)) return true;
    return false;
}
