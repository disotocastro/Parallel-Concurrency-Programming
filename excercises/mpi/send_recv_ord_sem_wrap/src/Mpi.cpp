#include <string>
#include <iostream>

#include "Mpi.hpp"
#include "MpiError.hpp"

#define sendMpiError(msg) throw MpiError(msg)

void Mpi::send(const std::string& text, int toProcess, int tag ) {
  if ( MPI_Send(text.data(), text.length(), map(text[0]), toProcess, tag,
  MPI_COMM_WORLD) != MPI_SUCCESS ) {
    throw MpiError("MPI_Send failed");
  }
}

void Mpi::receive(std::string& text, int capacity,
  int fromProcess, int tag) {
  if ( MPI_Recv(&text[0], capacity, MPI_CHAR, fromProcess, tag,
    MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS ) {
    throw MpiError("MPI_Recv failed");
  }
}
