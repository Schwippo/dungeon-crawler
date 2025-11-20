#include "../include/switch.h"

Switch::Switch(int r, int c) : Floor(r, c) {
    texture = "?";
}

std::pair<bool, Tile*> Switch::onEnter(Character* who) {
    active(); // notifys all doors
    return Floor::onEnter(who);
}
