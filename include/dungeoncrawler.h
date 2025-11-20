#ifndef DUNGEONCRAWLER_H
#define DUNGEONCRAWLER_H

#include "abstractcontroller.h"
#include "abstractView.h"
#include "level.h"
#include "character.h"

#include <cstdlib>

class Level;
class AbstractController;
class Character;

class DungeonCrawler {
    Level* level;
    AbstractController* controller;

public:
    DungeonCrawler();
    ~DungeonCrawler();

    bool turn();

    Level* getLevel() const;
};



#endif //DUNGEONCRAWLER_H
