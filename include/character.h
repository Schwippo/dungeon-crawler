#ifndef CHARACTER_H
#define CHARACTER_H

#include "abstractController.h"
#include <string>

class Tile;
class AbstractController;

class Character {
    std::string texture;
    Tile* tile{nullptr};
    AbstractController* controller{nullptr};

public:
    explicit Character(std::string texture);
    const std::string& getTexture() const;

    Tile* getTile() const;
    void setTile(Tile* t);

    void setController(AbstractController* c);
    Input getNextMove();
};



#endif //CHARACTER_H
