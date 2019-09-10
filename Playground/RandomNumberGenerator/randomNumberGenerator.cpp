// Jonathan Ginsburg (/jginsburgn) and Sebastian Galguera
// Random card number generator using Middle Square Method and Boost Library

#include <iostream>
#include <set>
#include <stdexcept>
#include <iomanip>

// Full path to boost big ints
#include </usr/local/include/boost/multiprecision/cpp_int.hpp>

// Avoiding macros
namespace randomgeneratordata{
  class Specs{
  public:
    static constexpr int MIDDLE_SQUARE_SIZE { 16 };
  };
};

typedef randomgeneratordata::Specs Specs;
typedef boost::multiprecision::uint512_t Uint512;
typedef unsigned long long Giantint;

bool isValid(Giantint);
void printData(Giantint, Uint512, Uint512);

// Function to create generator
auto msm(Giantint t_seed) {
    Giantint* currentResult = new Giantint(t_seed);

    auto generator = [currentResult](bool stop = false)-> Giantint {
        if (stop) {
            delete currentResult;
            return 0;
        }

        Uint512 tremendouslyBig = *currentResult;
        tremendouslyBig *= tremendouslyBig;

        std::string str = boost::lexical_cast<std::string>(tremendouslyBig);
        *currentResult = std::stoull(str.substr((str.size()/2-8), Specs::MIDDLE_SQUARE_SIZE));

        return *currentResult;
    };
    return generator;
}

int main() {

	Uint512 all, valid = 0;
	Giantint seed = 5186479483157648;
  Giantint prueba = 4941330105954188;

	try {
        auto generator = msm(seed);
        std::set<Giantint> seen;
        Giantint current = generator();

        while(seen.find(current) == seen.end()) {
            if(isValid(current)){
                seen.insert(current);
                std::cout << current << std::endl;
                valid++;
            }
            all++;
            current = generator();
            if(current == 0)
            	break;
        }
        printData(seed, all, valid);
        generator(true);
    }
    catch (std::invalid_argument e) {
    	puts(e.what());
    }
    std::cout << "Is it valid? " << isValid(prueba) << std::endl;
    return 0;
}

// Function to print the resulting data
void printData(Giantint seed, Uint512 all, Uint512 valid){
  std::cout << "Period for seed " << seed << ": " << all << "." << std::endl;
  std::cout << "Number of valid cards in period for seed " << ": " << valid << "." << std::endl;
  std::cout << "Percentage of credit cards in period " << double(valid)/double(all) << std::endl;
}

// Function to verify if the card is valid
bool isValid(Giantint t_generator){
    std::string numberString = std::to_string(t_generator);

    if(numberString.size() != 16){ return 0; }

    std::vector<int> vec;

    for(int i = 0; i < numberString.size(); i++){
        int number = numberString[i] - '0';

        if(i%2 == 0){
            number *= 2;
            if(number > 9){
                int units = number % 10;
                int tenths = number / 10;
                number = units + tenths;
            }

        }
        vec.push_back(number);
    }
    int acum = 0;
    for (auto& n : vec){ acum += n; }
    return acum%10 == 0;
};
