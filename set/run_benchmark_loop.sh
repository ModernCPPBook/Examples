#!/bin/bash

for i in {1..40}
do
data=""
for j in {1..100}
do
    result=$(../build/set/algorithm_parallel Mandelbrot --hpx:threads=${i}) 
    data="data $result"
done
list=(`for n in $data; do printf "%015.06f\n" $n; done | sort -n`);
echo "$i,${list[${#list[*]}/2]},${list[0]},${list[${#list[*]}-1]}"
done
