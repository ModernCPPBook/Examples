#include <mpi.h>
#include <chrono>
#include <fstream>
#include <config.hpp>
#include <kernel.hpp>
#include <util.hpp>

using std::chrono::high_resolution_clock;
//-----------------------------------------------------------------
int main() {
  // Initialize the MPI environment
  MPI_Init(NULL, NULL);
  // Get the number of processes or nodes
  int mpi_size;
  MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
  // Get the rank of the process
  int mpi_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);
  // Start the timer
  high_resolution_clock::time_point start_time;
  std::ofstream outfile ("data_"+std::to_string(mpi_rank)+".part");
  if (mpi_rank == 0)
    start_time  = high_resolution_clock::now();

  std::size_t iter_start, iter_end;
  split_work(mpi_size, size_x, mpi_rank, iter_start, iter_end); 

  std::vector<std::vector<int>> data(iter_end-iter_start); 

  #pragma omp parallel for   
  for (size_t iter = iter_start; iter < iter_end; iter++) { 
    data[iter-iter_start] = compute_row(iter);
  }

  size_t iter  = iter_start;  
  for( auto row : data){
     outfile << iter << " ";
     for(auto color : row)
       outfile << color << " ";
     outfile << "\n";
     iter++;
  }  

  // Stop the timer
  if (mpi_rank == 0){
    auto stop_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
    stop_time - start_time);
    std::cout << "Time: " << duration.count()*1e-9 << std::endl;
  }
  outfile.close();
  // Finalize the MPI environment.
  MPI_Finalize();
}
