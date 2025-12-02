#ifndef SWITCH_H
#define SWITCH_H

#include "floor.h"
#include "active.h"

class Switch : public Floor, public Active {
public:
    Switch(int r, int c);
    std::pair<bool, Tile*> onEnter(Character* who) override;
};

#endif // SWITCH_H
