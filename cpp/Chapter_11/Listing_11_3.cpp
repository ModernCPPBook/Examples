#include <vector>
#include <pbm.hpp>
#include <hpx/hpx.hpp>
#include <hpx/hpx_main.hpp>
#include <kernel.hpp>
//-----------------------------------------------------------------

void launch(size_t start, size_t end, PBM *pbm) {

  for (size_t i = start; i < end; i ++)
    pbm->row(i) = compute_row(i);
}

hpx::future<void> run(size_t partitions, PBM *pbm) {
  std::vector<hpx::future<void>> futures;

  size_t size = size_y / partitions;

  for (size_t i = 0; i < partitions; i++) {
    size_t start = i * size;
    size_t end = (i + 1) * size;
    if (i == partitions - 1) end = size_y;
    auto f = hpx::async(launch, start, end, pbm);

    futures.push_back(std::move(f));
  }

  auto futures2 = co_await hpx::when_all(std::move(futures)); 

  co_return; 
}

int main(){

  PBM pbm(size_y, size_x);

  auto start_time = std::chrono::high_resolution_clock::now();

  run(4,&pbm).get();

  auto stop_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
    stop_time - start_time);
  std::cout << "Total time(s): " << duration.count()*1e-9 << std::endl;

  // Save the image
  pbm.save("image.pbm");
}
