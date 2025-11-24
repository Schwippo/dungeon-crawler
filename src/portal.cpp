#include "../include/portal.h"

Portal::Portal(int r, int c)
    : Tile("O", r, c), destination(nullptr){}

void Portal::setDestination(Portal* p) { destination = p; }

std::pair<bool, Tile *> Portal::onEnter(Character *who) {
    return {true, destination}; // can always be entered
}

bool Portal::onLeave(Tile* /*dest*/, Character* /*who*/) {
    return true; // can always be left
}
