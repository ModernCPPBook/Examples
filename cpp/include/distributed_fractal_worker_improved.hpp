#include <config.hpp>
#include <kernel.hpp>
std::chrono::high_resolution_clock::time_point start, finish;
std::atomic<int> next_work_item(0);
std::atomic<int> completed_work_items(0);
size_t output = get_size_t("OUTPUT", 1);
//-----------------------------------------------------------------
// Called by workers to get an item of work from the supervisor
int get_work() { return next_work_item++; }
HPX_PLAIN_ACTION(get_work, get_work_action);

// The basic unit of work.
void do_work(const hpx::id_type& loc, int item_index, int id) { 
  std::ofstream outfile("data_"+std::to_string(id)+".part"); 
  while (item_index < size_x) {
    // ask for the next work item asynchronously. That way
    // we overlap communication and computation.
    hpx::future<int> fitem = hpx::async<get_work_action>(loc);
    std::vector<int> result;

    complex c = complex(0, 4) * complex(item_index, 0) /
                complex(size_x, 0) - complex(0, 2);

    for (int i = 0; i < size_y; i++) {
      // Get the number of iterations
      int value = compute_pixel(c + 4.0 * i / size_y - 2.0);
      // Convert the smoothened value to RGB color space
      std::tuple<size_t, size_t, size_t> color = get_rgb(value);
      result.push_back(make_color(std::get<0>(color),
        std::get<1>(color),std::get<2>(color)));
    }

    outfile << item_index << " "; 
    for(auto d : result)
      outfile << d << " ";
    outfile << "\n";
    item_index = fitem.get();
  }
  outfile.close(); 
}
HPX_PLAIN_ACTION(do_work, do_work_action);
