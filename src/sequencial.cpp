#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

#include "../include/auxiliar.hpp"

int main() {
    std::ifstream file1("matriz1.txt");
    auto matriz1 = readMatriz(file1);
    file1.close();

    std::ifstream file2("matriz1.txt");
    auto matriz2 = readMatriz(file2);
    file1.close();

    int n1 = matriz1.size();
    int n2 = matriz1[0].size();
    int m1 = matriz2.size();
    int m2 = matriz2[0].size();

    std::vector<std::vector<int>> matrizResultado;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for(int i=0; i<n1; i++) {
        matrizResultado.push_back(std::vector<int>());
        for(int j=0; j<m2; j++) {
            matrizResultado[i].push_back(0);
            for(int k=0; k<n2; k++) {
                matrizResultado[i][j] += matriz1[i][k] + matriz2[k][j];
            }
        }
    }
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    auto tempo = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

    std::ofstream outfile("resultado_sequencial.txt");
    writeMatriz(matrizResultado, outfile);
    outfile << tempo << '\n';
    outfile.close();

    std::cout << "Tempo: " << tempo << " [ms]" << std::endl;
}
