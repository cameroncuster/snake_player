for count in $(seq 1 100)
do
	./driver 20 20 >> results.dat
done
./avgScores.pl < results.dat
