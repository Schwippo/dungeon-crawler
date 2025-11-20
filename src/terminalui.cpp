#include "../include/terminalui.h"
#include "../include/level.h"
#include "../include/tile.h"

#include <iostream>
#include <limits>

void TerminalUI::draw(Level* level) {
    std::cout << "Aktuelles Level:\n\n";
    for (int r = 0; r < level->getHeight(); ++r) {
        for (int c = 0; c < level->getWidth(); ++c) {
            const Tile* t = level->getTile(r, c);
            std::cout << t->getTexture();
        }
        std::cout << "\n";
    }
    std::cout.flush();
}

Input TerminalUI::move() {
    std::cout.flush();
    Input in{};
    int v = -1;

    std::cout << "\nBitte eingeben (1.9, 5=stehen, 0=exit): ";
    std::cout.flush();

    if (!(std::cin >> v)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return in; // no movement
    }

    switch (v) {
    case 0: in.quit = true; break;
    case 1: in.dr = +1; in.dc = -1; break;
    case 2: in.dr = +1; in.dc =  0; break;
    case 3: in.dr = +1; in.dc = +1; break;
    case 4: in.dr =  0; in.dc = -1; break;
    case 5: in.dr =  0; in.dc =  0; break;
    case 6: in.dr =  0; in.dc = +1; break;
    case 7: in.dr = -1; in.dc = -1; break;
    case 8: in.dr = -1; in.dc =  0; break;
    case 9: in.dr = -1; in.dc = +1; break;
    default:
        std::cout << "Ungültige Eingabe\n";
        break;
    }
    return in;
}
