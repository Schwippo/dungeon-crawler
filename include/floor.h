#ifndef FLOOR_H
#define FLOOR_H

#include "tile.h"

class Floor : public Tile {
public:
    Floor(int r, int c);
    std::pair<bool, Tile*> onEnter(Character* who) override;
    bool onLeave(Tile* destTile, Character* who) override;
};



#endif //FLOOR_H
