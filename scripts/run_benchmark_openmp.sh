#!/bin/bash

export MAX_ITER=80
export SIZE_X=39860
export SIZE_Y=21600
export OUTPUT=0

for i in {40..1}
do
data=""
export OMP_NUM_THREADS=${i}
for j in {1..10}
do
result=$(../build/set/openmp_parallel)
array=($result)
data="$data ${array[-1]}"
done
list=(`for n in $data; do printf "%015.06f\n" $n; done | sort -n`); 
echo "$i,${list[${#list[*]}/2]},${list[0]},${list[${#list[*]}-1]}" >> data_openmp.csv
done

