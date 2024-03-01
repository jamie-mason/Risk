#ifndef SUBJECT_H_
#define SUBJECT_H_

#include "Observer.h" // Include the declaration of Observer class
#include <list> // Include list library for std::list
#include <iostream>

class Observer;
//prevent circular dependency



class Subject {
public:
    Subject(); // Constructor
    ~Subject(); // Destructor
    void addObserver(Observer* o); // Method to add an observer to the list
    void removeObserver(Observer* o); // Method to remove an observer from the list
    void notify(Observer* o); // Method to notify a specific observer (not implemented)
    void notifyAll(); // Method to notify all observers

private:
    std::list<Observer*>* observers; // List to store pointers to observers
};

#endif 
