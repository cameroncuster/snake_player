#!/bin/bash

# extract the player (shared library)
cp ../libPlayer.so .

# record scores
for ((i = 1; i <= 10; i++))
do
    ../driver 20 16 true >> results.dat
    echo "Iteration: $i"
done

# average scores
./avgScores.pl < results.dat

# clean-up
rm libPlayer.so results.dat
