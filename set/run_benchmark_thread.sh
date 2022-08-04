#!/bin/bash

export MAX_ITER=240
export SIZE_X=384000
export SIZE_Y=216000
   
for i in {1..40}
do
data=""
export NUM_THREADS=${i}
for j in {1..10}
do
    result=$(../build/set/thread_parallel)
data="$data $result"
done
list=(`for n in $data; do printf "%015.06f\n" $n; done | sort -n`); 
echo "$i,${list[${#list[*]}/2]},${list[0]},${list[${#list[*]}-1]}"
done
