#ifndef __DATAPRODUCER_H_
#define __DATAPRODUCER_H_

// standard imports
#include <iostream>
#include <vector> // FIXME
#include <string> // FIXME
#include <unistd.h>
#include <time.h> // FIXME
#include <iomanip>
// 3rd party imports
#include "SharedMemory.h"

using namespace std;

class DataProducer {

  // attributes
  string m_sensorDataType;
  double m_data;
  double m_periodicity; // seconds
  string m_csvFilePath = "car_data.csv";
  // io::CSVReader<1>* m_csvReader;
  int m_targetCollumn;
  int m_maxRowNumber;

  SharedMemory *m_sharedMemory;
  int m_dataIndex; // where it saves in the sharedMemory

  public:
  DataProducer(string sensorDataType, int targetCollumn, double periodicity, SharedMemory *sharedMemory, int dataIndex);
  int read_data(int row);
  void print_data();
  void run();
  int ms_2_us(int timeMS);

};

#endif // __DATAPRODUCER_H_
