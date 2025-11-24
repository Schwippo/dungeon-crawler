#ifndef ACTIVE_H
#define ACTIVE_H
#include <vector>

class Passive;

class Active {
private:
    std::vector<Passive*> listeners;

public:
    virtual ~Active() = default;

    void attach(Passive* p);
    void detach(Passive* p);
    void active(); // calls notify() for all passive objects
};

#endif // ACTIVE_H
