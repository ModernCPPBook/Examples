#!/usr/bin/env bash
#SBATCH -o hello2.out
#SBATCH -e hello2.err
#SBATCH -t 48:00:00
#SBATCH -p medusa
#SBATCH -N 1
#SBATCH --mail-user=pdiehl@cct.lsu.edu

module load gcc hwloc boost gperftools

./run_benchmark_loop.sh > datai_loop.csv
./run_benchmark_thread.sh > data_thread.csv
./run_benchmark_future.sh > data_future.csv
