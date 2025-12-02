#include "../include/dungeoncrawler.h"
#include "../include/graphicalui.h"
#include "../include/character.h"
#include "../include/tile.h"

DungeonCrawler::DungeonCrawler() : level(nullptr), view(nullptr), controller(nullptr) {

    Level* tmp = new Level();
    level = new Level(*tmp); // test copy contructor
    *level = *tmp; // test assignment operator
    delete tmp;

    // create graphicalUI
    GraphicalUI* gui = new GraphicalUI(this);
    view = gui;
    controller = gui;

    // connect player to controller
    if(level->getPlayer())
        level->getPlayer()->setController(controller);

    // draw instantly
    view->draw(level);
}

DungeonCrawler::~DungeonCrawler() {
    delete level;
    delete view;
}

bool DungeonCrawler::turn() {

    if (!level || !controller)
        return false;

    Character* player = level->getPlayer();
    if(!player) return false;

    // GUI gives input
    Input in = controller->move();

    // quit?
    if (in.quit)
        return false;

    // save direction in character
    player->setMoveDirection(in);

    // 2) dest. tile
    Tile* currentTile = player->getTile();
    if(!currentTile)
        return false;

    int newRow = currentTile->getRow() + in.dr;
    int newCol = currentTile->getColumn() + in.dc;

    // check
    if(newRow < 0 || newRow >= level->getHeight() ||
       newCol < 0 || newCol >= level->getWidth()) {
        view->draw(level);
        return true;
    }

    Tile* destTile = level->getTile(newRow, newCol);

    // 3) movement if in level
    if (destTile) {
        currentTile->moveTo(destTile, player);
    }

    view->draw(level);
    return true;
}
