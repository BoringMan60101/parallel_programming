#!/bin/bash

launchesNumber=5
export OMP_NUM_THREADS=$3
export OMP_WAIT_POLICY="active"
g++ -fopenmp parallel_with_tasks.cpp -o "parallel_tasks.out"

start_T=$(date +%s.%N)

for((r = 1; r <= launchesNumber; r++))
do
# $1 is 'm' value, $2 is 'eps' value, look commnets in the source code
	./parallel_tasks.out $1 $2
done

end_T=$(date +%s.%N)
totalTime=$(./countFloats $end_T "-" $start_T)
avgExeTime=$(./countFloats $totalTime "/" $launchesNumber)

echo "Estimated execution time (parallel_tasks): $avgExeTime"

rm parallel_tasks.out
