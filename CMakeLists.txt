cmake_minimum_required(VERSION 3.10)
project(matrizes)
set(CMAKE_CXX_STANDARD 11)

include_directories(include)

add_executable(gerador
               src/gerador.cpp
               src/auxiliar.cpp)

add_executable(sequencial
               src/sequencial.cpp
               src/auxiliar.cpp)

add_executable(threads
               src/threads.cpp
               src/auxiliar.cpp)

add_executable(processos
               src/processos.cpp
               src/auxiliar.cpp)
