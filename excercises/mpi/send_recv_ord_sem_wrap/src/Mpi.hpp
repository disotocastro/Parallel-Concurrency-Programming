#ifndef MPI_WRAPPER_MPI_H
#define MPI_WRAPPER_MPI_H

#include "mpi.h"
#include "MpiError.hpp" // Agregar la inclusión de MpiError.hpp

#include <exception>
#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>

/// @brief Evita la duplicación de código y asegurar que los métodos de copia 
/// y movimiento se manejen de manera coherente.
#define DISABLE_COPY(Class) \
  DECLARE_RULE4(Class, delete)

/// @brief Esta macro define cuatro de los cinco métodos de la 
/// "regla de los cinco" para una clase en C++.
#define DECLARE_RULE4(Class, action) \
  Class(const Class& other) = action; \
  Class(Class&& other) = action; \
  Class& operator=(const Class& other) = action; \
  Class& operator=(Class&& other) = action

#define fail(error_msg) throw std::runtime_error(error_msg)

/// @class Mpi
/// @brief Clase para manejar la inicialización y finalización de MPI.
class Mpi {
  private:
    int process_number; 
    int process_count; 
    std::string process_hostname; 

  public:
    /// Datatypes
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
    static inline MPI_Datatype map(unsigned long long) { return MPI_UNSIGNED_LONG_LONG; }
    static inline MPI_Datatype map(float) { return MPI_FLOAT; }
    static inline MPI_Datatype map(double) { return MPI_DOUBLE; }
    static inline MPI_Datatype map(long double) { return MPI_LONG_DOUBLE; }
  public:
    void send(const std::string& text, int toProcess, int tag );
    void receive(std::string& text, int capacity, int fromProcess, int tag);
  
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

    /// @brief Envía un dato a un proceso específico.
    /// @param value Dato a enviar.
    /// @param toProcess Proceso de destino.
    /// @param tag Etiqueta del mensaje.
    template <typename data>
    void send(const data& value, int toProcess, int tag = 0) {
      if (MPI_Send(&value, 1, map(value), toProcess, tag, MPI_COMM_WORLD) != MPI_SUCCESS) {
        fail("MPI_Send failed");
      }
    }

    /// @brief Recibe un dato de un proceso específico.
    /// @param value Dato a recibir.
    /// @param fromProcess Proceso fuente.
    /// @param tag Etiqueta del mensaje.
    template <typename data>
    void receive(data& value, int fromProcess = MPI_ANY_SOURCE, 
                 int tag = MPI_ANY_TAG) {
      if (MPI_Recv(&value, 1, map(value), fromProcess, tag, 
          MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS) {
        fail("MPI_Recv failed");
      }
    }

    /// @brief Envía un array de datos a un proceso específico.
    /// @param values Array de datos a enviar.
    /// @param count Cantidad de elementos en el array.
    /// @param toProcess Proceso de destino.
    /// @param tag Etiqueta del mensaje.
    template <typename data>
    void send(const data* values, int count, int toProcess, int tag = 0) {
      if (MPI_Send(values, count, map(values[0]), toProcess, tag, 
          MPI_COMM_WORLD) != MPI_SUCCESS) {
        fail("MPI_Send failed");
      }
    }

    /// @brief Recibe un array de datos de un proceso específico.
    /// @param values Array de datos a recibir.
    /// @param count Cantidad de elementos en el array.
    /// @param fromProcess Proceso fuente.
    /// @param tag Etiqueta del mensaje.
    template <typename data>
    void receive(data* values, int count, int fromProcess = MPI_ANY_SOURCE, 
                                          int tag = MPI_ANY_TAG) {
      if (MPI_Recv(values, count, map(values[0]), fromProcess, tag, 
                MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS) {
        fail("MPI_Recv failed");
      }
    }

    /// @brief Envía un vector de datos a un proceso específico.
    /// @param values Vector de datos a enviar.
    /// @param toProcess Proceso de destino.
    /// @param tag Etiqueta del mensaje.
    template <typename data>
    void send(const std::vector<data>& values, int toProcess, int tag = 0) {
      if (MPI_Send(values.data(), values.size(), map(values[0]), 
                  toProcess, tag, MPI_COMM_WORLD) != MPI_SUCCESS) {
        fail("MPI_Send failed");
      }
    }

    /// @brief Recibe un vector de datos de un proceso específico.
    /// @param values Vector de datos a recibir.
    /// @param count Cantidad de elementos en el vector.
    /// @param fromProcess Proceso fuente.
    /// @param tag Etiqueta del mensaje.
    template <typename data>
    void receive(std::vector<data>& values, int count, 
      int fromProcess = MPI_ANY_SOURCE, int tag = MPI_ANY_TAG) {
      values.resize(count);
      if (MPI_Recv(values.data(), count, map(values[0]), fromProcess, tag, 
                   MPI_COMM_WORLD, MPI_STATUS_IGNORE) != MPI_SUCCESS) {
        fail("MPI_Recv failed");
      }
    }
};

#endif // MPI_WRAPPER_MPI_H
