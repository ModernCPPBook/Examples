#include <pbm.hpp>
#include "config.hpp"
#include "kernel.hpp"

std::chrono::high_resolution_clock::time_point start, finish;

std::atomic<int> next_work_item(0);
std::atomic<int> completed_work_items(0);

// Called by workers to get an item of work from the supervisor
int get_work() {
    return next_work_item++;
}

HPX_PLAIN_ACTION(get_work, get_work_action);

// Called by workers to send a result to the supervisor 
void send_result(const std::vector<int>& result,int item_index) {

  /*
    if(item_index < work_to_be_done) {
        apply_result(item_index, result);
        int n = ++completed_work_items;
        // If I am the one to complete the last work item
        // then I can call finish up.
        if(n == work_to_be_done) {
            auto finish = high_resolution_clock::now();
            auto duration = duration_cast<microseconds>(finish - start);
            std::cout << "duration: " << (duration.count()*1e-6) << std::endl;
            finish_up();
        }
    }
    */
}

HPX_PLAIN_ACTION(send_result, send_result_action);

// The basic unit of work. Does nothing but hand
// args back aa a std::vector<int>.
void do_work(const hpx::id_type& loc, int item_index) {

  /*
    while(item_index < work_to_be_done) {
        // ask for the next work item asynchronously. That way
        // we overlap communication and computation.
        hpx::future<int> fitem = hpx::async<get_work_action>(loc);
        std::vector<int> result;
        create_result(item_index,result);
        // apply() is like async(), except no future comes back.
        hpx::apply<send_result_action>(loc,result,item_index);
        item_index = fitem.get();
    }

    */
}

HPX_PLAIN_ACTION(do_work, do_work_action);
