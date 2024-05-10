#define USE_HPX 1
#include <algorithm>
#include <future>
#include <iostream>
#include <numeric>
#include <pbm.hpp>
#include "config.hpp"
#include "kernel.hpp"
//-----------------------------------------------------------------
#if USE_HPX 
#include <hpx/hpx.hpp>
#include <hpx/hpx_main.hpp>
namespace par = hpx;
#else
namespace par = std;
#endif

void launch(size_t begin, size_t end, PBM* pbm) {
  for (size_t i = begin; i < end; i++) {
    complex c = complex(0, 4) * complex(i, 0) /
        complex(size_x, 0) - complex(0, 2);

    for (size_t j = 0; j < size_y; j++) {
      int value = compute_pixel(c + 4.0 * j / size_y - 2.0);
      // Convert the value to RGB color space
      std::tuple<size_t, size_t, size_t> color = get_rgb(value);
      // Set the pixel color
      (*pbm)(i, j) = make_color(std::get<0>(color),
                                std::get<1>(color),
                                std::get<2>(color));
    }
  }
}

int main(int argc, char* argv[]) {
  size_t partitions = get_size_t("NUM_THREADS", 3);
  size_t output = get_size_t("OUTPUT", 1);
  PBM pbm = PBM(size_x, size_y);

  size_t size = std::round(size_x / partitions);
  std::vector<par::future<void>> futures; 
  auto start = std::chrono::high_resolution_clock::now();
  for (size_t i = 0; i < partitions; i++) {
    size_t start = i * size;
    size_t end = (i + 1) * size;
    if (i == partitions - 1) end = size_x;
    auto f = par::async(launch, start, end, &pbm); 
    futures.push_back(std::move(f)); 
  }
  for (auto&& f : futures) f.wait(); 
  auto stop = std::chrono::high_resolution_clock::now();
  auto duration =
      std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
  std::cout << duration.count() * 1e-6 << std::endl;

  // Save the image
  if (output == 1) pbm.save("image_future_parallel_" + type + ".pbm");

  return EXIT_SUCCESS;
}
