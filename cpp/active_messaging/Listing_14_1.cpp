#include <mpi.h>
#include <sstream>
//-----------------------------------------------------------------
int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  int sender = 1;
  int receiver = 0;
  int tag = 16;
  if(rank == sender) {
    std::ostringstream msg;
    msg << "Hello, world, from " << sender;
    auto m = msg.str();
    std::cout << "Sender is: " << sender << std::endl;
    MPI_Send(m.c_str(), m.size()+1, MPI_CHAR, receiver, tag, MPI_COMM_WORLD);
  } else if(rank == receiver) {
    char msgbuf[100];
    MPI_Recv(msgbuf, sizeof(msgbuf), MPI_CHAR, sender, tag, MPI_COMM_WORLD, nullptr);
    std::cout << "Receiver is: " << receiver << std::endl;
    std::cout << "Message is: " << msgbuf << std::endl;
  }
  MPI_Finalize();
}
