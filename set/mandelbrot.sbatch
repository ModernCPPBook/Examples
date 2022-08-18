#!/usr/bin/env bash
#SBATCH -o hello2.out
#SBATCH -e hello2.err
#SBATCH -t 04:00:00
#SBATCH -p medusa
#SBATCH -N 1
#SBATCH --mail-user=pdiehl@cct.lsu.edu

module load gcc boost

./run_benchmark_loop.sh > data_loop.csv
./run_benchmark_thread.sh > data_thread.csv
./run_benchmark_future.sh > data_future.csv
./run_benchmark_future_hpx.sh > data_future_hpx.csv
