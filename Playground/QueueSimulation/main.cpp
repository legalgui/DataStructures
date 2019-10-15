// Sebastian Galguera
// Code to implement Queue Simulation System

#include <time.h>

// General helpers
#include "ConsoleUtilities.hpp"
namespace output = consoleutilities::output;

// Problem specifics
#include "PriorityHandler.hpp"
using queuesimulationutilities::PriorityHandler;

#include "Event.hpp"
using queuesimulationutilities::Event;

#include "Probabilities.hpp"
namespace probs = queuesimulationutilities::probabilities;

// Data structures
#include "../../Structures/Queue/Queue.hpp"
using datastruct::Queue;

// Avoiding macros
namespace queuesimulationdata{
  class Specs{
  public:
    static constexpr int NUMBER_OF_TRUCKS { 16 };
    static constexpr int TIME_OF_START { 660 };
    static constexpr int TIME_OF_END { 1260 };
    static constexpr double TIME_INTERVAL { 1 };

    static constexpr double COST_PER_PERSON_EXTRA_TIME { 37.5 };
    static constexpr double COST_PER_PERSON_NORMAL_TIME { 25.0 };
    static constexpr double COST_PER_TRUCK_IN_QUEUE { 50.0 };
    static constexpr double COST_PER_HOUR_OF_WAREHOUSE { 500.0 };
    static constexpr int NUMBER_OF_PEOPLE { 4 };
    static int id;
  };
};

typedef queuesimulationdata::Specs Specs;
int Specs::id {0};

void nextStep(double &, double &, double &);
void printCosts(const double &, const double &);

int main(){
  output::printHeader("QUEUE SIMULATOR");

  // Flags
  bool hourOfArrivalHasPassed { true };
  bool hadLunch { false };

  // Counters
  double limitCount { 0 };

  // Specifiers
  double nextArrival { 0 };
  double hourOfNextArrival { 660 };
  double durationOfEvent { 0 };

  // Accumulators
  double timeWastedInQueue { 0 };
  double timeWastedByStaff { 0 };

  // Bay
  Queue<Event *> * bay { new Queue<Event *>() };
  PriorityHandler<Event *> ph(bay);

  // First event
  Event * e { new Event("First case", Specs::id++) };
  e->setTimeOfArrival(660);
  e->setDuration(20);
  ph.syncEnqueue(e);

  // Start 11:00 AM
  for(int clock = Specs::TIME_OF_START; clock < Specs::TIME_OF_END; clock += Specs::TIME_INTERVAL){
    std::cout << "Current time: ";
    output::printTime(clock);

    if(!bay->empty()){
      if(clock == bay->front()->getInfo()->getTimeOfEventEnd()){
        // Penalize everything but lunch time
        if(!(bay->front()->getInfo()->getEventType() == "Lunch")){
          timeWastedInQueue += bay->front()->getInfo()->getTimeWastedInQueue();
          timeWastedByStaff += bay->front()->getInfo()->getTimeWastedByStaff();
        }
        std::cout << "Exits" << std::endl;
        std::cout << *bay->dequeue()->getInfo() << std::endl;
        std::cout << "Number of events in queue: " << bay->size() << std::endl;
      }
    }

    // Getting the next arrival
    if(hourOfArrivalHasPassed){
      nextStep(nextArrival, hourOfNextArrival, durationOfEvent);
      hourOfArrivalHasPassed = false;
    }

    // Lunch special case
    if(clock >= 900 && !hadLunch){
      Event * e { new Event("Lunch", 0) };
      e->setTimeOfArrival(860);
      e->setDuration(30);
      ph.syncEnqueue(e);
      std::cout << "Enters " << std::endl;
      std::cout << *e << std::endl;
      hadLunch = true;
    }

     if(clock == hourOfNextArrival && limitCount < Specs::NUMBER_OF_TRUCKS){
       Event * e { new Event("Truck Event", Specs::id++) };
       e->setTimeOfArrival(hourOfNextArrival);
       e->setDuration(durationOfEvent);
       ph.syncEnqueue(e);
       std::cout << "ENTERS " << std::endl;
       std::cout << *e << std::endl;
       hourOfArrivalHasPassed = true;
       limitCount++;
     }

 }

 // PRINT THE REMAINING QUEUE IF THERE IS ANY
 for(int i = 0; i < bay->size(); i++){
   std::cout << *bay->dequeue()->getInfo() << std::endl;
 }

 // PRINT THE TOTALS
 std::cout << "\nResults\n" << std::endl;

 // CALCULATE THE NUMBER OF HOURS
 double activeHours = (Specs::TIME_OF_END - Specs::TIME_OF_START)/60;

 // PRINTING THE COSTS AND TOTAL
 printCosts(activeHours, timeWastedInQueue);

 delete bay;
 return 0;
}

void printCosts(const double &activeHours, const double &timeWastedInQueue){
  std::cout << "Cost of warehouse active hours: " << "$" <<
  (activeHours * Specs::COST_PER_HOUR_OF_WAREHOUSE) << std::endl;

  std::cout << "Cost of personnel normal hours: " << "$" <<
  (activeHours * Specs::COST_PER_PERSON_NORMAL_TIME*Specs::NUMBER_OF_PEOPLE) << std::endl;

  std::cout << "Cost of personnel extra houss: " << "$" <<
  (0 * Specs::COST_PER_PERSON_EXTRA_TIME * Specs::NUMBER_OF_PEOPLE) << std::endl;

  std::cout << "Cost of trucks waiting in queue: " << "$" <<
  (timeWastedInQueue/60 * Specs::COST_PER_TRUCK_IN_QUEUE) << std::endl;

  std::cout << "Total: " << "$" << (activeHours * Specs::COST_PER_HOUR_OF_WAREHOUSE +
  activeHours * Specs::COST_PER_PERSON_NORMAL_TIME * Specs::NUMBER_OF_PEOPLE +
  0 * Specs::COST_PER_PERSON_EXTRA_TIME * Specs::NUMBER_OF_PEOPLE +
  timeWastedInQueue/60 * Specs::COST_PER_TRUCK_IN_QUEUE) << std::endl;
}

// Function to simulate time
void nextStep(double &nextArrival, double &hourOfNextArrival, double &duration){
    nextArrival = probs::timeOfNextArrival(probs::probsOfArrival4[Specs::id+1]);
    hourOfNextArrival += nextArrival;
    duration = probs::getServTime4(probs::probServiceTime4[Specs::id+1]);
};
