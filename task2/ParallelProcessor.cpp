#include "ParallelProcessor.h"
#include <thread>
#include <fstream>
#include <iostream>
#include <vector>
#include <cmath>
#include "Functions.h"
#include <random>
#include <algorithm>
#include <chrono>

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


void processRandomSplit(const std::vector<int>& numbers, int threadCount, void(*chosenFunction)(const std::vector<int>&), std::vector<std::thread>& threads) {
    std::vector<int> indices = generateRandomIndices(numbers.size(), threadCount);

    int prevIdx = 0;

    for (int i = 0; i < indices.size(); ++i) {
        int startIdx = prevIdx;
        int endIdx = indices[i];
        prevIdx = endIdx;

        std::vector<int> chunk(numbers.begin() + startIdx, numbers.begin() + endIdx);
        threads.emplace_back(chosenFunction, chunk);
    }

    std::vector<int> lastChunk(numbers.begin() + prevIdx, numbers.end()); // последний участок
    threads.emplace_back(chosenFunction, lastChunk);
}

void processEqualSplit(const std::vector<int>& numbers, int threadCount, void(*chosenFunction)(const std::vector<int>&), std::vector<std::thread>& threads) {
    int chunkSize = numbers.size() / threadCount;

    for (int i = 0; i < threadCount; ++i) {
        int startIdx = i * chunkSize;
        int endIdx = (i == threadCount - 1) ? numbers.size() : startIdx + chunkSize;

        std::vector<int> chunk(numbers.begin() + startIdx, numbers.begin() + endIdx);
        threads.emplace_back(chosenFunction, chunk);
    }
}


std::chrono::duration<double> ParallelProcessor::processFile(std::vector<int>& numbers, int threadCount, int8_t computationMethod, bool randomSplit, std::chrono::duration<double>& notParallelTime) {


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
    default:
        chosenFunction = Functions::complexFunction_1;
        break;
    }

    std::vector<std::thread> threads;


    if (randomSplit) {
        processRandomSplit(numbers, threadCount, chosenFunction, threads);
    }
    else {
        processEqualSplit(numbers, threadCount, chosenFunction, threads);
    }

    auto end = std::chrono::high_resolution_clock::now();
    notParallelTime = end - start;

    for (auto& t : threads) {
        t.join();
    }
    auto end_2 = std::chrono::high_resolution_clock::now();

    return end_2 - start;
}

