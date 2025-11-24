#include "../include/terminalui.h"
#include "../include/level.h"
#include "../include/tile.h"

#include <iostream>

void TerminalUI::draw(Level* level) {
    if(!level) return;
    std::cout << "Aktuelles Level:\n\n";

    for (int r = 0; r < level->getHeight(); ++r) {
        for (int c = 0; c < level->getWidth(); ++c) {
            const Tile* t = level->getTile(r, c);
            std::cout << t->getTexture();
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

Input TerminalUI::move() {
    std::cout << "Bitte Zug eingeben (w/a/s/d, q = Exit): ";

    char character;
    std::cin >> character;

    Input in;

    switch (character) {
    case 'w': in.dr = -1; break;
    case 's': in.dr = +1; break;
    case 'a': in.dr = -1; break;
    case 'd': in.dr = +1; break;

    default:
        std::cout << "Ungültige Eingabe\n";
        break;
    }
    return in;
}
