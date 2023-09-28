#!/bin/bash

max_tempo=120000

n=100

media_sequencial=0

> tempos_sequencial.txt
> tempos_threads.txt
> tempos_processos.txt

while [ $media_sequencial -lt $max_tempo ]
do
    ./build/gerador $n $n $n $n

    echo "Rodando para n = $n"

    echo "Sequencial..." 
    soma=0
    for i in {1..10}
    do
        ./build/sequencial matriz1.txt matriz2.txt
        tempo_sequencial=$(./scripts/tempo_sequencial.sh)
        soma=$(($soma+$tempo_sequencial))
    done
    media_sequencial=$(($soma / 10))
    echo $n $media_sequencial >> tempos_sequencial.txt
    echo "Tempo: $media_sequencial ms"

    echo "Threads..."
    soma=0
    for i in {1..10}
    do
        ./build/threads matriz1.txt matriz2.txt $(( ( $n*$n / 8 ) + ( $n*$n % 8 > 0 ) ))
        tempo_threads=$(./scripts/tempo_threads.sh)
        soma=$(($soma+$tempo_threads))
    done
    media_threads=$((soma / 10))
    echo $n $media_threads >> tempos_threads.txt
    echo "Tempo: $media_threads ms"

    echo "Processos..."
    soma=0
    for i in {1..10}
    do
        ./build/processos matriz1.txt matriz2.txt $(( ( $n*$n / 8 ) + ( $n*$n % 8 > 0) ))
        tempo_processos=$(./scripts/tempo_processos.sh)
        soma=$(($soma+$tempo_processos))
    done
    media_processos=$((soma / 10))
    echo $n $media_processos >> tempos_processos.txt
    echo "Tempo: $media_processos ms"

    n=$(($n*2))
done