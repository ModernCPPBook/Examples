#include <vector>
#include <hpx/hpx.hpp>
#include <hpx/hpx_main.hpp>

#include <data_server.hpp>
#include <data_client.hpp>
//-----------------------------------------------------------------

int main(int args, char **argv) {

  std::vector<hpx::id_type> localities = hpx::find_all_localities(); 

  // Generate ten double values initialized with 1
  // on the local locality, i.e. localities[0].
  data_client local = data_client(localities[0],10,1); 
  hpx::future<std::vector<double>> data_local = local.get_data(); 

  // Generate ten double values initialized with 2
  // on the first remote locality
  if (localities.size() > 0) {
  	  data_client remote(localities[1],20,2); 
	  hpx::future<std::vector<double>> data_remote = remote.get_data(); 
	  std::vector<double> d_remote = data_remote.get(); 
      std::cout << "remote: " << d_remote[1] << std::endl;
  }

  std::vector<double> d_local = data_local.get(); 
  std::cout << "local: " << d_local[1] << std::endl;

  return EXIT_SUCCESS;
}
