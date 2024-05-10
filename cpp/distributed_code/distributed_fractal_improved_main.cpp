#include <hpx/hpx.hpp>
#include <hpx/hpx_main.hpp>
#include "distributed_fractal_worker_improved.hpp"
#include <fstream>
#include <chrono>

using std::chrono::high_resolution_clock;
//-----------------------------------------------------------------
int main() {
    auto locs = hpx::find_remote_localities();

    // The supervisor
    auto supervisor = hpx::find_here();

    // Compute the number of worker localities
    const int num_workers = locs.size();

    // Make sure we have some workers
    assert(num_workers > 0);

    // The logic below assumes more work than workers
    assert(num_workers < size_x && num_workers < size_y);

    // Measure the time only on the supervisor
    high_resolution_clock::time_point start_time = high_resolution_clock::now();

    std::vector<hpx::future<void>> data;
    // Load up workers...
    for(int j=0;j<num_workers;j++) {
        auto loc = locs.at(j);
        hpx::future<void> f = hpx::async<do_work_action>(loc, supervisor, next_work_item++, j); 
        data.push_back(std::move(f));
    }

    for(int j=0;j<data.size();j++)
        data.at(j).wait();

    std::vector<hpx::future<void>> futures;

    hpx::when_all(futures).get();

    auto stop_time = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>( stop_time - start_time );
    std::cout << "Time: " << duration.count() * 1e-9 << std::endl;
}
