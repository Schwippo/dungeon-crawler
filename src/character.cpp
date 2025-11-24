#include "../include/character.h"

Character::Character(const std::string& texture)
    : texture(texture), tile(nullptr), controller(nullptr) {}

std::string Character::getTexture() const { return texture; }

Tile* Character::getTile() const { return tile;}
void Character::setTile(Tile* t) { tile = t; }

void Character::setController(AbstractController* c) { controller = c; }

Input Character::getNextMove() {
    if(controller)
        return controller->move();
    return {};
}
