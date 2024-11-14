#include "Functions.h"
#include <cmath>

const int multiplier = 10;

namespace Functions {

    void simpleFunction(const std::vector<int>& numbers) {
        double new_number;
        for (int number : numbers) {
            new_number = number * multiplier;
        }
    }

    void complexFunction_1(const std::vector<int>& numbers) {
        double new_number;
        for (int number : numbers) {
            new_number = std::pow(pow(pow(pow(pow(pow(number, 0.23), 3.5), 0.23), 3.5), 0.23), 3.5);
        }
    }
    
    void complexFunction_2(const std::vector<int>& numbers) {
        double new_number;
        for (int number1 : numbers) {
            for (int number2 : numbers) {
                new_number = number1 + number2;
            }
        }
    }
}
