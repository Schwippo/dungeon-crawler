#include "../include/wall.h"


Wall::Wall(int r, int c)
    : Tile("#", r, c) {}

std::pair<bool, Tile *> Wall::onEnter(Character *who) {
    return {false, nullptr};
}
