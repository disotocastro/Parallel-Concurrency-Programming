/// @copyright 2024 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Juan Diego Soto Castro <juan.sotocastro@ucr.ac.cr>

#ifndef ASSEMBLERTEST_H
#define ASSEMBLERTEST_H

#include "Assembler.hpp"
#include "Consumer.hpp"
#include "NetworkMessage.hpp"

/**
 * @brief A AssemblerTest class example
 */

class AssemblerTest : public Assembler<NetworkMessage, NetworkMessage> {
  DISABLE_COPY(AssemblerTest);

 protected:
  /// Delay of Assembler to consume a package, negative for max random
  int consumerDelay = 0;
  /// Number of messages received
  size_t receivedMessages = 0;

 public:
  /// Constructor
  //explicit AssemblerTest(int consumerDelay);
  /// Consume the messages in its own execution thread
  int run() override;
  /// Override this method to process any data extracted from the queue
  void consume(NetworkMessage data) override;
};

#endif  // ASSEMBLERTEST_H