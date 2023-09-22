#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <random>
#include <string>
#include <vector>

#include "../include/auxiliar.hpp"

int main (int argc, char *argv[]) {
    if(argc != 5) {
        std::cout << "Número de argumentos inválido (" << argc - 1 << "). Esperados 4 argumentos.\n";
        return 0;
    }

    srand(time(NULL));

    size_t n1 = atoi(argv[1]);
    size_t m1 = atoi(argv[2]);
    size_t n2 = atoi(argv[3]);
    size_t m2 = atoi(argv[4]);

    auto matriz1 = gerarMatriz(n1, n2);
    auto matriz2 = gerarMatriz(m1, m2);

    std::ofstream file1;
    std::ofstream file2;

    file1.open("matriz1.txt");
    writeMatriz(matriz1, file1);
    file1.close();

    file2.open("matriz2.txt");
    writeMatriz(matriz2, file2);
    file2.close();

    return 0;
}
