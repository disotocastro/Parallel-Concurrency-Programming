#ifndef HELLO_IW_SHR_HPP
#define HELLO_IW_SHR_HPP

#include <cstdint>
#include <chrono>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <thread>
#include <vector>
#include <mutex>
#include <exception>

typedef struct shared_data {
    uint64_t thread_count;
} shared_data_t;

typedef struct private_data {
    uint64_t thread_number;
    shared_data_t* shared_data;
} private_data_t;

void* greet(void* data);

int create_threads(shared_data_t* shared_data);

#endif // HELLO_IW_SHR_HPP
