// Sebastian Galguera
// Code to implement Queue Simulation System

#include <time.h>

// General helpers
#include "ConsoleUtilities.hpp"
namespace output = consoleutilities::output;

// Problem specifics
#include "EventHandler.hpp"
using queuesimulationutilities::EventHandler;


int main(){
  output::printHeader("QUEUE SIMULATOR");
  EventHandler eHandler;
  eHandler.run();
 return 0;
}
