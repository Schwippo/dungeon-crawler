#ifndef CHARACTER_H
#define CHARACTER_H

#include "abstractController.h"
#include <string>

class Tile;
class Level;

class Character {
    std::string texture;
    Tile* tile;
    AbstractController* controller;

public:
    Character(const std::string& texture);
    std::string getTexture() const;

    Tile* getTile() const;
    void setTile(Tile* t);

    void setController(AbstractController* c);
    Input getNextMove();
};



#endif //CHARACTER_H
