#ifndef MPI_WRAPPER_MPI_H
#define MPI_WRAPPER_MPI_H

#include <exception>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "MpiError.hpp"
#include "MpiStream.hpp"  // Include the MpiStream header
#include "mpi.h"

#define DISABLE_COPY(Class) DECLARE_RULE4(Class, delete)
#define DECLARE_RULE4(Class, action)             \
  Class(const Class& other) = action;            \
  Class(Class&& other) = action;                 \
  Class& operator=(const Class& other) = action; \
  Class& operator=(Class&& other) = action

#define fail(error_msg) throw std::runtime_error(error_msg)

class Mpi {
 private:
  int process_number;
  int process_count;
  std::string process_hostname;

 public:
  static inline MPI_Datatype map(bool) { return MPI_C_BOOL; }
  static inline MPI_Datatype map(char) { return MPI_CHAR; }
  static inline MPI_Datatype map(unsigned char) { return MPI_UNSIGNED_CHAR; }
  static inline MPI_Datatype map(short) { return MPI_SHORT; }
  static inline MPI_Datatype map(unsigned short) { return MPI_UNSIGNED_SHORT; }
  static inline MPI_Datatype map(int) { return MPI_INT; }
  static inline MPI_Datatype map(unsigned) { return MPI_UNSIGNED; }
  static inline MPI_Datatype map(long) { return MPI_LONG; }
  static inline MPI_Datatype map(unsigned long) { return MPI_UNSIGNED_LONG; }
  static inline MPI_Datatype map(long long) { return MPI_LONG_LONG; }
  static inline MPI_Datatype map(unsigned long long) {
    return MPI_UNSIGNED_LONG_LONG;
  }
  static inline MPI_Datatype map(float) { return MPI_FLOAT; }
  static inline MPI_Datatype map(double) { return MPI_DOUBLE; }
  static inline MPI_Datatype map(long double) { return MPI_LONG_DOUBLE; }

 public:
  void send(const std::string& text, int toProcess, int tag);
  void receive(std::string& text, int capacity, int fromProcess, int tag);

  Mpi(int& argc, char**& argv) {
    if (MPI_Init(&argc, &argv) != MPI_SUCCESS) {
      throw MpiError("MPI_Init failed");
    }
    MPI_Comm_size(MPI_COMM_WORLD, &process_count);
    MPI_Comm_rank(MPI_COMM_WORLD, &process_number);
    char char_process_name[MPI_MAX_PROCESSOR_NAME] = {'\0'};
    int hostname_length = -1;
    MPI_Get_processor_name(char_process_name, &hostname_length);
    process_hostname = std::string(char_process_name, hostname_length);
  }

  ~Mpi() { MPI_Finalize(); }

  inline int getProcessNumber() const { return process_number; }
  inline int getProcessCount() const { return process_count; }
  inline std::string getHostname() const { return process_hostname; }

  DISABLE_COPY(Mpi);

  template <typename data>
  void send(const data& value, int toProcess, int tag = 0) {
    if (MPI_Send(&value, 1, map(value), toProcess, tag, MPI_COMM_WORLD) !=
        MPI_SUCCESS) {
      fail("MPI_Send failed");
    }
  }

  template <typename data>
  void receive(data& value, int fromProcess = MPI_ANY_SOURCE,
               int tag = MPI_ANY_TAG) {
    if (MPI_Recv(&value, 1, map(value), fromProcess, tag, MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE) != MPI_SUCCESS) {
      fail("MPI_Recv failed");
    }
  }

  template <typename data>
  void send(const data* values, int count, int toProcess, int tag = 0) {
    if (MPI_Send(values, count, map(values[0]), toProcess, tag,
                 MPI_COMM_WORLD) != MPI_SUCCESS) {
      fail("MPI_Send failed");
    }
  }

  template <typename data>
  void receive(data* values, int count, int fromProcess = MPI_ANY_SOURCE,
               int tag = MPI_ANY_TAG) {
    if (MPI_Recv(values, count, map(values[0]), fromProcess, tag,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS) {
      fail("MPI_Recv failed");
    }
  }

  template <typename data>
  void send(const std::vector<data>& values, int toProcess, int tag = 0) {
    if (MPI_Send(values.data(), values.size(), map(values[0]), toProcess, tag,
                 MPI_COMM_WORLD) != MPI_SUCCESS) {
      fail("MPI_Send failed");
    }
  }

  template <typename data>
  void receive(std::vector<data>& values, int count,
               int fromProcess = MPI_ANY_SOURCE, int tag = MPI_ANY_TAG) {
    values.resize(count);
    if (MPI_Recv(values.data(), count, map(values[0]), fromProcess, tag,
                 MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS) {
      fail("MPI_Recv failed");
    }
  }

  MpiStream operator[](int target) { return MpiStream(*this, target); }
};

#endif  // MPI_WRAPPER_MPI_H
