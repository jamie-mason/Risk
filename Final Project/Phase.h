#ifndef PHASE_H_
#define PHASE_H_

#include "Subject.h"
#include "PhaseObserver.h"

class Subject;
class PhaseObserver;
//prevent circular dependency

class Phase : public Subject {

private:
	static PhaseObserver observe;

public:
	Phase();
	static void notify(Player*, std::string, std::string);

};

#endif 