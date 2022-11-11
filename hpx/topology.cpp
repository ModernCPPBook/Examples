#include <cstdlib>
#include <hpx/hpx.hpp>
#include <hpx/hpx_main.hpp>
#include <iostream>

int main(int args, char** argv) {

    // Get the number of OS threads
    std::cout <<  hpx::get_os_thread_count() << std::endl;

    // Get the number of all localities
    std::cout << hpx::get_num_localities().get() << std::endl;

    // Get all localities
    std::cout << hpx::find_all_localities().size() << std::endl;

    // Get all remote localities
    std::cout << hpx::find_all_localities().size() << std::endl;

    return EXIT_SUCCESS;
}
