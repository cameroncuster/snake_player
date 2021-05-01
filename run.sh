#!/bin/bash

# record scores
for ((i = 1; i <= 100; i++))
do
    ./driver  3 50          >> results03x50.dat
    ./driver  3 50  true    >> results03x50Ob.dat

    ./driver  3 40          >> results03x40.dat
    ./driver  3 40  true    >> results03x40Ob.dat

    ./driver  5  5          >> results05x05.dat
    ./driver  5  5  true    >> results05x05Ob.dat

    ./driver 10 10          >> results10x10.dat
    ./driver 10 10  true    >> results10x10Ob.dat

    ./driver 10 20          >> results10x20.dat
    ./driver 10 20  true    >> results10x20Ob.dat

    ./driver 10 30          >> results10x30.dat
    ./driver 10 30  true    >> results10x30Ob.dat

    ./driver 20 20          >> results20x20.dat
    ./driver 20 20  true    >> results20x20Ob.dat

    ./driver 20 30          >> results20x30.dat
    ./driver 20 30  true    >> results20x30Ob.dat

    ./driver 30 30          >> results30x30.dat
    ./driver 30 30  true    >> results30x30Ob.dat

    echo "Iteration: $i"
done

# average scores
./avgScores.pl < results03x50.dat
./avgScores.pl < results03x50Ob.dat

./avgScores.pl < results03x40.dat
./avgScores.pl < results03x40Ob.dat

./avgScores.pl < results05x05.dat
./avgScores.pl < results05x05Ob.dat

./avgScores.pl < results10x10.dat
./avgScores.pl < results10x10Ob.dat

./avgScores.pl < results10x20.dat
./avgScores.pl < results10x20Ob.dat

./avgScores.pl < results10x30.dat
./avgScores.pl < results10x30Ob.dat

./avgScores.pl < results20x20.dat
./avgScores.pl < results20x20Ob.dat

./avgScores.pl < results20x30.dat
./avgScores.pl < results20x30Ob.dat

./avgScores.pl < results30x30.dat
./avgScores.pl < results30x30Ob.dat

# clean-up
rm *.dat
