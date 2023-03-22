#include <hpx/hpx.hpp>
#include <hpx/hpx_main.hpp>

#include "distributed_fractal_worker.hpp"

int main() {
  auto locs = hpx::find_all_localities();
  // The supervisor
  auto supervisor = locs[0];

  // Compute the number of worker localities
  const int num_workers = locs.size() - 1;

  // Make sure we have some workers
  assert(num_workers > 0);

  // The logic below assumes more work than workers
  assert(num_workers < size_x and num_workers < size_y);

  if ( supervisor == hpx::find_here())
    p = PBM(size_x, size_y);

  start = std::chrono::high_resolution_clock::now();

  // Place to hold futures for current worker tasks
  std::vector<hpx::future<void>> data;

  // Load up workers...
  for (int j = 0; j < num_workers; j++) {
    int loc_index = 1 + (j % num_workers);
    auto loc = locs.at(loc_index);
    hpx::future<void> f =
        hpx::async<do_work_action>(loc, supervisor, next_work_item++);
    data.push_back(std::move(f));
  }
  for (int j = 0; j < data.size(); j++) {
    data.at(j).wait();
  }
}
