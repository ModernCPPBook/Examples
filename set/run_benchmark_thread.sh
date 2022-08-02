#!/bin/bash

for i in {1..10}
do
../build/set/thread_parallel Mandelbrot ${i} 
done


