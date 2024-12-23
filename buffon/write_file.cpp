#include "write_file.h"

void writeArraysToFile(const char* filename, int* array1, double* array2, double* array3, int size) {
    std::ofstream outFile(filename);

    if (!outFile) {
        std::cerr << "Error opening file for writing." << std::endl;
        return;
    }

    // 배열의 내용을 파일에 출력
    for (int i = 0; i < size; ++i) {
        outFile << array1[i] << " " << array2[i] << " " << array3[i] << std::endl;
    }

    outFile.close();
}