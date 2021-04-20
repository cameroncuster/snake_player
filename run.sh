make driver
for count in $(seq 1 100)
do
	./driver 40 33 >> results.dat
done
./avgScores.pl < results.dat
