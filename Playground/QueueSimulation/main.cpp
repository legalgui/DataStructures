// Sebastian Galguera
// Code to implement Queue Simulation System

#include <time.h>

// General helpers
#include "ConsoleUtilities.hpp"
namespace output = consoleutilities::output;

#include "Event.hpp"
using queuesimulationutilities::Event;

#include "Probabilities.hpp"
namespace probs = probabilities;

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
    static constexpr int TIME_INTERVAL { 5 };

    static constexpr double COST_PER_PERSON_EXTRA_TIME { 37.5 };
    static constexpr double COST_PER_PERSON_NORMAL_TIME { 25.0 };
    static constexpr double COST_PER_TRUCK_IN_QUEUE { 100.0 };
    static constexpr double COST_PER_HOUR_OF_WAREHOUSE { 500.0 };
    static constexpr int NUMBER_OF_PEOPLE { 4 };

  };
};

int id = 0;
typedef queuesimulationdata::Specs Specs;

void nextStep(double &, double &, double &);

int main(){
  output::printHeader("COMMUNICATIONS SIMULATOR");
  // CATCHING THE SYSTEM MACROS
  int numberOfTrucks = Specs::NUMBER_OF_TRUCKS;
  int timeOfStart = Specs::TIME_OF_START;
  int timeOfEnd = Specs::TIME_OF_END;
  int timeInterval = Specs::TIME_INTERVAL;

  // FLAGS
  bool hourOfArrivalHasPassed = 1;
  bool hadLunch = 0;
  bool emergency = 0;

  // COUNTERS
  double limitCount = 0;

  // SPECIFIERS
  double nextArrival = 0;
  double hourOfNextArrival = 660;
  double durationOfEvent = 0;

  // ACCUMULATORS
  double timeWastedInQueue = 0;
  double timeWastedByStaff = 0;

  // OUR BAY
  Queue<Event *> * bay = new Queue<Event *>;

  // INITIAL CONDITIONS
  Event * e = new Event("First case", id);
  e->setTimeOfArrival(660);
  e->setDuration(20);
  bay->enqueue(e);

  // START DAY
  for(int clock = timeOfStart; clock < timeOfEnd; clock += timeInterval){
    // GENERAL TIME OF THE DAY
    std::cout << "Current time : ";
    output::printTime(clock);

    // DEQUEUING CONDITIONS
    if(!bay->empty()){
      // IF THE TIME OF DEQUEUING HAS COME
      if(clock == bay->front()->getInfo()->getTimeOfEventEnd()){
        // DON'T PENALIZE QUEUE OR STAFF FOR LUNCH
        if(!(bay->front()->getInfo()->getEventType() == "Lunch")){
          timeWastedInQueue += bay->front()->getInfo()->getTimeWastedInQueue();
          timeWastedByStaff += bay->front()->getInfo()->getTimeWastedByStaff();
        }
        std::cout << "EXITS " << std::endl;
        std::cout << bay->dequeue()->getInfo() << std::endl;
        std::cout << "SIZE OF QUEUE " << bay->size() << std::endl;
      }
    }

    // TRIGGERING A NEW TIME OF ARRIVAL AND DURATION
    if(hourOfArrivalHasPassed){
      nextStep(nextArrival, hourOfNextArrival, durationOfEvent);
      hourOfArrivalHasPassed = 0;
    }

    // INJECTING A SPECIAL EVENT
    if(clock >= 900 && !hadLunch){
      Event * e = new Event("Lunch", id++);
      e->setTimeOfArrival(900);
      e->setDuration(30);
      bay->enqueue(e);
      id--;
      std::cout << "ENTERS " << std::endl;
      std::cout << *e << std::endl;
      hadLunch = 1;
    }

     // IF THE CLOCK REACHES THE TIME OF ARRIVAL
     if(clock == hourOfNextArrival && limitCount < numberOfTrucks){
       Event * e = new Event("Truck Event", ++id);
       e->setTimeOfArrival(hourOfNextArrival);
       e->setDuration(durationOfEvent);
       bay->enqueue(e);
       std::cout << "ENTERS " << std::endl;
       std::cout << *e << std::endl;
       hourOfArrivalHasPassed = 1;
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


 return 0;
}


// Function to simulate time
void nextStep(double &nextArrival, double &hourOfNextArrival, double &durationOfEvent){
    nextArrival = probs::timeOfNextArrival(probs::probsOfArrival4[id+1]);
    hourOfNextArrival += nextArrival;
    durationOfEvent = probs::getServTime4(probs::probServiceTime4[id+1]);
};
