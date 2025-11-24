#include "../include/dungeoncrawler.h"
#include <iostream>

DungeonCrawler::DungeonCrawler() {
    ui = new TerminalUI();
    Level* tmp = new Level();

    // test copy constructor
    level = new Level(*tmp);

    // test assignment operator
    *level = *tmp;
    delete tmp;

    // set player-controller
    if(level->getPlayer())
        level->getPlayer()->setController(ui);
}

DungeonCrawler::~DungeonCrawler() {
    delete level;
    delete ui;
}

bool DungeonCrawler::turn() {
    Character* player = level->getPlayer();

    if (!player)
        return false;

    // take input
    Input in = player->getNextMove();
    if (in.quit)
        return false;

    // 2) dest. tile
    Tile* currentTile = player->getTile();
    if(!currentTile)
        return false;

    int r = currentTile->getRow() + in.dr;
    int c = currentTile->getColumn() + in.dc;

    Tile* destinationTile = level->getTile(r, c);

    // 3) movement if in level
    if (destinationTile)
        currentTile->moveTo(destinationTile, player);

    return true;
}

void DungeonCrawler::run() {
    bool running = true;

    while(running) {
        ui->draw(level);
        running = turn();
    }
}
