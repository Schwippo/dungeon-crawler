#ifndef DUNGEONCRAWLER_H
#define DUNGEONCRAWLER_H

#include "level.h"
#include "abstractView.h"
#include "abstractcontroller.h"

class GraphicalUI;

class DungeonCrawler {
private:
    Level* level;
    AbstractView* view;
    AbstractController* controller;

public:
    DungeonCrawler();
    ~DungeonCrawler();

    bool turn();
    Level* getLevel() { return level; }
};



#endif //DUNGEONCRAWLER_H
