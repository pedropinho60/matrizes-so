#ifndef AUXILIAR_HPP
#define AUXILIAR_HPP

#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>

std::vector<std::vector<int>> gerarMatriz(size_t linhas, size_t colunas);
void printMatriz(std::vector<std::vector<int>> matriz);
void writeMatriz(std::vector<std::vector<int>> matriz, std::ofstream& file);
std::vector<std::vector<int>> readMatriz(std::ifstream& file);

#endif
