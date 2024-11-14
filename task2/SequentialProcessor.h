#ifndef SEQUENTIALPROCESSOR_H
#define SEQUENTIALPROCESSOR_H

#include <vector>
#include <string>

class SequentialProcessor {
public:
    static void processFile(const std::vector<int>& numbers, uint8_t computationMethod);
};

#endif
