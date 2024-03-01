#include "Phase.h" // Include header file for Phase class

PhaseObserver Phase::observe; // Static member initialization for PhaseObserver object

Phase::Phase() {

}
void Phase::notify(Player* player, std::string phaseName, std::string message) {
    // Call the update method of the PhaseObserver object
    observe.update(player, phaseName, message);
}
