#include "../include/floor.h"

Floor::Floor(int r, int c)
    : Tile(".", r, c) {}

std::pair<bool, Tile*> Floor::onEnter(Character* who) {
    return {true, nullptr}; // can always be entered
}

bool Floor::onLeave(Tile* /*dest*/, Character* /*who*/) {
    return true; // can always be left
}
