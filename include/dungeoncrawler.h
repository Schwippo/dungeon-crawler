#ifndef DUNGEONCRAWLER_H
#define DUNGEONCRAWLER_H

#include "level.h"
#include "terminalui.h"


class DungeonCrawler {
private:
    Level* level;
    TerminalUI* ui;

    bool turn();

public:
    DungeonCrawler();
    ~DungeonCrawler();

    void run();
};



#endif //DUNGEONCRAWLER_H
