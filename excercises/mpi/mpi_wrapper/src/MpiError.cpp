#include "MpiError.hpp"
#include "Mpi.hpp" 

#include <sstream>  // Para construir el mensaje de error

// Constructor que toma solo el mensaje
MpiError::MpiError(const std::string& message)
    : std::runtime_error(message) {}

// Constructor que toma el mensaje y una referencia a Mpi
MpiError::MpiError(const std::string& message, const Mpi& mpi)
  : std::runtime_error([&message, &mpi]() {
    std::ostringstream oss;
    oss << mpi.getHostname() << ":" << mpi.getProcessNumber() 
                                    << ": " << message;
    return oss.str();
  }()) {}

// Constructor que toma el mensaje, una referencia a Mpi y un número de hilo
MpiError::MpiError(const std::string& message, const Mpi& mpi, const int threadNumber)
  : std::runtime_error([&message, &mpi, threadNumber]() {
    std::ostringstream oss;
    oss << mpi.getHostname() << ":" << mpi.getProcessNumber() << "." 
                                    << threadNumber << ": " << message;
    return oss.str();
  }()) {}