#ifndef ENVIROMENTVARIABLES_H
#define ENVIROMENTVARIABLES_H

#include <vector>
#include <string>

class EnviromentVariables {
public:
    static void getEnviromentVariables(int& N, int& M, int& computationMethod, bool& randomSplit);
    static bool isCorrect(int N, int M, int computationMethod, bool randomSplit);
};

#endif



