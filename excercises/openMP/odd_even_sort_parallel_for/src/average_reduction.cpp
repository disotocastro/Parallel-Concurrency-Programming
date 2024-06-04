#include <omp.h>
#include <iostream>
#include <vector>
#include <cmath> // Para sqrt()

int main(int argc, char* argv[]) {
  int thread_count = omp_get_max_threads();
  if (argc >= 2) {
    thread_count = atoi(argv[1]);
  }

  std::vector<double> values;

  double value = 0.0;
  while (std::cin >> value) {
    values.push_back(value);
  }

  double sum = 0.0;
  double sum_squared_diff = 0.0; 
  // Variable compartida para almacenar la suma de los cuadrados de las diferencias
  double min_value = values[0];
  double max_value = values[0];

  #pragma omp parallel for num_threads(thread_count) schedule(runtime) \
    default(none) shared(values, min_value, max_value, sum_squared_diff) reduction(+:sum)
  for (size_t index = 0; index < values.size(); ++index) {
    sum += values[index];

    #pragma omp critical
    {
      if (values[index] < min_value) {
        min_value = values[index];
      }

      if (values[index] > max_value) {
        max_value = values[index];
      }

      // Calcula la suma de los cuadrados de las diferencias entre cada valor y la media
      double diff = values[index] - (sum / values.size());
      sum_squared_diff += diff * diff;
    }
  }

  const double average = values.size() ? sum / values.size() : 0.0;
  const double variance = values.size() ? sum_squared_diff / values.size() : 0.0; // Varianza
  const double standard_deviation = sqrt(variance); // Desviación estándar

  std::cout << "Average Value: " << average << std::endl;
  std::cout << "Max Value: " << max_value << std::endl;
  std::cout << "Min Value: " << min_value << std::endl;
  std::cout << "Standard Deviation: " << standard_deviation << std::endl;

  return 0;
}
