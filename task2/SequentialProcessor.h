#ifndef SEQUENTIALPROCESSOR_H
#define SEQUENTIALPROCESSOR_H

#include <vector>
#include <string>
#include <chrono>

class SequentialProcessor {
public:
    static std::chrono::duration<double> processFile(const std::vector<int>& numbers, uint8_t computationMethod);
};

#endif
