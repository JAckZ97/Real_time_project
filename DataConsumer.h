#ifndef __DATACONSUMER_H_
#define __DATACONSUMER_H_

// standard imports
#include <thread>
#include <iostream>
#include <unistd.h>
#include <iomanip>
#include "SharedMemory.h"
// 3rd party imports

using namespace std;

class DataConsumer {

  // attributes
  int m_period; // ms
  SharedMemory *m_sharedMemory;

  public:
  DataConsumer(SharedMemory *sharedMemory, int period);
  array<double, 8> read_data();
  void print_data(array<double, 8> data);
  int ms_2_us(int timeMS);
  void run();

};

#endif // __DATACONSUMER_H_