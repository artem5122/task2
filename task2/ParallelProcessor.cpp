#include "ParallelProcessor.h"
#include <thread>
#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include "Functions.h"
#include <random>
#include <algorithm>

std::vector<int> generateRandomIndices(int N, int threadCount) {
    std::vector<int> indices;
    if (N <= threadCount) {
        for (int i = 0; i < N; ++i) {
            indices.push_back(i);
        }
    }
    else {
        std::random_device rd;  //устройство для получения случайных чисел
        std::mt19937 gen(rd()); // один из генераторов
        std::uniform_int_distribution<> dis(1, N - 1); 

        while (indices.size() < threadCount - 1) {
            int idx = dis(gen);
            // find вернет указатель на конец конейнера, если не нашёлся дубликат, поэтому == indices.end()
            if (std::find(indices.begin(), indices.end(), idx) == indices.end()) {
                indices.push_back(idx);
            }
        }
        std::sort(indices.begin(), indices.end());
    }
    return indices;
}

std::chrono::duration<double> ParallelProcessor::processFile(std::vector<int>& numbers, int threadCount, int8_t computationMethod, bool shuffle) {

    auto start = std::chrono::high_resolution_clock::now();

    void(*chosenFunction)(const std::vector<int>&);
    
    switch (computationMethod) {
    case 0:
        chosenFunction = Functions::simpleFunction;
        break;
    case 1:
        chosenFunction = Functions::complexFunction_1;
        break;
    case 2:
        chosenFunction = Functions::complexFunction_2;
        break;
    }

    std::vector<std::thread> threads;


    if (shuffle) {
        std::vector<int> indices = generateRandomIndices(numbers.size(), threadCount);

        int prevIdx = 0;

        for (int i = 0; i < indices.size(); ++i) {
            int startIdx = prevIdx;
            int endIdx = indices[i];
            prevIdx = endIdx;

            std::vector<int> chunk(numbers.begin() + startIdx, numbers.begin() + endIdx);
            threads.emplace_back(chosenFunction, chunk);
        }

        std::vector<int> lastChunk(numbers.begin() + prevIdx, numbers.end()); //последний участок
        threads.emplace_back(chosenFunction, lastChunk);
    }
    else {
        int chunkSize = numbers.size() / threadCount;

        for (int i = 0; i < threadCount; ++i) {
            int startIdx = i * chunkSize;
            int endIdx = (i == threadCount - 1) ? numbers.size() : startIdx + chunkSize;

            std::vector<int> chunk(numbers.begin() + startIdx, numbers.begin() + endIdx);
            threads.emplace_back(chosenFunction, chunk);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> notParallelTime = end - start;

    for (auto& t : threads) {
        t.join();
    }
    return notParallelTime;
}

