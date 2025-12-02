#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <string>

class Tile;
class Character;
class Portal;
class Switch;
class Door;

class Level {
private:
    int height;
    int width;

    std::vector<std::vector<Tile*>> grid;
    Character* player;

    void clear();
    void copyFrom(const Level& other);

public:
    Level();
    ~Level();

    int getHeight() const;
    int getWidth() const;

    Tile* getTile(int r, int c);
    const Tile* getTile(int r, int c) const;

    void placeCharacter(Character* c, int r, int col);
    Character* getPlayer() const { return player; }

    // copying
    Level(const Level& other);
    Level& operator=(const Level& other);
};



#endif //LEVEL_H

