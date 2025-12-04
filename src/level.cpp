#include "../include/level.h"
#include "../include/tile.h"
#include "../include/floor.h"
#include "../include/wall.h"
#include "../include/portal.h"
#include "../include/character.h"
#include "../include/pit.h"
#include "../include/ramp.h"
#include "../include/switch.h"
#include "../include/door.h"

#include <vector>


// help function -> create tile based on one symbol
static Tile* createBasicTile(char ch, int r, int c)
{
    switch (ch)
    {
    case '#': return new Wall(r, c);
    case '.': return new Floor(r, c);
    case '_': return new Pit(r, c);
    case '<': return new Ramp(r, c);
    case 'O': return new Portal(r, c);
    case '?': return new Switch(r, c);
    case 'X': return new Door(r, c);     // closed door
    case '/': {                          // open
        Door* d = new Door(r, c);
        d->notify();                     // toggle → open
        return d;
    }
    default:
        return new Floor(r, c);
    }
}

Level::Level() : height(0), width(0), player(nullptr) {
    // example
    const std::vector<std::string> map = {
        "##########",
        "#O.....<.#",
        "#..../...#",
        "#...O....#",
        "#?.......#",
        "#..../...#",
        "##########",
        "#O.......#",
        "#....O<..#",
        "##########"
    };

    height = map.size();
    width = map[0].size();
    grid.resize(height, std::vector<Tile*>(width, nullptr));

    std::vector<Portal*> portals;
    std::vector<Switch*> switches;
    std::vector<Door*> doors;

    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            char ch = map[r][c];

            switch (ch) {
            case 'O': {
                // Portal with type

                int type = portals.size() / 3;
                // Portal 0 & 1 -> Type 0
                // Portal 2 & 3 -> Type 1
                // Portal 4 & 5 -> Type 2 ...

                Portal* p = new Portal(r, c, type);
                grid[r][c] = p;
                portals.push_back(p);
                break;
            }
            case '?': {
                Switch* s = new Switch(r, c);
                grid[r][c] = s;
                switches.push_back(s);
                break;
            }
            case 'X': {
                Door* d = new Door(r, c);
                grid[r][c] = d;
                doors.push_back(d);
                break;
            }
            case '/': {
                Door* d = new Door(r, c);
                d->notify(); // open door
                grid[r][c] = d;
                doors.push_back(d);
                break;
            }
            default:
                grid[r][c] = createBasicTile(ch, r, c);
                break;
            }
        }
    }

    // set player
    player = new Character("@");
    placeCharacter(player, 1, 1);

    // portal pairs (0-1), (2-3), (4-5), ...
    for(size_t i = 0; i + 1 < portals.size(); i += 2) {
        portals[i]->setDestination(portals[i + 1]);
        portals[i + 1]->setDestination(portals[i]);
    }

    // switch -> door connect
    for(auto* s : switches) {
        for(auto* d: doors)
            s->attach(d);
    }
}

Level::~Level() {
    clear();
}

void Level::clear() {
    for(auto& row : grid)
        for(Tile* t : row)
            delete t;

    grid.clear();

    delete player;
    player = nullptr;
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

    t->setCharacter(c);
    c->setTile(t);
}

// copy constructor
Level::Level(const Level& other) : height(0), width(0), player(nullptr) {
    copyFrom(other);
}

Level& Level::operator=(const Level& other) {
    if(this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

void Level::copyFrom(const Level& other) {
    height = other.height;
    width = other.width;

    grid.resize(height, std::vector<Tile*>(width, nullptr));

    std::vector<Portal*> portalsCopy;
    std::vector<Portal*> portalsOriginal;
    std::vector<Door*> doorsCopy;
    std::vector<Switch*> switchesCopy;

    // copy tiles
    for(int r = 0; r < height; ++r) {
        for(int c = 0; c < width; ++c) {

            Tile* src = other.grid[r][c];
            Tile* dest = nullptr;

            if (auto f = dynamic_cast<Floor*>(src))
                dest = new Floor(r, c);

            else if (auto w = dynamic_cast<Wall*>(src))
                dest = new Wall(r, c);

            else if (auto p = dynamic_cast<Portal*>(src)) {
                int type = p->getPortalType();
                Portal* copy = new Portal(r, c, type);
                dest = copy;
                portalsCopy.push_back(copy);
                portalsOriginal.push_back(p);
            }

            else if (auto s = dynamic_cast<Switch*>(src)) {
                Switch* sc = new Switch(r, c);
                dest = sc;
                switchesCopy.push_back(sc);
            }

            else if (auto d = dynamic_cast<Door*>(src)) {
                Door* dc = new Door(r, c);
                if (d->isOpenDoor())
                    dc->notify();
                dest = dc;
                doorsCopy.push_back(dc);
            }

            else if (auto pit = dynamic_cast<Pit*>(src))
                dest = new Pit(r, c);

            else if (auto ra = dynamic_cast<Ramp*>(src))
                dest = new Ramp(r, c);

            else
                dest = new Floor(r, c);

            grid[r][c] = dest;
            }
        }

        // restore portal connections
        for (size_t i = 0; i < portalsCopy.size() && i < portalsOriginal.size(); i++) {

            Portal* original = portalsOriginal[i];
            Portal* copy = portalsCopy[i];

            Portal* originalDest = original->getDestination();
            if (!originalDest) continue;

            // define goal index
            for (size_t j = 0; j < portalsOriginal.size(); j++) {
                if (portalsOriginal[j] == originalDest) {
                    copy->setDestination(portalsCopy[j]);
                    break;
                }
            }
        }

        // restore switch-door connections
        for(auto* s : switchesCopy)
            for (auto* d : doorsCopy)
                s->attach(d);

        // copy player
        if(other.player) {
            player = new Character(other.player->getTexture());
            int playerRow = other.player->getTile()->getRow();
            int playerCol = other.player->getTile()->getColumn();
            placeCharacter(player, playerRow, playerCol);
        }
}
