#include "sharedData.hpp"

// Se encarga de manejar el control de concurrencia para 
// que los productores se repartan la carga de creación de mensajes de red
int SharedData::getIndex() {
  int index_producers = 0;

  mutex.lock();
    index_producers = this->Count;
    if (this->Count > 0) {
      --this->Count;
    }
  mutex.unlock();
  return index_producers;
}
