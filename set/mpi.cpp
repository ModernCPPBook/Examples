//  Copyright (c) 2022 AUTHORS
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#include <mpi.h>

#include <chrono>

#include "config.h"
#include "kernel.h"
#include "pbm.hpp"

int main(int argc, char* argv[]) {
  size_t output = get_size_t("OUTPUT", 1);

  // Initialize the MPI environment
  MPI_Init(&argc, &argv);

  // Get the number of processes
  int mpi_size;
  MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);

  // Get the rank of the process
  int mpi_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);

  auto start_time = std::chrono::high_resolution_clock::now();

  size_t size = std::round(size_x / mpi_size);

  int start = mpi_rank * size;
  int end = (mpi_rank + 1) * size;
  if (mpi_rank == mpi_size - 1) end = size_x;

  std::vector<int> pixels(size * size_y);

  //#pragma omp parallel for
  for (size_t i = start; i < end; i++) {
    complex c =
        complex(0, 4) * complex(i, 0) / complex(size_x, 0) - complex(0, 2);

    for (size_t j = 0; j < size_y; j++) {
      // Get the number of iterations
      int value = compute_pixel(c + 4.0 * j / size_y - 2.0);
      // Convert the smoothened value to RGB color space
      std::tuple<size_t, size_t, size_t> color = get_rgb(value);
      // Set the pixel color
      pixels[(-start + i) * size_y + j] = make_color(
          std::get<0>(color), std::get<1>(color), std::get<2>(color));
    }
  }

  if (mpi_rank == 0) {
    auto stop_time = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(
        stop_time - start_time);
    std::cout << duration.count() * 1e-6 << std::endl;
  }
  // Save the image
  if (output == 1 && mpi_rank == 0) {
    PBM pbm;
    std::cout << "out " << std::endl;
    if (mpi_rank != 0) {
      MPI_Request request;
      MPI_Isend(&pixels[0], pixels.size(), MPI_INT, 0, 0, MPI_COMM_WORLD,
                &request);
      MPI_Status status;
      MPI_Wait(&request, &status);
    } else {
      pbm = PBM(size_x, size_y);

      for (size_t x = 0; x < size; x++) {
        for (size_t y = 0; y < size_y; y++) pbm(x, y) = pixels[x * size_y + y];
      }

      for (size_t i = 1; i < mpi_size; i++)

      {
        MPI_Request request;
        MPI_Irecv(&pixels[0], pixels.size(), MPI_INT, i, 0, MPI_COMM_WORLD,
                  &request);
        MPI_Status status;
        MPI_Wait(&request, &status);
        for (size_t x = 0; x < size; x++) {
          for (size_t y = 0; y < size_y; y++) {
            // std::cout << i << " " << x << " " << y << " " << i * size + x <<
            // std::endl;
            pbm(i * size + x, y) = pixels[x * size_y + y];
          }
        }
      }
      pbm.save("image_mpi_" + type + ".pbm");
    }
  }
  // Finalize the MPI environment.
  MPI_Finalize();

  return EXIT_SUCCESS;
}
