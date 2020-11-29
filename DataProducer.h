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
#include "CSVRead.h"

using namespace std;

class DataProducer {

  // attributes
  string m_sensorDataType;
  double m_data;
  double m_periodicity; // seconds
  const char* m_csvFilePath;
  // io::CSVReader<1>* m_csvReader;
  int m_targetCollumn;
  int m_maxRowNumber;

  SharedMemory *m_sharedMemory;
  int m_dataIndex; // where it saves in the sharedMemory

  CSVRead *m_csvRead;

  public:
  DataProducer(string sensorDataType, int targetCollumn, double periodicity, SharedMemory *sharedMemory, int dataIndex, CSVRead *csvRead);
  int read_data(int row);
  void print_data();
  void run();
  int ms_2_us(int timeMS);
  double get_current_time();

};

#endif // __DATAPRODUCER_H_
