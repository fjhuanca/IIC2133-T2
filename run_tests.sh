#!/bin/bash

make
for j in Easy Medium Hard
do  
    for i in {1..6..1}
    do
    echo "Running $j-$i:"
        time ./fumigate tests/${j}/test_${i}.txt
    done
done

for j in Easy Medium Hard
do
    for i in {1..6..1}
    do
    echo "Checking $j-$i:"
        python ./check.py $j $i -i
    done
done