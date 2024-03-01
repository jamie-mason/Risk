#ifndef OBSERVER_H_
#define OBSERVER_H_

class Observer {
public:
    virtual void update() = 0; // Pure virtual function to be implemented by derived classes
};
#endif