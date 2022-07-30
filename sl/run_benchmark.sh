#!/bin/bash


for i in {1..1}
do
data1=""
data2=""
data3=""
data4=""
data5=""
data6=""
data7=""
data8=""
data9=""
data10=""

for j in {1..100}
do
result=($(../build/sl/benchmark_containers "$((10**$i))")) 
data1="$data1 ${result[1]}"
data2="$data2 ${result[2]}"
data3="$data3 ${result[3]}"
data4="$data4 ${result[4]}"
data5="$data5 ${result[5]}"
data6="$data6 ${result[6]}"
data7="$data7 ${result[7]}"
data8="$data8 ${result[8]}"
data9="$data9 ${result[9]}"
data10="$data10 ${result[10]}"
done

std1=$(echo ${data1[@]} | awk 'NF {sum=0;ssq=0;for (i=1;i<=NF;i++){sum+=$i;ssq+=$i**2}; print (ssq/NF-(sum/NF)**2)**0.5}')
std2=$(echo ${data2[@]} | awk 'NF {sum=0;ssq=0;for (i=1;i<=NF;i++){sum+=$i;ssq+=$i**2}; print (ssq/NF-(sum/NF)**2)**0.5}')
std3=$(echo ${data3[@]} | awk 'NF {sum=0;ssq=0;for (i=1;i<=NF;i++){sum+=$i;ssq+=$i**2}; print (ssq/NF-(sum/NF)**2)**0.5}')
std4=$(echo ${data4[@]} | awk 'NF {sum=0;ssq=0;for (i=1;i<=NF;i++){sum+=$i;ssq+=$i**2}; print (ssq/NF-(sum/NF)**2)**0.5}')
std5=$(echo ${data5[@]} | awk 'NF {sum=0;ssq=0;for (i=1;i<=NF;i++){sum+=$i;ssq+=$i**2}; print (ssq/NF-(sum/NF)**2)**0.5}')
std6=$(echo ${data6[@]} | awk 'NF {sum=0;ssq=0;for (i=1;i<=NF;i++){sum+=$i;ssq+=$i**2}; print (ssq/NF-(sum/NF)**2)**0.5}')
std8=$(echo ${data7[@]} | awk 'NF {sum=0;ssq=0;for (i=1;i<=NF;i++){sum+=$i;ssq+=$i**2}; print (ssq/NF-(sum/NF)**2)**0.5}')
std8=$(echo ${data8[@]} | awk 'NF {sum=0;ssq=0;for (i=1;i<=NF;i++){sum+=$i;ssq+=$i**2}; print (ssq/NF-(sum/NF)**2)**0.5}')
std9=$(echo ${data9[@]} | awk 'NF {sum=0;ssq=0;for (i=1;i<=NF;i++){sum+=$i;ssq+=$i**2}; print (ssq/NF-(sum/NF)**2)**0.5}')
std10=$(echo ${data10[@]} | awk 'NF {sum=0;ssq=0;for (i=1;i<=NF;i++){sum+=$i;ssq+=$i**2}; print (ssq/NF-(sum/NF)**2)**0.5}')

sum1=$(echo ${data1[@]} | awk 'NF {sum=0;for (i=1;i<=NF;i++){sum+=$i;}; print (sum/NF)}')
sum2=$(echo ${data2[@]} | awk 'NF {sum=0;for (i=1;i<=NF;i++){sum+=$i;}; print (sum/NF)}')
sum3=$(echo ${data3[@]} | awk 'NF {sum=0;for (i=1;i<=NF;i++){sum+=$i;}; print (sum/NF)}')
sum4=$(echo ${data4[@]} | awk 'NF {sum=0;for (i=1;i<=NF;i++){sum+=$i;}; print (sum/NF)}')
sum5=$(echo ${data5[@]} | awk 'NF {sum=0;for (i=1;i<=NF;i++){sum+=$i;}; print (sum/NF)}')
sum6=$(echo ${data6[@]} | awk 'NF {sum=0;for (i=1;i<=NF;i++){sum+=$i;}; print (sum/NF)}')
sum7=$(echo ${data7[@]} | awk 'NF {sum=0;for (i=1;i<=NF;i++){sum+=$i;}; print (sum/NF)}')
sum8=$(echo ${data8[@]} | awk 'NF {sum=0;for (i=1;i<=NF;i++){sum+=$i;}; print (sum/NF)}')
sum9=$(echo ${data9[@]} | awk 'NF {sum=0;for (i=1;i<=NF;i++){sum+=$i;}; print (sum/NF)}')
sum10=$(echo ${data10[@]} | awk 'NF {sum=0;for (i=1;i<=NF;i++){sum+=$i;}; print (sum/NF)}')
echo "$result,$sum1,$std1,$sum2,$std2,$sum3,$std3,$sum4,$std4,$sum5,$std5,$sum6,$std6,$sum7,$std7,$sum8,$std8,$sum9,$std9,$sum10,$std10"
done

