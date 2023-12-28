#!/bin/bash

# Necessary arguments:
# $1 -- 'm' value, which is used is used to define a unirom mesh in the main program
# $2 -- number of theards for OpenMP parallelism

# How may times to run the program to estimate execution time
launchesNumber=5

# Compiling auxilary program, that computes real numbers
g++ ../auxilary/countFloats.cpp -o countFloats.out

# Compiling main program
export OMP_NUM_THREADS=$2
export OMP_WAIT_POLICY="passive"
g++ -fopenmp parallel_with_tasks.cpp -o "parallel_tasks.out"

# Run the program several times, to find out average execution time
start_T=$(date +%s.%N)
for((r = 1; r <= launchesNumber; r++))
do
	./parallel_tasks.out $1
done
end_T=$(date +%s.%N)


# Output averaged estimation
totalTime=$(./countFloats.out $end_T "-" $start_T)
avgExeTime=$(./countFloats.out $totalTime "/" $launchesNumber)
echo "Average run time (parallel_tasks m=$1 OMP_NUM_THREADS=$2): $avgExeTime"
rm parallel_tasks.out
rm countFloats.out
