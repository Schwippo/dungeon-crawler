#include "../include/dungeoncrawler.h"
#include "../include/level.h"
#include "../include/terminalui.h"
#include "../include/character.h"
#include "../include/tile.h"
#include <iostream>

DungeonCrawler::DungeonCrawler()
    : level(new Level()), controller(new TerminalUI()) {

    if (auto* p = level->getPlayer()) {
        p->setController(controller);
    }
    controller->draw(level);
    std::cout.flush();
}

DungeonCrawler::~DungeonCrawler() {
    delete controller;
    delete level;
}

Level *DungeonCrawler::getLevel() const { return level; }

bool DungeonCrawler::turn() {
    std::cout.flush();

    auto* player = level->getPlayer();
    if (!player) {
        std::cout.flush();
        return false;
    }

    // input
    Input in = player->getNextMove();
    std::cout.flush();
    if (in.quit) return false;

    // 2) dest. tile
    int r = player->getTile()->getRow() + in.dr;
    int c = player->getTile()->getColumn() + in.dc;

    auto* dest = level->getTile(r, c);

    // 3) movement if in level
    if (dest) {
        player->getTile()->moveTo(dest, player);
    }

    // 4) new drawing
    controller->draw(level);
    return true;
}
