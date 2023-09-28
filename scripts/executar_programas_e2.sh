#!/bin/bash

n=100

./build/gerador $n $n $n $n

> tempos_threads_e2.txt
> tempos_processos_e2.txt

for i in {32..2}
do
    p=$(( ($n*$n / $i ) + ($n*$n % $i > 0) ))

    echo "Rodando para p = $p"

    echo "Threads..."
    for j in {1..10}
    do
        ./build/threads matriz1.txt matriz2.txt $p
        tempo_threads=$(./scripts/tempo_threads.sh)
        soma=$(($soma+$tempo_threads))
    done
    media_threads=$((soma / 10))
    echo $p $media_threads >> tempos_threads_e2.txt
    echo "Tempo: $media_threads ms"

    echo "Processos..."
    for j in {1..10}
    do
        ./build/processos matriz1.txt matriz2.txt $p
        tempo_processos=$(./scripts/tempo_processos.sh)
        soma=$(($soma+$tempo_processos))
    done
    media_processos=$((soma / 10))
    echo $p $media_processos >> tempos_processos_e2.txt
    echo "Tempo: $media_processos ms"
done