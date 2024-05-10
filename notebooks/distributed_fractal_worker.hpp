#include <pbm.hpp>
#include <config.hpp>
#include <kernel.hpp>
//-----------------------------------------------------------------
std::chrono::high_resolution_clock::time_point start, finish;
std::atomic<int> next_work_item(0); 
std::atomic<int> completed_work_items(0);
size_t output = get_size_t("OUTPUT", 1);
PBM p;

// Called by workers to get an item of work from the supervisor
int get_work() { return next_work_item++; } 
HPX_PLAIN_ACTION(get_work, get_work_action);

// Called by workers to send a result to the supervisor
void send_result(const std::vector<int>& result, int item_index) { 
  if (item_index < size_x) {
    p.row(item_index) = result;
    int n = ++completed_work_items;  
    // If the work is complete
    // then I can call finish up.
    if (n == size_x) {
      auto finish = std::chrono::high_resolution_clock::now();
      auto duration =
          std::chrono::duration_cast<std::chrono::microseconds>(finish - start);
      std::cout << "duration: " << (duration.count() * 1e-6) << std::endl;
      if ( output == 1)
          p.save("image_distributed.pbm");
    }
  }
}
HPX_PLAIN_ACTION(send_result, send_result_action); 

// The basic unit of work.
void do_work(const hpx::id_type& loc, int item_index) { 
  while (item_index < size_x) {
    // ask for the next work item asynchronously. That way
    // we overlap communication and computation.
    hpx::future<int> fitem = hpx::async<get_work_action>(loc);  
    std::vector<int> result; 

    complex c = complex(0, 4) * complex(item_index, 0) / complex(size_x, 0) -
                complex(0, 2);

    for (int i = 0; i < size_y; i++) {
      // Get the number of iterations
      int value = compute_pixel(c + 4.0 * i / size_y - 2.0);
      // Convert the value to RGB color space
      std::tuple<size_t, size_t, size_t> color = get_rgb(value);
      result.push_back(make_color(std::get<0>(color),
                                  std::get<1>(color),
                                  std::get<2>(color)));
    } 

    // apply() is like async(), except no future comes back.
    hpx::apply<send_result_action>(loc, result, item_index); 
    item_index = fitem.get(); 
  }
}
HPX_PLAIN_ACTION(do_work, do_work_action); 
