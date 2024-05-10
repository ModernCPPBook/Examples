#include <hpx/hpx.hpp>
#include <hpx/hpx_main.hpp>

#include <distributed_fractal_worker.hpp>
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

    // Allocate the PBM image only for the supervisor
    p = PBM(size_y, size_x);

    start = std::chrono::high_resolution_clock::now(); 

    // Place to hold futures for current worker tasks
    std::vector<hpx::future<void>> data;  

    // Load up workers...
    for(int j=0;j<num_workers;j++) {  
        auto loc = locs.at(j);
        hpx::future<void> f = hpx::async<do_work_action>(loc, supervisor, next_work_item++); 
        data.push_back(std::move(f)); 
    }
    for(int j=0;j<data.size();j++) {
        data.at(j).wait(); 
    }

}
