#ifndef PORTAL_H
#define PORTAL_H

#include "tile.h"

class Portal : public Tile {
private:
    Portal* destination;
    int portalType;

public:
    Portal(int r, int c, int type = 0);

    void setDestination(Portal* p);
    std::pair<bool, Tile*> onEnter(Character* who) override;
    bool onLeave(Tile* destTile, Character* who) override;

    int getPortalType() const { return portalType; }

    Portal* getDestination() const { return destination; }
};



#endif //PORTAL_H
