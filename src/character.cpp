#include "../include/character.h"
#include "../include/tile.h"

Character::Character(const std::string& texture)
    : texture(texture), tile(nullptr), controller(nullptr), lastMoveDirection({0, 0, false}) {}

std::string Character::getTexture() const { return texture; }

Tile* Character::getTile() const { return tile;}
void Character::setTile(Tile* t) { tile = t; }

void Character::setController(AbstractController* c) { controller = c; }

Input Character::getNextMove() {
    if(controller) {
        Input in = controller->move();
        lastMoveDirection = in;
        return in;
    }
    return {};
}
