#ifndef DOOR_H
#define DOOR_H

#include "wall.h"
#include "passive.h"

class Door : public Wall, public Passive {
private:
    bool open;

public:
    Door(int r, int c);

    void notify() override;
    std::pair<bool, Tile*> onEnter(Character* who) override;
    // std::string getTexure() const;
};

#endif // DOOR_H
