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


// help function -> create tile based on one symbol
static Tile* createTile(char ch, int r, int c)
{
    switch (ch)
    {
    case '#': return new Wall(r, c);
    case '.': return new Floor(r, c);
    case 'O': return new Portal(r, c);
    case '?': return new Switch(r, c);
    case 'X': return new Door(r, c);     // closed
    case '/': {                          // open
        Door* d = new Door(r, c);
        d->notify();                     // toggle 1x → open
        return d;
    }
    case '_': return new Pit(r, c);
    case '<': return new Ramp(r, c);

    default:
        return new Floor(r, c);
    }
}

Level::Level() : height(0), width(0), player(nullptr) {
    // example
    const std::vector<std::string> map = {
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
/*          case '#': {
                Tile* t = createTile('#', r, c);
                t = new Wall(r, c); break;
            }
            case '.': {
                Tile* t = createTile('.', r, c);
                t = new Floor(r, c); break;
            }
*/
            case 'O': {
                // Portal
                Tile* t = createTile('O', r, c);
                grid[r][c] = t;
                portals.push_back(dynamic_cast<Portal*>(t));
                break;
            }
            case '?': {
                Tile* t = createTile('?', r, c);
                grid[r][c] = t;
                switches.push_back(dynamic_cast<Switch*>(t));
            }
            case 'X': {
                Tile* t = createTile(ch, r, c);
                grid[r][c] = t;
                doors.push_back(dynamic_cast<Door*>(t));
            }
            case '/': {
                Tile* t = createTile(ch, r, c);
                grid[r][c] = t;
                doors.push_back(dynamic_cast<Door*>(t));
            }
            default:  {
                Tile* t = createTile(ch, r, c);
                grid[r][c] = t;new Floor(r, c); break;}
            }
            if (r == 1 && c == 1) {
                player = new Character("@");
                placeCharacter(player, r, c);
            }
        }
    }

    // connect portals
    if(portals.size() == 2) {
        portals[0]->setDestination(portals[1]);
        portals[1]->setDestination(portals[0]);
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
    std::vector<std::pair<int, int>> originalPortalPositions;
    std::vector<Door*> doorsCopy;
    std::vector<Switch*> switchesCopy;

    // copy tiles
    for(int r = 0; r < height; ++r) {
        for(int c = 0; c < width; ++c) {
            Tile* src = other.grid[r][c];
            Tile* copy = nullptr;

            // identify type
            if(dynamic_cast<Floor*>(src)) copy = new Floor(r,c);
            else if (dynamic_cast<Wall*>(src)) copy = new Wall(r, c);
            else if (dynamic_cast<Portal*>(src)) {
                copy = new Portal(r, c);
                portalsCopy.push_back(dynamic_cast<Portal*>(copy));
                originalPortalPositions.push_back({r,c});
            }
            else if (dynamic_cast<Switch*>(src)) {
                copy = new Switch(r, c);
                switchesCopy.push_back(dynamic_cast<Switch*>(copy));
            }
            else if (dynamic_cast<Door*>(src)) {
                Door* d = new Door(r, c);
                // take door condition
                if (src->getTexture() == "/")
                    d->notify();
                copy = d;
                doorsCopy.push_back(d);
            }
            else if (dynamic_cast<Pit*>(src)) copy = new Pit(r, c);
            else if (dynamic_cast<Ramp*>(src)) copy = new Ramp(r, c);
            else copy = new Floor(r, c);

            grid[r][c] = copy;
            }
        }

        // restore portal connections
        if(portalsCopy.size() == 2) {
            portalsCopy[0]->setDestination(portalsCopy[1]);
            portalsCopy[1]->setDestination(portalsCopy[0]);
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
