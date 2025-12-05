#include "../include/portal.h"

Portal::Portal(int r, int c, int type)
    : Tile("O", r, c), destination(nullptr), portalType(type) {}

void Portal::setDestination(Portal* p) { destination = p; }

std::pair<bool, Tile *> Portal::onEnter(Character* who) {
    if(destination) {
        return {true, destination};
    }
    return {true, destination};
}

bool Portal::onLeave(Tile* /*dest*/, Character* /*who*/) {
    return true; // can always be left
}
