#!/bin/bash

max=0

for file in resultado_threads/*
do
    tempo=`tail -n 1 $file`
    if [ $tempo -gt $max ]
    then
        max=$tempo
    fi
done

echo $max 