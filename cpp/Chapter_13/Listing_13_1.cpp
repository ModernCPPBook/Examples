#include <mpi.h>
#include <chrono>

#include <config.hpp>
#include <pbm.hpp>
#include <kernel.hpp>
#include <util.hpp>
#include <io.hpp>
//-----------------------------------------------------------------

using std::chrono::high_resolution_clock;
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
  PBM pbm;
  if (mpi_rank == 0){
    start_time  = high_resolution_clock::now(); 
  }
  pbm = PBM(size_y, size_x);

  std::size_t iter_start, iter_end;
  split_work(mpi_size, size_x, mpi_rank, iter_start, iter_end); 

  for (size_t iter = iter_start; iter < iter_end; iter++) { 
    pbm.row(iter) = compute_row(iter);
    assert(pbm.row(iter).size() == size_y);
    if(mpi_rank > 0) {
       MPI_Request req;
       MPI_Isend((void*)pbm.row(iter).data(),size_y,MPI_INT,0,iter,MPI_COMM_WORLD,&req); 
    }
  } 

  // Save the image
  if (mpi_rank == 0) { 
     save_image(pbm, mpi_size, size_x, size_y);
  }
  // Stop the timer
  if (mpi_rank == 0){
    auto stop_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
        stop_time - start_time);
    std::cout << "Time: " << duration.count()*1e-9 << std::endl;
  }
  // Finalize the MPI environment.
  MPI_Finalize();  
}
