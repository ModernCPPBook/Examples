#include <iostream>

#include <hpx/hpx.hpp>
#include <hpx/hpx_main.hpp>
#include <sstream>
//-----------------------------------------------------------------
std::string msg() {
  std::ostringstream msg;
  msg << "Hello, world, from " << hpx::find_here();
  return msg.str();
}

// Make it possible to call msg() on another location.
HPX_PLAIN_ACTION(msg, msg_action);

int main() {
  auto localities = hpx::find_remote_localities();
  std::cout << "Sender is: " << hpx::find_here() << std::endl;
  std::cout << "Receiver is: " << localities[0] << std::endl;
  // Run the message on locality 1 and get the result in a future.
  hpx::future<std::string> f = hpx::async<msg_action>(localities[0]);
  std::cout << "Message is: " << f.get() << std::endl;
}
