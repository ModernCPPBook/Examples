struct data_server
    : hpx::components::component_base<data_server> {

  // Construct new instances
  data_server() {} 

  data_server(size_t size_) { 
    for(int i=0;i<size_;i++)
      data.push_back(0.0);
  }

  data_server(size_t size, double const value) { 
    for (size_t i=0;i < size; ++i)
      data.push_back(value);
  }

  // Access data
  std::vector<double> get_data() const { 
    return data;
  }

  // Every member function which has to be invoked remotely needs to be  wrapped into a component action. The macro below defines a new type 'get_data_action' which represents the (possibly remote) member function
  HPX_DEFINE_COMPONENT_DIRECT_ACTION( 
  data_server, get_data, get_data_action)

  private:
    std::vector<double> data; 
};

// Code generation via macros to expose the data_server as a component for remote access

// HPX_REGISTER_COMPONENT() exposes the component creation
typedef hpx::components::component<data_server> data_server_type;
HPX_REGISTER_COMPONENT(data_server_type, data_server) 

// HPX_REGISTER_ACTION() exposes the component member function for remote invocation.
typedef data_server::get_data_action get_data_action;
HPX_REGISTER_ACTION(get_data_action) 
