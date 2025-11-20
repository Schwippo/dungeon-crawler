#include "../include/portal.h"

Portal::Portal(int r, int c)
    : Tile("O", r, c) {}

void Portal::setDestination(Tile* d) { destination = d; }
Tile* Portal::getDestination() const { return destination; }

std::pair<bool, Tile *> Portal::onEnter(Character *who) {
    return {destination != nullptr, destination};
}
