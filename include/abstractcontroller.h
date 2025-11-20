#ifndef ABSTRACTCONTROLLER_H
#define ABSTRACTCONTROLLER_H

// Eingabe-Struktur für Bewegung (row, col) und Beenden
struct Input {
    int dr{0};
    int dc{0};
    bool quit{false};
};

class AbstractController {
public:
    virtual ~AbstractController() = default;
    virtual Input move() = 0;
};

#endif // ABSTRACTCONTROLLER_H
