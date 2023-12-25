#!/bin/bash

# $1 -- 'm' value, which is used is used to define a unirom mesh in the main program

# How may times to run the program to estimate execution time
launchesNumber=5

# Compiling auxilary program, that computes real numbers
g++ ../auxilary/countFloats.cpp -o countFloats.out

# Compiling main program
g++ serial.cpp -o "serial.out"

# Run the program several times, to find out average execution time
start_T=$(date +%s.%N)
for((r = 1; r <= launchesNumber; r++))
do
	./serial.out $1
done
end_T=$(date +%s.%N)

# Output averaged estimation
totalTime=$(./countFloats.out $end_T "-" $start_T)
avgExeTime=$(./countFloats.out $totalTime "/" $launchesNumber)
echo "Estimated execution time (serial): $avgExeTime"
rm serial.out
rm countFloats.out
