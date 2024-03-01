#include "Subject.h" // Include the declaration of Subject class

Subject::Subject() {
	// Constructor: Initialize the list of observers
	observers = new std::list<Observer*>;
}

Subject::~Subject() {
	// Destructor: Deallocate memory for the list of observers
	delete observers;
}

void Subject::addObserver(Observer* o) {
	// Method to add an observer to the list
	observers->push_back(o);
}

void Subject::removeObserver(Observer* o) {
	// Method to remove an observer from the list
	for (std::list<Observer*>::iterator it = observers->begin(); it != observers->end(); it++) {
		if (*it == o) {
			observers->erase(it); // Remove the observer from the list
		}
	}
}

void Subject::notify(Observer* o) {
	// Method to notify a specific observer (not implemented)
	// TODO get a specific observer to notify
}

void Subject::notifyAll() {
	// Method to notify all observers
	std::list<Observer*>::iterator it = observers->begin(); // Iterator to traverse the list of observers

	for (; it != observers->end(); it++)
		(*it)->update(); // Call the update method for each observer
}
