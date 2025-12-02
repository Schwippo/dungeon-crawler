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

    Input lastMoveDirection{};

public:
    Character(const std::string& texture);
    std::string getTexture() const;

    Tile* getTile() const;
    void setTile(Tile* t);

    void setController(AbstractController* c);
    Input getNextMove();

    void setMoveDirection(const Input& in) { lastMoveDirection = in; }
    Input getMoveDirection() const { return lastMoveDirection; }
};



#endif //CHARACTER_H
