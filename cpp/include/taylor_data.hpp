#ifndef TAYLOR_DATA_HPP

#define TAYLOR_DATA_HPP

typedef hpx::serialization::serialize_buffer<double> buffer;
struct data : public buffer {
  data(size_t size=0, double value=0.0) :
    buffer(std::allocator<double>().allocate(size), size, buffer::take)
  {
    for(size_t i=0;i < size; i++) (*this)[i] = value+i;
  }
};

#endif
