/// @copyright 2024 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Juan Diego Soto Castro <juan.sotocastro@ucr.ac.cr>

#include "AssemblerTest.hpp"
#include "Log.hpp"
#include "Util.hpp"
#include "Queue.hpp"
#include <random>

int AssemblerTest::run() {
  // Start the forever loop to consume all the messages that arrive
  this->consumeForever();
  return EXIT_SUCCESS;
}

/**
 * 
 * Por cada paquete que este hilo ensamblador recibe, se genera un número 
 * flotante pseudoaleatorio entre 0 y 100. 
 * Si este número generado es menor que la probabilidad de pérdida de paquetes, 
 * el hilo descarta el paquete, de lo contrario, 
 * modifica al azar el destino del paquete, y lo pone de regreso en la cola 
 * entre el productor y el repartidor.
 * 
 */

// Por cada paquete que este hilo ensamblador recibe, se genera un número 
void AssemblerTest::consume(NetworkMessage data) {
  (void)data;
  ++this->receivedMessages;

  // flotante pseudoaleatorio entre 0 y 100.
  double random_number = 1 + (rand() % 100);

 // Si este número generado es mayor que la probabilidad de pérdida de paquetes, 
  if (random_number < this->packetLoss) {
    // modifica al azar el destino del paquete, y lo pone de regreso en la cola
    // entre el productor y el repartidor.
    Util::sleepFor(this->consumerDelay);
    produce(modifyPacket());
    std::cout << "Mensaje perdido... prueba" << std::endl;
  }
  
}

// struct NetworkMessage {
//  public:
//   /// The target consumer
//   uint16_t target = 0;
//   /// The source producer
//   uint16_t source = 0;


// modifica al azar el destino del paquete
NetworkMessage AssemblerTest::modifyPacket() {
  uint16_t source = this->packetID;
  uint16_t source_packet = this->packetID;

  /**
   * Mientras que el ID del paquete y el source sean iguales:
   *  Se genera un paquete random
   * 
   * Despues, se envia un paquete
   * 
  */
  while (source == packetID) {
    source_packet =  1 + (rand() % this->consumerCount);
  }

  uint16_t target = source_packet;

  return NetworkMessage(target, source);
}

//  lo pone de regreso en la cola entre el productor y el repartidor.
Queue<NetworkMessage>*  AssemblerTest::getQueue() {
  return this->consumingQueue;
}

