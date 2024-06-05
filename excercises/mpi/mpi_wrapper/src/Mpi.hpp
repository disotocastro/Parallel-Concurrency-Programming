#ifndef MPI_WRAPPER_MPI_H
#define MPI_WRAPPER_MPI_H

#include "mpi.h"
#include "MpiError.hpp" // Agregar la inclusión de MpiError.hpp


#include <exception>
#include <iostream>
#include <string>
#include <stdexcept>

/// @brief Evitar la duplicación de código y asegurar que los métodos de copia 
/// y movimiento se manejen de manera coherente.
#define DISABLE_COPY(Class) \
  DECLARE_RULE4(Class, delete)

/// @brief Esta macro define cuatro de los cinco métodos de la "regla de los cinco" 
/// para una clase en C++.
#define DECLARE_RULE4(Class, action) \
  Class(const Class& other) = action; \
  Class(Class&& other) = action; \
  Class& operator=(const Class& other) = action; \
  Class& operator=(Class&& other) = action

/// @brief Lanza una excepción de tiempo de ejecución con el mensaje de error proporcionado.
/// @param error_msg Mensaje de error a lanzar.
#define fail(error_msg) throw std::runtime_error(error_msg)

/// @class Mpi
/// @brief Clase para manejar la inicialización y finalización de MPI.
class Mpi {
  private:
    int process_number; ///< Número del proceso actual.
    int process_count; ///< Cantidad total de procesos.
    std::string process_hostname; ///< Nombre del host del proceso.

  public:
    /// @brief Constructor que inicializa MPI.
    /// @param argc Referencia al contador de argumentos.
    /// @param argv Referencia a la lista de argumentos.
    /// @throws std::runtime_error si MPI_Init falla.
    Mpi(int &argc, char** &argv) {
      if (MPI_Init(&argc, &argv) != MPI_SUCCESS) {
        throw MpiError("MPI_Init failed");
      }
      MPI_Comm_size(MPI_COMM_WORLD, &process_count);
      MPI_Comm_rank(MPI_COMM_WORLD, &process_number);
      char char_process_name[MPI_MAX_PROCESSOR_NAME] = { '\0' };
      int hostname_length = -1;
      MPI_Get_processor_name(char_process_name, &hostname_length);
      process_hostname = std::string(char_process_name, hostname_length);
    }
  
    /// @brief Destructor que finaliza MPI.
    ~Mpi() { MPI_Finalize(); }

    /// @brief Obtiene el número del proceso actual.
    /// @return Número del proceso actual.
    inline int getProcessNumber() const {
      return process_number;
    }

    /// @brief Obtiene la cantidad total de procesos.
    /// @return Cantidad total de procesos.
    inline int getProcessCount() const {
      return process_count;
    }

    /// @brief Obtiene el nombre del host del proceso.
    /// @return Nombre del host del proceso.
    inline std::string getHostname() const {
      return process_hostname;
    }

    /// @brief Deshabilita la copia y el movimiento de objetos de esta clase.
    DISABLE_COPY(Mpi);
};

#endif // MPI_WRAPPER_MPI_H
