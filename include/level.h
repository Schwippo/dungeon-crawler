#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include "tile.h"
#include "character.h"

class Level {
    int height;
    int width;

    std::vector<std::vector<Tile*>> grid;
    Character* player;

    void clear();
    void copyFrom(const Level& other);

public:
    Level();
    Level(const Level& other);
    Level& operator=(const Level& other);
    ~Level();

    int getHeight() const;
    int getWidth() const;

    Tile* getTile(int r, int c);
    const Tile* getTile(int r, int c) const;

    void placeCharacter(Character* c, int r, int col);

    Character* getPlayer() const { return player; }
    // const std::vector<Character*>& getCharacters() const;
};



#endif //LEVEL_H

