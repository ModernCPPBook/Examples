#ifndef TAYLOR_DATA_HPP

#define TAYLOR_DATA_HPP

struct data {
  data() : size_(0) {}

  data(size_t size)
      : data_(std ::allocator<double>().allocate(size), size,
              buffer_type ::take),
        size_(0) {}

  data(size_t size, double init)
      : data_(std ::allocator<double>().allocate(size), size,
              buffer_type ::take),
        size_(size) {
    for (size_t i = 0; i < size_; i++) data_[i] = init + i;
  }

  size_t size() { return size_; }

  double& operator[](size_t id) { return data_[id]; }

 private:
  typedef hpx ::serialization ::serialize_buffer<double> buffer_type;

  buffer_type data_;
  size_t size_;

  friend class hpx::serialization::access;

  template <typename Archive>
  void serialize(Archive& ar, const unsigned int) {
    ar& data_& size_;
  }
};

#endif