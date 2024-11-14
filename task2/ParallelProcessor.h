#ifndef PARALLELPROCESSOR_H
#define PARALLELPROCESSOR_H
#include <chrono>

#include <string>
#include <vector>

class ParallelProcessor {
public:
    static std::chrono::duration<double> processFile(std::vector<int>& numbers, int threadCount, int8_t computationMethod, bool shuffle);
};

#endif
