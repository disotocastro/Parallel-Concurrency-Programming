#include <mpi.h>

#include <chrono>
#include <iostream>
#include <stdexcept>
#include <thread>

int main(int argc, char* argv[]) {
  // Inicializa el entorno MPI
  MPI_Init(&argc, &argv);

  int world_size;
  // Obtiene el número total de procesos en el comunicador global
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  // Verifica que el número de procesos sea exactamente 2
  if (world_size != 2) {
    if (world_size == 1) {
      std::cerr << "Se necesitan al menos dos procesos para jugar."
                << std::endl;
    } else {
      std::cerr << "Este programa solo soporta dos procesos." << std::endl;
    }
    // Aborta el programa si el número de procesos no es 2
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  int world_rank;
  // Obtiene el rango (identificador) del proceso actual dentro del comunicador
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  int delay = 0;  // El retraso por defecto es 0 milisegundos
  if (argc == 2) {
    // Si se especifica un argumento, se usa como el retraso en milisegundos
    delay = std::stoi(argv[1]);
  }

  int ball = 0;  // Representa la bola que se pasa entre los procesos
  while (true) {
    if (world_rank == 0) {
      // Proceso 0 envía la bola al proceso 1
      std::cout << "Proceso 0: Enviando bola " << ball << " al proceso 1"
                << std::endl;
      MPI_Send(&ball, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
      // Espera el tiempo especificado antes de recibir
      std::this_thread::sleep_for(std::chrono::milliseconds(delay));
      MPI_Recv(&ball, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      std::cout << "Proceso 0: Recibiendo bola " << ball << " del proceso 1"
                << std::endl;
    } else if (world_rank == 1) {
      // Proceso 1 recibe la bola del proceso 0
      MPI_Recv(&ball, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      std::cout << "Proceso 1: Recibiendo bola " << ball << " del proceso 0"
                << std::endl;
      ball++;  // Incrementa el conteo de la bola
      // Espera el tiempo especificado antes de enviar
      std::this_thread::sleep_for(std::chrono::milliseconds(delay));
      MPI_Send(&ball, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
      std::cout << "Proceso 1: Enviando bola " << ball << " al proceso 0"
                << std::endl;
    }
  }

  MPI_Finalize();
  return 0;
}
