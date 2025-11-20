#include "../include/door.h"

Door::Door(int r, int c) : Wall(r, c), open(false) {
    texture = "X";
}

void Door::notify() {
    open = !open;
    texture = open ? "/" : "X";
}

std::pair<bool, Tile*> Door::onEnter(Character* who) {
    if(!open) {
        return {false, nullptr};
    }
    return {true, nullptr};
}
