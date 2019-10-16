// Sebastian Galguera
// Event handler class for Queue Simulation implementation

// Guards
#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP

#include <iostream>

// General helpers
#include "ConsoleUtilities.hpp"
namespace output = consoleutilities::output;

// Problem specifics
#include "Event.hpp"
#include "PriorityHandler.hpp"
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
    static int ID;
  };
};

typedef queuesimulationdata::Specs Specs;
int Specs::ID {0};

// Namespace enclosing
namespace queuesimulationutilities{
  class EventHandler{

    // Flags
    bool m_hourOfArrivalHasPassed { true };
    bool m_hadLunch { false };

    // Counters
    double m_limitCount { 0 };

    // Specifiers
    double m_nextArrival { 0 };
    double m_hourOfNextArrival { 660 };
    double m_duration { 0 };

    // Accumulators
    double m_timeWastedInQueue { 0 };
    double m_timeWastedByStaff { 0 };

    // Bay
    Queue<Event *> * m_bay { new Queue<Event *>() };
    PriorityHandler<Event *> m_ph;

  public:
    EventHandler(){};
    ~EventHandler();

    void nextStep();
    void createEvent(const std::string, const int, const double, const double);
    void handleEvent();
    void printCosts();
    void dismiss();
    void run();
  };

  EventHandler::~EventHandler(){
    if(m_bay->size()){ delete m_bay; }
  };

  // Function to get next step
  void EventHandler::nextStep(){
    // Pre-established probabilities for testing, but should be random
    m_nextArrival = probs::timeOfNextArrival(probs::probsOfArrival4[Specs::ID+1]);
    m_hourOfNextArrival += m_nextArrival;
    m_duration = probs::getServTime4(probs::probServiceTime4[Specs::ID+1]);
  };

  void EventHandler::createEvent(const std::string t_name, const int t_id,
    const double t_hourOfNextArrival, const double t_duration){

      Event * e { new Event(t_name, t_id) };
      e->setTimeOfArrival(t_hourOfNextArrival);
      e->setDuration(t_duration);
      m_ph.syncEnqueue(e);
      if(t_name != "Lunch"){ m_limitCount++; }
      std::cout << "Enters " << std::endl;
      std::cout << *e << std::endl;
  };

  void EventHandler::handleEvent(){
    // Penalize everything but lunch time
    if(!(m_bay->front()->getInfo()->getEventType() == "Lunch")){
      m_timeWastedInQueue += m_bay->front()->getInfo()->getTimeWastedInQueue();
      m_timeWastedByStaff += m_bay->front()->getInfo()->getTimeWastedByStaff();
    }
    std::cout << "Exits" << std::endl;
    std::cout << *m_bay->dequeue()->getInfo() << std::endl;
    std::cout << "Number of events in queue: " << m_bay->size() << std::endl;
  };

  void EventHandler::printCosts(){

    double activeHours { (Specs::TIME_OF_END - Specs::TIME_OF_START)/60 };

    output::printHeader("Results");
    std::cout << "Cost of warehouse active hours: " << "$" <<
    (activeHours * Specs::COST_PER_HOUR_OF_WAREHOUSE) << std::endl;

    std::cout << "Cost of personnel normal hours: " << "$" <<
    (activeHours * Specs::COST_PER_PERSON_NORMAL_TIME * Specs::NUMBER_OF_PEOPLE) << std::endl;

    std::cout << "Cost of personnel extra houss: " << "$" <<
    (0 * Specs::COST_PER_PERSON_EXTRA_TIME * Specs::NUMBER_OF_PEOPLE) << std::endl;

    std::cout << "Cost of trucks waiting in queue: " << "$" <<
    (m_timeWastedInQueue / 60 * Specs::COST_PER_TRUCK_IN_QUEUE) << std::endl;

    std::cout << "Total: " << "$" << (activeHours * Specs::COST_PER_HOUR_OF_WAREHOUSE +
    activeHours * Specs::COST_PER_PERSON_NORMAL_TIME * Specs::NUMBER_OF_PEOPLE +
    0 * Specs::COST_PER_PERSON_EXTRA_TIME * Specs::NUMBER_OF_PEOPLE +
    m_timeWastedInQueue / 60 * Specs::COST_PER_TRUCK_IN_QUEUE) << std::endl;
  };

  void EventHandler::dismiss(){
    // Pop the remaining events
    for(int i = 0; i < m_bay->size(); i++){
      std::cout << *m_bay->dequeue()->getInfo() << std::endl;
    }
  };

  void EventHandler::run(){
    // Bind the Queue
    m_ph.bind(m_bay);
    // First event
    createEvent("First case", Specs::ID++, 660, 20);

    // Start 11:00 AM
    for(int clock = Specs::TIME_OF_START; clock < Specs::TIME_OF_END; clock += Specs::TIME_INTERVAL){
      std::cout << "Current time: ";
      output::printTime(clock);

      if(!m_bay->empty() && (clock == m_bay->front()->getInfo()->getTimeOfEventEnd())){
        handleEvent();
      }

      // Getting the next arrival
      if(m_hourOfArrivalHasPassed){
        nextStep();
        m_hourOfArrivalHasPassed = false;
      }

      // Launch special case
      if(clock >= 900 && !m_hadLunch){
        createEvent("Lunch", Specs::ID++, 900, 30);
        m_hadLunch = true;
      }

      // Launch normal case
      if(clock == m_hourOfNextArrival && m_limitCount < Specs::NUMBER_OF_TRUCKS){
        createEvent("Truck Event", Specs::ID++, m_hourOfNextArrival, m_duration);
        m_hourOfArrivalHasPassed = true;
      }

   }
   dismiss();
   printCosts();
   delete m_bay;
 };

}

#endif /* EVENT_HANDLER_HPP */
