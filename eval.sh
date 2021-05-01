#!/bin/bash

# record scores
for ((i = 1; i <= 100; i++))
do
    ./driver  3 40          >> results03x40.dat
    ./driver  3 40  true    >> results03x40Ob.dat

    ./driver  3 50          >> results03x50.dat
    ./driver  3 50  true    >> results03x50Ob.dat

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
echo "## Performance ##"
echo "**Performance 03x40**"
./avgScores.pl < results03x40.dat

echo "**Performance 03x40 Obstacles**"
./avgScores.pl < results03x40Ob.dat

echo "**Performance 03x50**"
./avgScores.pl < results03x50.dat

echo "**Performance 03x50 Obstacles**"
./avgScores.pl < results03x50Ob.dat

echo "**Performance 05x05**"
./avgScores.pl < results05x05.dat

echo "**Performance 05x05 Obstacles**"
./avgScores.pl < results05x05Ob.dat

echo "**Performance 10x10**"
./avgScores.pl < results10x10.dat

echo "**Performance 10x10 Obstacles**"
./avgScores.pl < results10x10Ob.dat

echo "**Performance 10x20**"
./avgScores.pl < results10x20.dat

echo "**Performance 10x20 Obstacles**"
./avgScores.pl < results10x20Ob.dat

echo "**Performance 10x30**"
./avgScores.pl < results10x30.dat

echo "**Performance 10x30 Obstacles**"
./avgScores.pl < results10x30Ob.dat

echo "**Performance 20x20**"
./avgScores.pl < results20x20.dat

echo "**Performance 20x20 Obstacles**"
./avgScores.pl < results20x20Ob.dat

echo "**Performance 20x30**"
./avgScores.pl < results20x30.dat

echo "**Performance 20x30 Obstacles**"
./avgScores.pl < results20x30Ob.dat

echo "**Performance 30x30**"
./avgScores.pl < results30x30.dat

echo "**Performance 30x30 Obstacles**"
./avgScores.pl < results30x30Ob.dat

# clean-up
rm *.dat
