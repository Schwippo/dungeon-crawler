#include "../include/ramp.h"
#include "../include/character.h"

Ramp::Ramp(int r, int c) : Tile("<", r, c) {
    texture = "<";
}

std::pair<bool, Tile*> Ramp::onEnter(Character* who) {
    return {true, nullptr}; // can always be entered
}

bool Ramp::onLeave(Tile*, Character*) {
    return true; // can always be left
}
