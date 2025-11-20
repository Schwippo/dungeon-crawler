#ifndef PORTAL_H
#define PORTAL_H

#include "tile.h"

class Portal : public Tile {
    Tile* destination{nullptr};

public:
    Portal(int r, int c);

    void setDestination(Tile* d);
    Tile* getDestination() const;

    std::pair<bool, Tile*> onEnter(Character* who) override;
};



#endif //PORTAL_H
