#ifndef ABSTRACTUI_H
#define ABSTRACTUI_H

class Level;

// Eingabe-Struktur für Bewegung (row, col) und Beenden
struct Input {
    int dr{0};
    int dc{0};
    bool quit{false};
};

// Abstraktes UI-Interface
class AbstractUI {
public:
    virtual ~AbstractUI() = default;
    virtual void draw(Level* level) = 0;
    virtual Input move() = 0;
};



#endif //ABSTRACTUI_H
