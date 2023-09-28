#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <sys/wait.h>
#include <unistd.h>

#include "../include/auxiliar.hpp"

std::vector<std::vector<int>> matriz1;
std::vector<std::vector<int>> matriz2;

void multiplicarProcessos(int first, int last, std::chrono::steady_clock::time_point begin, 
                          std::string filename) {
    std::ofstream file(filename);

    int n1 = matriz1.size();
    int n2 = matriz1[0].size();
    int m1 = matriz2.size();
    int m2 = matriz2[0].size();

    if(last > n1*m2) {
        last = n1*m2;
    }

    file << n1 << " " << n2 << "\n";

    for(int idx=first; idx<last; idx++) {
        int i = idx / m2;
        int j = idx % m2;

        int resultado = 0;
        for(int k=0; k<n2; k++) {
            resultado += matriz1[i][k] + matriz2[k][j];
        }

        file << "c" << i+1 << j+1 << " " << resultado << "\n";
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    auto tempo = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    file << tempo << "\n";

    file.close();
}

int main(int argc, char* argv[]) {
    std::ifstream file1(argv[1]);
    matriz1 = readMatriz(file1);
    file1.close();

    std::ifstream file2(argv[2]);
    matriz2 = readMatriz(file2);
    file1.close();

    system("rm -f resultado_processos/*");

    int n1 = matriz1.size();
    int n2 = matriz1[0].size();
    int m1 = matriz2.size();
    int m2 = matriz2[0].size();

    int p = std::stoi(argv[3]);

    int numProcessos = std::ceil(n1*m2 / (float)p);

    for(int i=0; i<n1*m2; i+=p) {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        pid_t pid = fork();

        if(pid == 0) {
            std::string filename = "resultado_processos/processo_" + std::to_string(i/p);
            multiplicarProcessos(i, i+p, begin, filename);
            exit(0);
        }
    }

    for(int i=0; i<numProcessos; i++) {
        wait(NULL);
    }

    return 0;
}
