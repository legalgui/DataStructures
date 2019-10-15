// Sebastian Galguera
// Probability helper functions for Queue Simulation implementation

// Guards
#ifndef PROBABILITIES_HPP
#define PROBABILITIES_HPP

namespace queuesimulationutilities{
  namespace probabilities{

    // Values for testing
    double probsOfArrival3[] = {0.0, 0.48355, 0.98977, 0.06533, 0.45128, 0.15486,
      0.19241, 0.15997, 0.6794, 0.90872, 0.58997, 0.68691,0.73488, 0.23423, 0.86675};

    double probServiceTime3[] = {0.83761, 0.14387, 0.51321, 0.72472, 0.05466, 0.84609,
      0.29735, 0.59076, 0.76355, 0.29549, 0.61958,0.17267, 0.10061, 0.45645, 0.86754};

    double probsOfArrival4[] = {0.68971, 0.18477, 0.14707, 0.83745, 0.1693, 0.20368,
      0.41196, 0.66919, 0.35352, 0.79982, 0.4685, 0.69248, 0.04013, 0.45645, 0.86786};

    double probServiceTime4[] = {0.11403, 0.65622, 0.93997, 0.22567, 0.33361, 0.07126,
      0.3748, 0.31678, 0.54131, 0.68416, 0.52326, 0.9346, 0.31792, 0.87315, 0.64564, 0.4545};


    // Number of buses per day
    double getBusNumPerDay(double prob){
      if(prob >= 0.00 && prob < 0.50) return 0;
      if(prob >= 0.50 && prob < 0.75) return 1;
      if(prob >= 0.75 && prob < 0.90) return 2;
      if(prob >= 0.90 && prob < 1) return 3;
      return 0;
    }

    // Time of arrival
    double timeOfNextArrival(double prob){
      if(prob >= 0.00 && prob < 0.02) return 20;
      if(prob >= 0.02 && prob < 0.10) return 25;
      if(prob >= 0.10 && prob < 0.22) return 30;
      if(prob >= 0.22 && prob < 0.47) return 35;
      if(prob >= 0.47 && prob < 0.67) return 40;
      if(prob >= 0.67 && prob < 0.82) return 45;
      if(prob >= 0.82 && prob < 0.92) return 50;
      if(prob >= 0.92 && prob < 0.97) return 55;
      if(prob >= 0.97 && prob < 1) return 60;
      return 0;
    }

    // Three people
    double getServTime3(double prob){
      if(prob >= 0.00 && prob < 0.05) return 20;
      if(prob >= 0.05 && prob < 0.15) return 25;
      if(prob >= 0.15 && prob < 0.35) return 30;
      if(prob >= 0.35 && prob < 0.60) return 35;
      if(prob >= 0.60 && prob < 0.72) return 40;
      if(prob >= 0.72 && prob < 0.82) return 45;
      if(prob >= 0.82 && prob < 0.90) return 50;
      if(prob >= 0.90 && prob < 0.96) return 55;
      if(prob >= 0.96 && prob < 1) return 60;
      return 0;
    }

    // Four people
    double getServTime4(double prob){
      if(prob >= 0.00 && prob < 0.05) return 15;
      if(prob >= 0.05 && prob < 0.20) return 20;
      if(prob >= 0.20 && prob < 0.40) return 25;
      if(prob >= 0.40 && prob < 0.60) return 30;
      if(prob >= 0.60 && prob < 0.75) return 35;
      if(prob >= 0.75 && prob < 0.87) return 40;
      if(prob >= 0.87 && prob < 0.95) return 45;
      if(prob >= 0.95 && prob < 0.99) return 50;
      if(prob >= 0.99 && prob < 1) return 55;
      return 0;
    }

    // Five people
    double getServTime5(double prob){
      if(prob >= 0.00 && prob < 0.10) return 10;
      if(prob >= 0.10 && prob < 0.28) return 15;
      if(prob >= 0.28 && prob < 0.50) return 20;
      if(prob >= 0.50 && prob < 0.68) return 25;
      if(prob >= 0.68 && prob < 0.78) return 30;
      if(prob >= 0.78 && prob < 0.86) return 35;
      if(prob >= 0.86 && prob < 0.92) return 40;
      if(prob >= 0.92 && prob < 0.97) return 45;
      if(prob >= 0.97 && prob < 1) return 50;
      return 0;
    }

    // Six people
    double getServTime6(double prob){
      if(prob >= 0.00 && prob < 0.12) return 10;
      if(prob >= 0.12 && prob < 0.27) return 15;
      if(prob >= 0.27 && prob < 0.53) return 20;
      if(prob >= 0.53 && prob < 0.68) return 25;
      if(prob >= 0.68 && prob < 0.80) return 30;
      if(prob >= 0.80 && prob < 0.88) return 35;
      if(prob >= 0.88 && prob < 0.94) return 40;
      if(prob >= 0.94 && prob < 0.98) return 45;
      if(prob >= 0.98 && prob < 1) return 50;
      return 0;
    }
  }
}


#endif /* PROBABILITIES_HPP */
