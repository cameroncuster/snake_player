#!/bin/bash

# record scores
for ((i = 1; i <= 10; i++))
do
    ./driver 13 10 >> results.dat
    echo "Iteration: $i"
done

# average scores
./avgScores.pl < results.dat

# clean-up
rm results.dat
