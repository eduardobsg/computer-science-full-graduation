#!/bin/sh

PROCESSES="2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25"

echo Parallel Program >> out.txt
echo ---------------- >> out.txt

echo Polynomial: 0.625*x^4 - 4*x^3 + 2*x + 1 >> out.txt
echo Interval: [0,8] >> out.txt
echo Subintervals: 10^7 >> out.txt
echo   >> out.txt

for processes in $PROCESSES; do
  echo $processes processes >> out.txt
  for i in 1 2 3 4 5; do 
    mpirun -np $processes ./trapeze_parallel >> out.txt;
  done;
done
