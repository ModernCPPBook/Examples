#ifndef UTIL_HPP
#define UTIL_HPP

// Split work evenly as possible. If the work cannot be
// divided exactly equally, then then first few workers
// will have one more item than the remainder.
void split_work(std::size_t workers, std::size_t work_items,
                std::size_t worker_num, std::size_t &start,
                std::size_t &end) {
  std::size_t partition_size = work_items / workers;
  std::size_t excess = work_items % workers;
  start = partition_size *  worker_num    + (std::min)(worker_num  , excess);
  end   = partition_size * (worker_num+1) + (std::min)(worker_num+1, excess);
}
#endif
