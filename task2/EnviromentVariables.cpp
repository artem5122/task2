#include "EnviromentVariables.h"
#include <fstream>
#include <iostream>

bool EnviromentVariables::isCorrect(int N, int M, int computationMethod, bool randomSplit) {
    if (N < 1 || M < 1) {
        return false;
    }
    if (computationMethod < 0 || computationMethod > 2) {
        return false;
    }
    if (randomSplit != 0 && randomSplit != 1) {
        return false;
    }
    return true;
}

void EnviromentVariables::getEnviromentVariables(int& N, int& M, int& computationMethod, bool& randomSplit)
{
    std::ifstream file("config.ini");
    if (!file.is_open()) {
        throw std::runtime_error("Ошибка: не удалось открыть файл config.ini.");
    }

    N = -1;
    M = -1;
    computationMethod = -1;


    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '[' || line[0] == ';') continue;
        auto delimiterPos = line.find("=");
        auto key = line.substr(0, delimiterPos);
        auto value = line.substr(delimiterPos + 1);
        if (key == "N") {
            N = std::stoi(value);
        }
        else if (key == "M") {
            M = std::stoi(value);
        }
        else if (key == "computationMethod") {
            computationMethod = std::stoi(value);
        }
        else if (key == "randomSplit") {
            randomSplit = (value == "true" || value == "1");
        }
    }

    // Проверка корректности ввода и считывания данных
    if (!isCorrect(N, M, computationMethod, randomSplit)) {
        std::cout << "Данные были введены некорректно\n" << std::endl;
        system("pause");
        std::exit(1);
    }

    std::cout << "N: " << N << "\n";
    std::cout << "M: " << M << "\n";
    std::cout << "computationMethod: " << computationMethod << "\n";
    std::cout << "randomSplit: " << randomSplit << "\n\n";

}
