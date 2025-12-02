#ifndef DOOR_H
#define DOOR_H

#include "tile.h"
#include "passive.h"

class Door : public Tile, public Passive {
private:
    bool isOpen;

public:
    Door(int r, int c);

    void notify() override;
    std::pair<bool, Tile*> onEnter(Character* who) override;

    // doors always can be left
    bool onLeave(Tile* dest, Character* who) override { return true; }

    bool isOpenDoor() const { return isOpen; }
};

#endif // DOOR_H
