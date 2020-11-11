#ifndef __DATAPRODUCER_H_
#define __DATAPRODUCER_H_

// standard imports
#include <thread>
#include <chrono>
#include <iostream>
// 3rd party imports

using namespace std;
using namespace std::chrono_literals;

class DataConsumer {

  // attributes
  string m_filePath = "car_output_data.csv";
  std::chrono::duration<double> m_periodicity;

  public:
  DataConsumer(string filePath);
  void read_data();
  void get_data();
  int ms_2_us(int timeMS);
  void run();

};

#endif // __DATAPRODUCER_H_
