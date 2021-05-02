#!/bin/bash

# average scores
./parsetoPlot.pl < results03x40.dat     >> points.dat

./parsetoPlot.pl < results03x40Ob.dat   >> points.dat

./parsetoPlot.pl < results03x50.dat     >> points.dat

./parsetoPlot.pl < results03x50Ob.dat   >> points.dat

./parsetoPlot.pl < results05x05.dat     >> points.dat

./parsetoPlot.pl < results05x05Ob.dat   >> points.dat

./parsetoPlot.pl < results10x10.dat     >> points.dat

./parsetoPlot.pl < results10x10Ob.dat   >> points.dat

./parsetoPlot.pl < results10x20.dat     >> points.dat

./parsetoPlot.pl < results10x20Ob.dat   >> points.dat

./parsetoPlot.pl < results10x30.dat     >> points.dat

./parsetoPlot.pl < results10x30Ob.dat   >> points.dat

./parsetoPlot.pl < results20x20.dat     >> points.dat

./parsetoPlot.pl < results20x20Ob.dat   >> points.dat

./parsetoPlot.pl < results20x30.dat     >> points.dat

./parsetoPlot.pl < results20x30Ob.dat   >> points.dat

./parsetoPlot.pl < results30x30.dat     >> points.dat

./parsetoPlot.pl < results30x30Ob.dat   >> points.dat

# plot
python3 plotPlayer.py < points.dat
