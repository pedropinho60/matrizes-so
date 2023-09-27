#include <bits/chrono.h>
#include <chrono>
#include <cmath>
#include <fstream>
#include <iostream>
#include <pthread.h>
#include <string>
#include <thread>
#include <vector>
#include <stdlib.h>

#include "../include/auxiliar.hpp"

struct arg_struct {
    int first;
    int last;
    std::vector<std::vector<int>> matriz1;
    std::vector<std::vector<int>> matriz2;
    std::string filename;
    std::chrono::steady_clock::time_point begin;
};

void* multiplicarThreads(void* args) { 
    int first = ((arg_struct*)args)->first;
    int last = ((arg_struct*)args)->last;
    auto& matriz1 = ((arg_struct*)args)->matriz1;
    auto& matriz2 = ((arg_struct*)args)->matriz2;
    std::string filename = ((arg_struct*)args)->filename;
    auto begin = ((arg_struct*)args)->begin;
    
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
    return 0;
}

void* test(void* args) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return 0;
}


int main(int argc, char* argv[]) {
    std::ifstream file1(argv[1]);
    auto matriz1 = readMatriz(file1);
    file1.close();

    std::ifstream file2(argv[2]);
    auto matriz2 = readMatriz(file2);
    file1.close();

    system("rm -f resultado_threads/*");

    int n1 = matriz1.size();
    int n2 = matriz1[0].size();
    int m1 = matriz2.size();
    int m2 = matriz2[0].size();

    int p = std::stoi(argv[3]);

    int numThreads = std::ceil(n1*m2 / (float)p);

    std::vector<pthread_t> threads;
    threads.resize(numThreads);

    std::vector<arg_struct> structs;
    structs.resize(numThreads);

    for(int i=0; i<n1*m2; i+=p) {
        std::string filename = "resultado_threads/thread_" + std::to_string(i/p);
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

        structs[i/p].matriz1 = matriz1;
        structs[i/p].matriz2 = matriz2;
        structs[i/p].filename = filename;
        structs[i/p].begin = begin;
        structs[i/p].first = i;
        structs[i/p].last = i+p;

        pthread_create(&(threads[i/p]), NULL, multiplicarThreads, (void*)&(structs[i/p]));
    }

    for(int i=0; i<numThreads; i++) {
        pthread_join(threads[i], NULL);
    }
}
