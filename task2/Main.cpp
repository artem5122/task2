#include "FileGenerator.h"
#include "NumbersGenerator.h"
#include "SequentialProcessor.h"
#include "ParallelProcessor.h"
#include "EnviromentVariables.h"
#include <iostream>
#include <chrono>
#include <fstream>


int main() {
    setlocale(LC_ALL, "Russian");
    int N, M, computationMethod;
    bool randomSplit;
    EnviromentVariables::getEnviromentVariables(N, M, computationMethod, randomSplit);


    std::ofstream csvFile("results.csv");
    csvFile << "computationMethod,N,M,randomSplit,S,Time\n";
    std::vector<int> numbers = NumbersGenerator::generateNumbers(N);


    // ���������������� ���������
    std::chrono::duration<double> sequentialTime = SequentialProcessor::processFile(numbers, computationMethod);
    csvFile << computationMethod << "," << N << ",None,None,None," << sequentialTime.count() << "\n";
    std::cout << "���������������� ��������� ������ " << sequentialTime.count() << " ������.\n\n";


    // ������������� ���������
    std::chrono::duration<double> notParallelTime;
    std::chrono::duration<double> parallelTime = ParallelProcessor::processFile(numbers, M, computationMethod, randomSplit, notParallelTime);
    double S = notParallelTime.count() / parallelTime.count();
    csvFile << computationMethod << "," << N << "," << M << "," << (randomSplit ? "true" : "false") << "," << S << "," << parallelTime.count() << "\n";
    std::cout <<"������������ ��������� ������ " << parallelTime.count() << " ������.\n���� ���������������� ����������: " << S  << "\n\n";


    csvFile.close();
    system("pause");
    return 0;
}
