#ifndef PORTAL_H
#define PORTAL_H

#include "tile.h"

class Portal : public Tile {
    Portal* destination;

public:
    Portal(int r, int c);

    void setDestination(Portal* p);
    std::pair<bool, Tile*> onEnter(Character* who) override;
    bool onLeave(Tile* destTile, Character* who) override;
};



#endif //PORTAL_H
