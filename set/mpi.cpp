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
  MPI_Init(NULL, NULL);

  // Get the number of processes
  int mpi_size;
  MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);

  // Get the rank of the process
  int mpi_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);

  auto start_time = std::chrono::high_resolution_clock::now();

  size_t size = std::round(size_x / mpi_size);

  PBM pbm = PBM(size, size_y);

  size_t start = mpi_rank * size;
  size_t end = (mpi_rank + 1) * size;
  if (mpi_rank == mpi_size - 1) end = size_x;

  for (size_t i = start; i < end; i++) {
    complex c =
        complex(0, 4) * complex(i, 0) / complex(size_x, 0) - complex(0, 2);

    for (size_t j = 0; j < size_y; j++) {
      // Get the number of iterations
      int value = compute_pixel(c + 4.0 * j / size_y - 2.0);
      // Convert the smoothened value to RGB color space
      std::tuple<size_t, size_t, size_t> color = get_rgb(value);
      // Set the pixel color
      pbm(i - start, j) = make_color(std::get<0>(color), std::get<1>(color),
                                     std::get<2>(color));
    }
  }

  auto stop_time = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::seconds>(stop_time - start_time);
  std::cout << duration.count() << std::endl;

  // Save the image
  if (output == 1 && mpi_rank == 0) pbm.save("image_mpi_" + type + ".pbm");

  // Finalize the MPI environment.
  MPI_Finalize();

  return EXIT_SUCCESS;
}
