#include "SequentialProcessor.h"
#include <fstream>
#include <iostream>
#include "Functions.h"



void SequentialProcessor::processFile(const std::vector<int>& numbers, uint8_t computationMethod) {
    switch (computationMethod) {
    case 0:
        Functions::simpleFunction(numbers);
        break;
    case 1:
        Functions::complexFunction_1(numbers);
        break;
    case 2:
        Functions::complexFunction_2(numbers);
        break;
    }
}