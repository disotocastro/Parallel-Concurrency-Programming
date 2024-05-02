/// @copyright 2020 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Juan Diego Soto Castro <juan.sotocastro@ucr.ac.cr>

#ifndef DEMUX_HPP
#define DEMUX_HPP

#include <exception>
#include <map>

#include "Producer.hpp"

/**
 * @brief A dispatcher is both, a consumer of its own queue, and a producer
 * for many queues. For each data that is pushed to its queue, the dispatcher
 * distributes the data to another queues, using key-values
 */
template <typename KeyType, typename DataType>




class Demux : public Producer<DataType> {
  /// Objects of this class cannot be copied
  DISABLE_COPY(Demux);

 protected:

  Queue<DataType>*& toQueue = Producer<DataType>::produceQueue;

  /// Crear su propia cola
  std::map<KeyType, Queue<DataType>*> toQueues;

 public:
  /// Constructor
  explicit Demux(Queue<DataType>* produceQueue = nullptr
    , const DataType& stopCondition = DataType()
    , bool createOwnQueue = false)
    : CProducer<DataType>(produceQueue, stopCondition) {
  }

  /// Destructor
  virtual ~Demux() {
  }

  // Crea una nueva cola para si mismo
  void createOwnQueue() {
    assert(this->produceQueue == nullptr);
    this->produceQueue = new Queue<DataType>();
  }

  /// Register a map. When the data to be consumed has this key, it will be
  /// redirected to the the given queue
  inline void registerRedirect(const KeyType& key, Queue<DataType>* toQueue) {
    this->toQueues[key] = toQueue;
  }

  /// Override this method to process any data extracted from the queue
  void produce(DataType data) override {
    const KeyType& key = this->extractKey(data);
    const auto& itr = this->toQueues.find(key);
    if ( itr == this->toQueues.end() ) {
      throw std::runtime_error("demux: queue's key not found");
    }
    if(!(itr->second->getConsumingQueue.empty())){
      toQueue.push(itr->second->pop(data));
    } else {
      throw std::runtime_error("demux: could not consume queue");
    }
  }

  /// Override this method to extract the key from a data stored in fromQueue
  virtual KeyType extractKey(const DataType& data) const = 0;
};

#endif  // DEMUX_HPP