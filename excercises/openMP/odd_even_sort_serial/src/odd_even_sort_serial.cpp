#include <iostream>
#include <vector>
#include <cstdlib>  // Para rand() y srand()
#include <ctime>    // Para time()
#include <algorithm> // Para std::swap

void serial_odd_even_sort(size_t n, std::vector<double> &arr) {
  for (size_t phase = 0; phase < n; ++phase) {
    if (phase % 2 == 0) {
      for (size_t i = 1; i < n; i += 2) {
          if (arr[i - 1] > arr[i]) {
              std::swap(arr[i - 1], arr[i]);
          }
      }
    } else {
      for (size_t i = 1; i < n - 1; i += 2) {
          if (arr[i] > arr[i + 1]) {
              std::swap(arr[i], arr[i + 1]);
          }
      }
    }
  }
}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <size of array>" << std::endl;
    return 1;
  }
  size_t n = std::stoi(argv[1]);
  std::vector<double> arr(n);
  // Inicializar el arreglo con valores aleatorios
  std::srand(static_cast<unsigned>(std::time(0)));
  for (size_t i = 0; i < n; ++i) {
      arr[i] = static_cast<double>(std::rand()) / RAND_MAX;
  }
  // Imprimir el arreglo antes de ordenarlo
  std::cout << "Array before sorting:" << std::endl;
  for (size_t i = 0; i < n; ++i) {
      std::cout << arr[i] << " ";
  }
  std::cout << std::endl;
  // Ordenar el arreglo utilizando serial_odd_even_sort
  serial_odd_even_sort(n, arr);
  // Imprimir el arreglo después de ordenarlo
  std::cout << "Array after sorting:" << std::endl;
  for (size_t i = 0; i < n; ++i) {
      std::cout << arr[i] << " ";
  }
  std::cout << std::endl;

  return 0;
}
