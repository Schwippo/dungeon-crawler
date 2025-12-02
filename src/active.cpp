#include "../include/active.h"
#include "../include/passive.h"

// TO DO
// NEW METHOD FOR ADD AND DELETE

void Active::attach(Passive* p) {
    if(!p) return;
    if(std::find(listeners.begin(), listeners.end(), p) == listeners.end()){
        listeners.push_back(p);
    }
}

void Active::detach(Passive* p) {
    auto it = std::remove(listeners.begin(), listeners.end(), p);
    listeners.erase(it, listeners.end());
}

void Active::active() {
    for(auto * p : listeners) {
        if(p) p->notify();
    }
}
