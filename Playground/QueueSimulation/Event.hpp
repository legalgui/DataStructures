// Sebastian Galguera
// Event class for Queue Simulation implementation

// Guards
#ifndef EVENT_HPP
#define EVENT_HPP

#include <iostream>

// General helpers
#include "ConsoleUtilities.hpp"
namespace output = consoleutilities::output;

// Namespace enclosing
namespace queuesimulationutilities{
  class Event{

      int m_id { 0 };
      std::string m_eventType;
      double m_duration { 0.0 };

      // Global times for day
      double m_timeOfArrival { 0.0 };
      double m_timeOfEventStart { 0.0 };
      double m_timeOfEventEnd { 0.0 };

      double m_lockedEvents { 0.0 };

      // Time wasted
      double m_timeWastedInQueue { 0.0 };
      double m_timeWastedByStaff { 0.0 };

  public:

      Event(std::string t_eventType, int t_id) : m_eventType(t_eventType), m_id(t_id) {}
      ~Event(){};

      int getID() const;

      void setEventType(const std::string);
      std::string getEventType() const;

      void setDuration(const double);
      double getDuration() const;

      void setTimeOfArrival(const double);
      double getTimeOfArrival() const;

      void setTimeOfEventStart(const double);
      double getTimeOfEventStart() const;

      void setTimeOfEventEnd(const double);
      double getTimeOfEventEnd() const;

      void setLockedEvents(const double);
      double getLockedEvents() const;

      void setTimeWastedInQueue(const double);
      double getTimeWastedInQueue() const;

      void setTimeWastedByStaff(const double);
      double getTimeWastedByStaff() const;

      inline bool operator==(const Event& t_event) const {
  			return m_id == t_event.getID();
  		}

      friend std::ostream & operator<<(std::ostream &, const Event  &);
  };

  int Event::getID() const{
    return m_id;
  };

  void Event::setEventType(const std::string t_eventType){
    m_eventType = t_eventType;
  };

  std::string Event::getEventType() const{
    return m_eventType;
  };

  void Event::setDuration(const double t_duration){
    m_duration = t_duration;
  };

  double Event::getDuration() const{
    return m_duration;
  };

  void Event::setTimeOfArrival(const double t_timeOfArrival){
    m_timeOfArrival = t_timeOfArrival;
  };

  double Event::getTimeOfArrival() const{
    return m_timeOfArrival;
  };

  void Event::setTimeOfEventStart(const double t_timeOfEventStart){
    m_timeOfEventStart = t_timeOfEventStart;
  };

  double Event::getTimeOfEventStart() const{
    return m_timeOfEventStart;
  };

  void Event::setTimeOfEventEnd(const double t_timeOfEventEnd){
    m_timeOfEventEnd = t_timeOfEventEnd;
  };

  double Event::getTimeOfEventEnd() const{
    return m_timeOfEventEnd;
  };

  void Event::setLockedEvents(const double t_lockedEvents){
    m_lockedEvents = t_lockedEvents;
  };

  double Event::getLockedEvents() const{
    return m_lockedEvents;
  };

  void Event::setTimeWastedInQueue(const double t_timeWastedInQueue){
    m_timeWastedInQueue = t_timeWastedInQueue;
  };

  double Event::getTimeWastedInQueue() const{
    return m_timeWastedInQueue;
  };

  void Event::setTimeWastedByStaff(const double t_timeWastedByStaff){
    m_timeWastedByStaff = t_timeWastedByStaff;
  };

  double Event::getTimeWastedByStaff() const{
    return m_timeWastedByStaff;
  };

  std::ostream & operator<<(std::ostream & t_os, const Event & t_event){
    output::printHeader(t_event.getEventType());

    std::cout << "Time the truck arrives : ";
    output::printTime(t_event.getTimeOfArrival());

    std::cout << "Time the service starts : ";
    output::printTime(t_event.getTimeOfEventStart());

    std::cout << "Duration of Service : ";
    output::printTime(t_event.getDuration());

    std::cout << "Time the service will end : ";
    output::printTime(t_event.getTimeOfEventEnd());

    return t_os;
  };
}

#endif /* EVENT_HPP */
