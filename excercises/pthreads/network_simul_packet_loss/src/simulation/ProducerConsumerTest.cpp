/// @copyright 2020 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Jeisson Hidalgo-Céspedes <jeisson.hidalgo@ucr.ac.cr>

#include <cstdlib>
#include <iostream>

#include "ProducerConsumerTest.hpp"
#include "ConsumerTest.hpp"
#include "DispatcherTest.hpp"
#include "ProducerTest.hpp"

const char* const usage =
  "Usage: prodcons packages consumers prod_delay disp_delay cons_delay packet_loss\n"
  "\n"
  "  packages    number of packages to be produced\n"
  "  consumers   number of consumer threads\n"
  "  prod_delay  delay of producer to create a package\n"
  "  disp_delay  delay of dispatcher to dispatch a package\n"
  "  cons_delay  delay of consumer to consume a package\n"
  "  packet_loss percentage of probability of losing a package [0 ... 100]\n"
  "\n"
  "Delays are in milliseconds, negative values represent maximums for random delays\n";

ProducerConsumerTest::~ProducerConsumerTest() {
  delete this->producer;
  delete this->dispatcher;
  delete this->assembler;
  for ( ConsumerTest* consumer : this->consumers )
    delete consumer;
}

int ProducerConsumerTest::start(int argc, char* argv[]) {
  // Parse arguments and store values in object members
  if ( int error = this->analyzeArguments(argc, argv) ) {
    return error;
  }

  // Create objects for the simulation
  this->producer = new ProducerTest(this->packageCount, this->productorDelay
    , this->consumerCount);
  this->dispatcher = new DispatcherTest(this->dispatcherDelay);
  this->assembler = new AssemblerTest(this->packetLoss, this->consumerCount,
    this->consumerDelay, this->consumerCount - 1);
  this->dispatcher->createOwnQueue();

  this->consumers.resize(this->consumerCount);
  for ( size_t index = 0; index < this->consumerCount; ++index ) {
    this->consumers[index] = new ConsumerTest(this->consumerDelay);
    assert(this->consumers[index]);
    this->consumers[index]->createOwnQueue();
  }

  // Communicate simulation objects
  // Producer push network messages to the dispatcher queue
  this->producer->setProducingQueue(this->dispatcher->getConsumingQueue());
  // Dispatcher delivers to each consumer, and they should be registered
  for ( size_t index = 0; index < this->consumerCount; ++index ) {
    this->dispatcher->registerRedirect(index + 1
      , this->consumers[index]->getConsumingQueue());
  }

  // Communicate assembler with dispatcher
  this->assembler->createOwnQueue();
  this->dispatcher->registerRedirect(this->consumerCount + 1
    , this->assembler->getConsumingQueue());

  // Start the simulation
  this->producer->startThread();
  this->dispatcher->startThread();
  for ( size_t index = 0; index < this->consumerCount; ++index ) {
    this->consumers[index]->startThread();
  }
  this->assembler->startThread();

  // Wait for objets to finish the simulation
  this->producer->waitToFinish();
  this->dispatcher->waitToFinish();
  for ( size_t index = 0; index < this->consumerCount; ++index ) {
    this->consumers[index]->waitToFinish();
  }
  this->assembler->waitToFinish();

  // Simulation finished
  return EXIT_SUCCESS;
}

int ProducerConsumerTest::analyzeArguments(int argc, char* argv[]) {
  // 6 + 1 arguments are mandatory
  if ( argc != 7 ) {
    std::cout << usage;
    return EXIT_FAILURE;
  }

  int index = 1;
  this->packageCount = std::strtoull(argv[index++], nullptr, 10); 
  this->consumerCount = std::strtoull(argv[index++], nullptr, 10);
  this->productorDelay = std::atoi(argv[index++]);
  this->dispatcherDelay = std::atoi(argv[index++]);
  this->consumerDelay = std::atoi(argv[index++]);
  this->packetLoss = std::atoi(argv[index++]);

  // Validate that given arguments are fine
  // For example, you could check if delays are non-negative, and packet loss is in the range [0, 100]

  return EXIT_SUCCESS;
}
