#include <mpi.h>

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <thread>

int main(int argc, char* argv[]) {
  MPI_Init(&argc, &argv);

  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  if (world_size != 2) {
    if (world_size == 1) {
      std::cerr << "Se necesitan exactamente dos procesos para jugar."
                << std::endl;
    } else {
      std::cerr << "Este programa solo soporta dos procesos." << std::endl;
    }
    MPI_Abort(MPI_COMM_WORLD, 1);
  }

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  if (argc != 4) {
    if (world_rank == 0) {
      std::cerr << "Uso: mpiexec -n 2 ping_pong <marcador_victoria> "
                   "<probabilidad_jugador1> <probabilidad_jugador2>"
                << std::endl;
    }
    MPI_Finalize();
    return 1;
  }

  int marcador_victoria = std::stoi(argv[1]);
  double probabilidad_jugador1 = std::stod(argv[2]);
  double probabilidad_jugador2 = std::stod(argv[3]);

  if (marcador_victoria <= 0 || probabilidad_jugador1 < 0 ||
      probabilidad_jugador2 < 0 || probabilidad_jugador1 > 100 ||
      probabilidad_jugador2 > 100) {
    if (world_rank == 0) {
      std::cerr
          << "Los argumentos deben ser: <marcador_victoria> (entero positivo "
             "mayor que cero), <probabilidad_jugador1> (double entre 0 y 100), "
             "<probabilidad_jugador2> (double entre 0 y 100)."
          << std::endl;
    }
    MPI_Finalize();
    return 1;
  }

  int score[2] = {0, 0};
  int round = 1;
  int services[2] = {0, 0};

  std::srand(
      std::time(nullptr) +
      world_rank);  // Utiliza el rango del proceso para la semilla aleatoria

  while (score[0] < marcador_victoria && score[1] < marcador_victoria) {
    int winner = -1;

    if (world_rank == 0) {
      double random_number = (double)std::rand() / RAND_MAX * 100.0;
      if (random_number < probabilidad_jugador1) {
        services[0]++;
        winner = 0;
        MPI_Send(&winner, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
      } else {
        winner = 1;
        MPI_Send(&winner, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
      }
      MPI_Recv(&winner, 1, MPI_INT, 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    } else if (world_rank == 1) {
      double random_number = (double)std::rand() / RAND_MAX * 100.0;
      if (random_number < probabilidad_jugador2) {
        services[1]++;
        winner = 1;
        MPI_Recv(&winner, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      } else {
        winner = 0;
        MPI_Recv(&winner, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      }
      MPI_Send(&winner, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    if (winner != -1) {
      score[winner]++;
      if (world_rank == 0) {
        std::cout << round << ": " << services[0] + services[1] << " "
                  << winner + 1 << std::endl;
        round++;
      }
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(10));
  }

  if (world_rank == 0) {
    std::cout << score[0] << " wins " << score[1] << " to " << score[0]
              << std::endl;
  }

  MPI_Finalize();
  return 0;
}
