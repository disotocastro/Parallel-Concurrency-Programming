#include <mpi.h>
#include <unistd.h>

#include <cstdlib>
#include <iostream>
#include <stdexcept>

#define fail(msg) throw std::runtime_error(msg)

void simulate_relay_race(int argc, char* argv[], int process_number,
                         int process_count);
void run_stage1(int stage1_delay, int process_number, int team_count);
void run_stage2(int stage2_delay, int process_number, int team_count);

int main(int argc, char* argv[]) {
  int error = EXIT_SUCCESS;
  if (MPI_Init(&argc, &argv) == MPI_SUCCESS) {
    try {
      int process_number = -1;
      MPI_Comm_rank(MPI_COMM_WORLD, &process_number);

      int process_count = -1;
      MPI_Comm_size(MPI_COMM_WORLD, &process_count);

      char process_hostname[MPI_MAX_PROCESSOR_NAME] = {'\0'};
      int hostname_length = -1;
      MPI_Get_processor_name(process_hostname, &hostname_length);

      simulate_relay_race(argc, argv, process_number, process_count);
    } catch (const std::runtime_error& exception) {
      std::cout << exception.what() << std::endl;
      error = EXIT_FAILURE;
    }
    MPI_Finalize();
  } else {
    std::cerr << "error: could not init MPI" << std::endl;
    error = EXIT_FAILURE;
  }
  return error;
}

void simulate_relay_race(int argc, char* argv[], int process_number,
                         int process_count) {
  if (argc == 3) {
    if (process_count >= 2) {
      const int team_count = process_count / 2;
      const int stage1_delay = atoi(argv[1]);
      const int stage2_delay = atoi(argv[2]);

      run_stage1(stage1_delay, process_number, team_count);
      run_stage2(stage2_delay, process_number, team_count);
    } else {
      fail("error: two or more of processes required");
    }
  } else {
    fail("usage: relay_race_dist stage1_delay stage2_delay");
  }
}

void run_stage1(int stage1_delay, int process_number, int team_count) {
  usleep(1000 * stage1_delay);
}

void run_stage2(int stage2_delay, int process_number, int team_count) {
  usleep(1000 * stage2_delay);
}