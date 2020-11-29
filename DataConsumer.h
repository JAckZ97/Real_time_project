#ifndef __DATACONSUMER_H_
#define __DATACONSUMER_H_

// standard imports
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
  int m_count;

  public:
  DataConsumer(SharedMemory *sharedMemory, int period);
  double* read_data();
  void print_data(double *data);
  int ms_2_us(int timeMS);
  void run();

};

#endif // __DATACONSUMER_H_