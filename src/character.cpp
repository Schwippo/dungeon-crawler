#include "../include/character.h"

#include <iostream>

Character::Character(std::string texture)
    : texture(std::move(texture)) {}

const std::string& Character::getTexture() const { return texture; }

Tile* Character::getTile() const { return tile;}
void Character::setTile(Tile* t) { tile = t; }

void Character::setController(AbstractController* c) { controller = c; }

Input Character::getNextMove() {
    std::cout.flush();
    return controller ? controller->move() : Input{};
}
