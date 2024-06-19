#include <iostream>
#include <stdexcept>

#include "Mpi.hpp"

int main(int argc, char* argv[]) {
  try {
    Mpi mpi(argc, argv);
    const int rank = mpi.getProcessNumber();
    const int count = mpi.getProcessCount();
    std::string hostName = mpi.getHostname();

    if (rank > 0) {
      mpi[0] << "Hello from " << rank << std::endl;
    } else {
      for (int source = 1; source < count; ++source) {
        std::string text;
        int sourceRank = 0;
        mpi[source] >> text >> sourceRank;
        std::cout << source << " says: " << text << sourceRank << std::endl;
      }
    }
  } catch (const std::exception& error) {
    std::cerr << "error: " << error.what() << std::endl;
  }
}
