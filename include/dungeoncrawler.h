#ifndef DUNGEONCRAWLER_H
#define DUNGEONCRAWLER_H

#include "abstractUI.h"
#include "terminalUI.h"
#include "level.h"
#include "character.h"
#include "tile.h"

#include <cstdlib>

class Level;
class AbstractUI;
class Input;
class Character;

class DungeonCrawler {
    Level* level;
    AbstractUI* ui;

public:
    DungeonCrawler();
    ~DungeonCrawler();

    // genau eine Runde, false bei Spielende
    bool turn();

    Level* getLevel() const;
};



#endif //DUNGEONCRAWLER_H
