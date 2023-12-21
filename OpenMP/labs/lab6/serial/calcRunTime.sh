#!/bin/bash

launchesNumber=5
g++ -fopenmp serial.cpp -o "serial.out"

start_T=$(date +%s.%N)

for((r = 1; r <= launchesNumber; r++))
do
# $1 is 'm' value, $2 is 'eps' value, look commnets in the source code
	./serial.out $1 $2
done

end_T=$(date +%s.%N)
totalTime=$(./countFloats $end_T "-" $start_T)
avgExeTime=$(./countFloats $totalTime "/" $launchesNumber)

echo "Estimated execution time (serial): $avgExeTime"

rm serial.out
