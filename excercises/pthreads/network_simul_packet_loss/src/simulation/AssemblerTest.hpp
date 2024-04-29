/// @copyright 2024 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Juan Diego Soto Castro <juan.sotocastro@ucr.ac.cr>

#ifndef ASSEMBLERTEST_H
#define ASSEMBLERTEST_H

#include "Assembler.hpp"
#include "Consumer.hpp"
#include "Queue.hpp"
#include "NetworkMessage.hpp"

/**
 * @brief A AssemblerTest class example
 * 
 * Por cada paquete que este hilo ensamblador recibe, se genera un número 
 * flotante pseudoaleatorio entre 0 y 100. 
 * Si este número generado es menor que la probabilidad de pérdida de paquetes, 
 * el hilo descarta el paquete, de lo contrario, 
 * modifica al azar el destino del paquete, y lo pone de regreso en la cola 
 * entre el productor y el repartidor.
 * 
 */

class AssemblerTest : public Assembler<NetworkMessage, NetworkMessage> {
  DISABLE_COPY(AssemblerTest);
 protected:
  /// Paquete que este hilo ensamblador recibe
  size_t consumerCount = 0;
  /// Number of messages received
  size_t receivedMessages = 0;
  // Perdida de paquetes
  float packetLoss = 0.0;

 public:
  /// Constructor
  explicit AssemblerTest(float packetLoss, size_t consumerCount) : Assembler(){
    this->packetLoss = packetLoss;
    this->packetLoss = consumerCount;
  }

  int run() override;
  void consume(NetworkMessage data) override;
};

#endif  // ASSEMBLERTEST_H