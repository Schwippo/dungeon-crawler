#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <string>

// Forward declaration
class Tile;
class Character;

class Level {
    int height{0};
    int width{0};

    // 2d grid aus Tile*
    std::vector<std::vector<Tile*>> grid;

    // character in levels - in P1 mindestens einen
    std::vector<Character*> characters;

public:
    // standard map (>= 4x4, portal pair, one character)
    Level();
    // delete Tiles and Characters
    ~Level();

    int getHeight() const;
    int getWidth() const;

    Tile* getTile(int r, int c);
    const Tile* getTile(int r, int c) const;

    // Figur platzieren (ohne onEnter, nur Initialisierung)
    void placeCharacter(Character* c, int r, int col);

    // Zugriff auf erste Figur in P1
    Character* getPlayer() const;
    const std::vector<Character*>& getCharacters() const;
};



#endif //LEVEL_H

