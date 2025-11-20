#include "../include/dungeoncrawler.h"
#include "../include/level.h"
#include "../include/terminalui.h"
#include "../include/character.h"
#include "../include/tile.h"

DungeonCrawler::DungeonCrawler()
    : level(new Level()), ui(new TerminalUI()) {

    // Character kennt seine UI (Delegation)
    if (auto* p = level->getPlayer()) {
        p->setUI(ui); // Player mit UI verbinden
        //std::cout << "DEBUG: UI dem Player zugwiesen\n";
    } else {
        //std::cout << "DEBUG: getPlayer() == nullptr!\n";
    }
    ui->draw(level);
    std::cout.flush();
}

DungeonCrawler::~DungeonCrawler() {
    delete ui;
    delete level;
}

Level *DungeonCrawler::getLevel() const { return level; }

bool DungeonCrawler::turn() {
    //std::cout << "DEBUG: turn() gestartet\n";
    std::cout.flush();

    auto* player = level->getPlayer();
    if (!player) {
        //std::cout << "DEBUG: player == nullptr!\n";
        std::cout.flush();
        return false;
    }

    //std::cout << "DEBUG: Player existiert -> getNextMove()\n";

    // 1) Eingabe
    Input in = player->getNextMove();
    //std::cout << "DEBUG: getNextMove() aufgerufen";
    std::cout.flush();
    if (in.quit) return false;

    // 2) Zielkachel berechnen
    int r = player->getTile()->getRow() + in.dr;
    int c = player->getTile()->getColumn() + in.dc;

    auto* dest = level->getTile(r, c);

    // 3) Bewegung ausführen, falls innerhalb des levels
    if (dest) {
        player->getTile()->moveTo(dest, player);
    }

    // 4) Neu zeichnen
    ui->draw(level);
    return true;
}
