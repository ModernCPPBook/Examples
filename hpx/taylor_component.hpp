#ifndef TAYLOR_COMPONENT_HPP

#define TAYLOR_COMPONENT_HPP 

struct data_server : hpx::components::component_base<data_server> {
  // Construct a new instance
  data_server() {}

  data_server(size_t size, double const value) : data_(size, value) {}

  // Access data
  data get_data() const { return data_; }

  HPX_DEFINE_COMPONENT_DIRECT_ACTION(data_server, get_data, get_data_action)

 private:
  data data_;
};

typedef hpx::components::component<data_server> data_server_type;
HPX_REGISTER_COMPONENT(data_server_type, data_server)

typedef data_server::get_data_action get_data_action;
HPX_REGISTER_ACTION(get_data_action)

// Component client

struct data_client : hpx ::components ::client_base<data_client, data_server> {
  typedef hpx::components::client_base<data_client, data_server> base_type;

  data_client() {}

  data_client(hpx::id_type where, size_t size, double init)
      : base_type(hpx::new_<data_server>(where, size, init)) {}

  hpx::future<data> get_data() const {
    data_server::get_data_action act;
    return hpx::async(act, get_id());
  }
};
#endif