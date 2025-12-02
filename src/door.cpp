#include "../include/door.h"
#include "../include/character.h"

Door::Door(int r, int c) : Tile("X", r, c), isOpen(false) {
    texture = "X";
}

void Door::notify() {
    isOpen = !isOpen;
    texture = isOpen ? "/" : "X";
}

std::pair<bool, Tile*> Door::onEnter(Character* who) {
    if(isOpen) {
        return {true, nullptr}; // can be entered
    }
    return {false, nullptr}; // closed
}
