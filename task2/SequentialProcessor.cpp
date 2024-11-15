#include "SequentialProcessor.h"
#include <fstream>
#include <iostream>
#include "Functions.h"
#include <chrono>



std::chrono::duration<double> SequentialProcessor::processFile(const std::vector<int>& numbers, uint8_t computationMethod) {
    auto start = std::chrono::high_resolution_clock::now();
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
    auto end = std::chrono::high_resolution_clock::now();
    return end - start;
}