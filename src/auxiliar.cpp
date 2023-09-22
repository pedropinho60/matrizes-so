#include "../include/auxiliar.hpp"

std::vector<std::vector<int>> gerarMatriz(size_t linhas, size_t colunas) {
    std::vector<std::vector<int>> matriz;

    for(int i=0; i<linhas; i++) {
        std::vector<int> linha;

        for(int j=0; j<colunas; j++) {
            linha.push_back(rand()%10 + 1);
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

std::vector<std::vector<int>> readMatriz(std::ifstream& file) {
    int n1;
    int n2;

    file >> n1;
    file >> n2;

    std::vector<std::vector<int>> matriz;

    for(int i=0; i<n1; i++) {
        matriz.push_back(std::vector<int>());
        for(int j=0; j<n2; j++) {
            matriz[i].push_back(0);
            file.ignore(4, ' ');
            file >> matriz[i][j];
            file.ignore(1, '\n');
        }
    }

    return matriz;
}
