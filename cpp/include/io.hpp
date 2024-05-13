#ifndef IO_HPP
#define IO_HPP

void save_image(PBM &pbm, size_t mpi_size, size_t size_x,
                size_t size_y) {
  std :: size_t iter_start , iter_end ;
  for(int worker=1;worker<mpi_size;worker++) { 
    split_work(mpi_size, size_x, worker, iter_start, iter_end);
    for(size_t iter=iter_start;iter < iter_end; ++iter) {  
      std::vector<int> v; 
      v.resize(size_y); 
      MPI_Status status;
      MPI_Recv((void*)v.data(),size_y,MPI_INT,worker,iter,MPI_COMM_WORLD,&status);   
      assert(pbm.row(iter).size() == v.size());
      pbm.row(iter) = v; 
    }
  }
  // Save the image
  pbm.save("image_mpi.pbm"); 
}
#endif
