#include "../include/level.h"
#include "../include/tile.h"
#include "../include/floor.h"
#include "../include/wall.h"
#include "../include/portal.h"
#include "../include/character.h"

#include <cassert>

Level::Level() {
    // example
    const std::vector<std::string> l = {
        "##########",
        "#O.......#",
        "#........#",
        "#........#",
        "#........#",
        "#........#",
        "##########",
        "#O.......#",
        "#........#",
        "##########"
    };
    height = static_cast<int>(l.size());
    width = static_cast<int>(l.front().size());
    grid.assign(height, std::vector<Tile*>(width, nullptr));

    // create tiles
    std::vector<Portal*> portals;
    for (int r = 0; r < height; ++r) {
        assert((int)l[r].size() == width);
        for (int c = 0; c < width; ++c) {
            char ch = l[r][c];
            Tile* t = nullptr;
            switch (ch) {
            case '#': t = new Wall(r, c); break;
            case '.': t = new Floor(r, c); break;
            case 'O': {
                auto* p = new Portal(r, c);
                portals.push_back(p);
                t = p; break;
            }
            default:  t = new Floor(r, c); break;
            }
            grid[r][c] = t;
        }
    }

    // pair portals
    for (size_t i = 0; i < portals.size(); i+= 2) {
        portals[i]->setDestination(portals[i+1]);
        portals[i+1]->setDestination(portals[i]);
    }

    // set character on start
    Character* hero = new Character("X");
    characters.push_back(hero);
    placeCharacter(hero, 2, 2);
}

Level::~Level() {
    for (auto& row : grid) {
        for (Tile* t : row) delete t;
    }
    for (Character* c : characters) delete c;
}

int Level::getHeight() const { return height; }
int Level::getWidth() const { return width; }

Tile* Level::getTile(int r, int c) {
    if (r < 0 || c < 0 || r >= height || c >= width) return nullptr;
    return grid[r][c];
}

const Tile *Level::getTile(int r, int c) const {
    if (r < 0 || c < 0 || r >= height || c >= width) return nullptr;
    return grid[r][c];
}

void Level::placeCharacter(Character* c, int r, int col) {
    Tile* t = getTile(r, col);
    if (!t) return;

    // clear old tile
    if (c->getTile()) c->getTile()->setCharacter(nullptr);

    // set new tile
    t->setCharacter(c);
    c->setTile(t);
}

Character* Level::getPlayer() const { return characters.empty() ? nullptr : characters.front(); }
const std::vector<Character *> &Level::getCharacters() const { return characters; }

