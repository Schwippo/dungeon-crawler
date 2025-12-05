#include "../include/switch.h"
#include "../include/character.h"

Switch::Switch(int r, int c) : Floor(r, c) {
    texture = "?";
}

std::pair<bool, Tile*> Switch::onEnter(Character* who) {
    active(); // notifys all doors
    return {true, nullptr};
}

bool Switch::onLeave(Tile*, Character*) {
    return true;
}
