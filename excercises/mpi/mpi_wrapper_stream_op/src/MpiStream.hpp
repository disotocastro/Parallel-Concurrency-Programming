#ifndef MPISTREAM_HPP
#define MPISTREAM_HPP

#include <string>

class Mpi;

class MpiStream {
  Mpi& mpi;
  int process_number;

 public:
  MpiStream(Mpi& mpi, int process_number);

  template <typename T>
  MpiStream& operator<<(const T& data);

  template <typename T>
  MpiStream& operator>>(T& data);

  MpiStream& operator<<(const std::string& text);
};

#endif  // MPISTREAM_HPP
