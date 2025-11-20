#ifndef PASSIVE_H
#define PASSIVE_H

class Passive {
public:
    virtual ~Passive() = default;
    virtual void notify() = 0;
};

#endif // PASSIVE_H
