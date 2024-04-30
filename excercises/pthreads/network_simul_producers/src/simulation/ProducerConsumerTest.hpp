/// @copyright 2020 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Jeisson Hidalgo-Céspedes <jeisson.hidalgo@ucr.ac.cr>

#ifndef PRODUCERCONSUMERTEST_HPP
#define PRODUCERCONSUMERTEST_HPP

#include <vector>

#include "common.hpp"
#include "sharedData.hpp"

// Forward declarations
class ConsumerTest;
class DispatcherTest;
class ProducerTest;

/**
 * @brief Controller class that simulates the message passing between
 * producer and cosumers through a dispatcher
 */
class ProducerConsumerTest {
  DISABLE_COPY(ProducerConsumerTest);

 private:
  /// Number of packages to be produced
  size_t packageCount = 0;
  /// Number of producers threads
  size_t producersCount = 0;
  /// Number of consumer threads
  size_t consumerCount = 0;
  /// Delay of producer to create a package, negative for max random
  int productorDelay = 0;
  /// Delay of dispatcher to dispatch a package, negative for max random
  int dispatcherDelay = 0;
  /// Delay of consumer to consume a package, negative for max random
  int consumerDelay = 0;

  /// Vector de productores
  std::vector<ProducerTest*> producers;
  /// Vector de consumidores
  std::vector<ConsumerTest*> consumers;

  DispatcherTest* dispatcher = nullptr;
  SharedData* producerSharedData = nullptr;

 public:
  /// Constructor
  ProducerConsumerTest() = default;
  /// Destructor
  ~ProducerConsumerTest();
  /// Start the simulation
  int start(int argc, char* argv[]);

 private:
  /// Analyze the command line arguments
  int analyzeArguments(int argc, char* argv[]);

  void createProducers();
};

#endif  // PRODUCERCONSUMERTEST_HPP
