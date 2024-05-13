#include <cstdlib>
#include <hpx/hpx.hpp>
#include <hpx/hpx_main.hpp>
#include <iostream>
//-----------------------------------------------------------------
struct data {
private:
  typedef hpx::serialization::serialize_buffer<double>
      buffer_type; 

public:
  data() : label("empty") {}  
  data(const std::string& label_,size_t size) 
      : label(label_),
        data_(std::allocator<double>().allocate(size), size, buffer_type::take) {}
  data(const std::string& label_,size_t size, double* data__) 
      : label(label_),
        data_(std::allocator<double>().allocate(size), size, buffer_type::take) {
    for (size_t i = 0; i < size; i++) data_[i] = data__[i];
  }
  data(std::string label_,size_t size, double data) 
      : label(label_), data_(std::allocator<double>().allocate(size), size, buffer_type::take) {
    for (size_t i = 0; i < size; i++) data_[i] = data;
  }
  data(std::string label_,size_t size, std::function<double(int)> f) 
      : label(label_), data_(std::allocator<double>().allocate(size), size, buffer_type::take) {
    for (size_t i = 0; i < size; i++) data_[i] = f(i);
  }
  double& operator[](size_t id) { return data_[id]; } 
  double operator[](size_t id) const { return data_[id]; } 

  size_t size() const { return data_.size(); } 

  std::string get_label() const { return label; } 
  void set_label(const std::string s) { label = s; } 

 private:
  std::string label;
  buffer_type data_; 

  friend class hpx::serialization::access; 

  template <typename Archive>  
  void serialize(Archive& ar, const unsigned int) {
    ar & label;
    ar & data_;
  }
};

static data square(data d) { 
  for (size_t i =0; i <  d.size() ; i++) d[i] = d[i] * d[i];
  d.set_label(d.get_label() + " squared");
  return d;
}


std::ostream& operator<<(std::ostream& o, const data& d) { 
    o << "data('" << d.get_label() << "',{";
    for(size_t i=0;i<d.size();i++) {
        if(i > 0) o << ", ";
        o << d[i];
    }
    return o << "})";
}

HPX_PLAIN_ACTION(square,square_action);  

int main(int args, char** argv) {
    data d = data("stats",10,[](int n) { return n; });  

    auto remote = hpx::find_remote_localities (); 
    if ( remote.size () > 0) {
      hpx::future<data> future = hpx::async<square_action>(remote[0],d); 
      data result = future.get();
      std::cout << result << std::endl;
    }
  return EXIT_SUCCESS;
}
