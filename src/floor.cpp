#include "../include/floor.h"

Floor::Floor(int r, int c)
    : Tile(".", r, c) {}

std::pair<bool, Tile*> Floor::onEnter(Character* who) {
    return {true, nullptr};
}
