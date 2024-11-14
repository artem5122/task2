#include "NumbersGenerator.h"

std::vector<int> NumbersGenerator::generateNumbers(int N)
{
    std::vector<int> array;
    for (int i = 1; i <= N; ++i) {
        array.push_back(i);
    }
    return array;
}
