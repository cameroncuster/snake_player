#!/bin/bash

# extract the player (shared library)
cp ../libPlayer.so .

# record scores
for ((i = 1; i <= 10; i++))
do
    ../driver 13 10 >> results.dat
    echo "Iteration: $i"
done

# average scores
./avgScores.pl < results.dat

# clean-up
rm libPlayer.so results.dat
