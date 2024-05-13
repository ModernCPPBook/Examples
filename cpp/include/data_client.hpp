struct data_client
    : hpx::components::client_base<data_client, data_server> {
  typedef hpx::components::client_base<data_client, data_server>
      base_type;  

  data_client() {} 

  // Create new component on locality 'where' and initialize the
  // held data
  data_client(hpx::id_type where, std::size_t size,
              double initial_value)
      : base_type(hpx::new_<data_server>(where, size,
                                         initial_value)) {} 

  // Attach a future representing a (possibly remote) partition.
  data_client(hpx::future<hpx::id_type> &&id)
      : base_type(std::move(id)) {}  

  // Invoke the (remote) member function which gives us access to
  // the data. This is a pure helper function hiding the async.
  hpx::future<std::vector<double>> get_data() const { 
    return hpx::async(get_data_action(), get_id());
  }
};
