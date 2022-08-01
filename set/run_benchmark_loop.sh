#!/bin/bash

for i in {1..10}
do
../build/set/algorithm_parallel Mandelbrot -t=${i} 
done


