#include "../include/character.h"

#include <iostream>

Character::Character(std::string texture)
    : texture(std::move(texture)) {}

const std::string& Character::getTexture() const { return texture; }

Tile* Character::getTile() const { return tile;}
void Character::setTile(Tile* t) { tile = t; }

void Character::setUI(AbstractUI* u) { ui = u; }

Input Character::getNextMove() {
    //std::cout << "DEBUG: getNextMove() erreicht\n";
    std::cout.flush();
    // Delegiert an UI, falls vorhanden, sonst keine Bewegung
    return ui ? ui->move() : Input{};
}
