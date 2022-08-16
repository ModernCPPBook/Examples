#!/bin/bash

export MAX_ITER=240
export SIZE_X=384000
export SIZE_Y=216000   

for i in {1..40}
do
data=""
for j in {1..10}
do
    result=$(../build/set/algorithm_parallel Mandelbrot --hpx:threads=${i} -Ihpx.stacks.use_guard_pages=0) 
    array=($result)
    data="$data ${array[-1]}"
     
done
list=(`for n in $data; do printf "%015.06f\n" $n; done | sort -n`);
echo "$i,${list[${#list[*]}/2]},${list[0]},${list[${#list[*]}-1]}"
done
