#include <cstdlib>
#include <hpx/hpx.hpp>
#include <hpx/hpx_main.hpp>
#include <iostream>

#include "taylor_data.hpp"
#include "taylor_component.hpp"
#include "taylor_action.hpp"
//-----------------------------------------------------------------

HPX_PLAIN_ACTION(compute, compute_action) 

int main(int args, char** argv) {
  int n = 100;
  double x = 0.25;

  std::vector<hpx::id_type> localities = hpx::find_all_localities(); 
  std::size_t num_partitions = localities.size();  
  size_t partition_size = std::round(n / num_partitions);  

  std::vector<data_client> parts(num_partitions);

  for (size_t i = 0; i < num_partitions; i++) {  
    size_t begin = 1;

    if (i > 0) begin = i * partition_size;

    if (i == num_partitions - 1)
      parts[i] = data_client(localities[i], n - (partition_size * i), begin);  
    else
      parts[i] = data_client(localities[i], partition_size, begin);
  }

  std::vector<hpx::future<double>> futures;  

  for (size_t i = 0; i < num_partitions; i++) { 
    futures.push_back(hpx::async<compute_action>(localities[i], parts[i], x));
  }

  double result = 0;   

  hpx::when_all(futures)
    .then([&](auto&& f) {
      auto futures = f.get();
      for (size_t i = 0; i < futures.size(); i++)
        result += futures[i].get();
    })
    .get();

  std::cout << "Difference of Taylor and C++ result "
            << result - std::log1p(x) << " after " << n << " iterations."
            << std::endl;  

  return EXIT_SUCCESS;
}
