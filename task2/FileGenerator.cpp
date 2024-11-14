#include "FileGenerator.h"
#include <fstream>

void FileGenerator::generateFile(const std::string& filename, int N) {
    std::ofstream outFile(filename);
    for (int i = 1; i <= N; ++i) {
        outFile << i << "\n";
    }
    outFile.close();
}
