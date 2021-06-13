#!/bin/bash
make
declare -a difficulty=("Easy" "Medium" "Hard" "Lunatic")
for j in ${difficulty[@]}
do
    for i in {1..6..1}
    do
    echo "Running $j-$i:"
        time ./fumigate tests/${j}/test_${i}.txt
    done
done
for j in ${difficulty[@]}
do
    for i in {1..6..1}
    do
    echo "Checking $j-$i:"
        python3 ./check.py ${j} ${i} -i
    done
done