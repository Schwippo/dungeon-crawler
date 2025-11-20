#ifndef LEVEL_H
#define LEVEL_H

#include <vector>

class Tile;
class Character;

class Level {
    int height{0};
    int width{0};

    std::vector<std::vector<Tile*>> grid;
    std::vector<Character*> characters;

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

    Character* getPlayer() const;
    const std::vector<Character*>& getCharacters() const;
};



#endif //LEVEL_H

