#include "FileGenerator.h"
#include "NumbersGenerator.h"
#include "SequentialProcessor.h"
#include "ParallelProcessor.h"
#include <iostream>
#include <chrono>
#include <fstream>


int main() {
    setlocale(LC_ALL, "Russian");


    std::ofstream csvFile("results.csv");

    csvFile << "computationMethod,N,M,shuffle,S,Time\n";


    for (auto& computationMethod : { 0, 1, 2 }) {
        std::vector<int> N_array;
        if (computationMethod == 2)
            N_array = { 1000, 2000, 4000, 5000, 7500, 10000, 25000, 50000, 100000 };
        else
            N_array = { 1000, 5000, 10'000, 100'000, 1000'000, 10'000'000, 50'000'000, 100'000'000 };

        std::vector<int> M_array = { 1, 2, 3, 4, 5, 8, 10, 20, 30, 50, 100 };

        for (auto& N : N_array) {
            std::vector<int> numbers = NumbersGenerator::generateNumbers(N);

            // Последовательная обработка
            auto start = std::chrono::high_resolution_clock::now();
            SequentialProcessor::processFile(numbers, computationMethod);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> sequentialTime = end - start;

            csvFile << computationMethod << "," << N << ",None,None,None," << sequentialTime.count() << "\n";
            std::cout << computationMethod << ". N = " << N << " Time: " << sequentialTime.count() << std::endl;
            
            for (bool shuffle : {false, true}) {
                std::cout << "Shuffle: " << shuffle << std::endl;
                for (auto& M : M_array) {
                    // Многопоточная обработка
                    start = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> notParallelTime = ParallelProcessor::processFile(numbers, M, computationMethod, shuffle);
                    end = std::chrono::high_resolution_clock::now();
                    std::chrono::duration<double> parallelTime = end - start;

                    double S = notParallelTime.count() / parallelTime.count();

                    csvFile << computationMethod << "," << N << "," << M << "," << (shuffle ? "true" : "false") << "," << S << "," << parallelTime.count() << "\n";
                    std::cout << computationMethod << ". N = " << N << "   M = " << M << "   S = " << S << " Time: " << parallelTime.count() << std::endl;
                }
            }
        }
    }

    csvFile.close();
    system("pause");
    return 0;
}
