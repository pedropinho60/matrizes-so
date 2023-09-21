#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <random>
#include <vector>

std::vector<std::vector<int>> gerarMatriz(size_t linhas, size_t colunas) {
    std::vector<std::vector<int>> matriz;

    for(int i=0; i<linhas; i++) {
        std::vector<int> linha;

        for(int j=0; j<colunas; j++) {
            linha.push_back(rand() % 10);
        }

        matriz.push_back(linha);
    }

    return matriz;
}

void printMatriz(std::vector<std::vector<int>> matriz) {
    for(auto l : matriz){
        for(auto c : l){
            std::cout << c << " ";
        }
        std::cout << "\n";
    }
}

void writeMatriz(std::vector<std::vector<int>> matriz, std::ofstream& file) {
    file << matriz.size() << " " << matriz[0].size() << "\n";
    
    for(int i=0; i<matriz.size(); i++) {
        for(int j=0; j<matriz[0].size(); j++) {
            file << "c" << i + 1 << j + 1<< " " << matriz[i][j] << "\n";
        }
    }
}

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
