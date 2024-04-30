#ifndef SHAREDDATA_HPP
#define SHAREDDATA_HPP

#include <mutex>

struct SharedData {
    std::mutex mutex;

    SharedData(int count): Count(count) {}
    ~SharedData() {}
    
    int Count;
    int getIndex();
    
};

#endif // SHAREDDATA_HPP
