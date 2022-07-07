#!/bin/bash

for i in {1..9}
do
 ../build/sl/benchmark_containers "$((10**$i))"
done