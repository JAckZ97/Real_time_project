#include "DataConsumer.h"


DataConsumer::DataConsumer(SharedMemory *sharedMemory, int period){
  // init variables
  m_period = period;
  m_sharedMemory =  sharedMemory;
}

array<double, 8> DataConsumer::read_data() {
    return m_sharedMemory->access(1, 0, 0);
}

void DataConsumer::print_data (array<double, 8> data) {
    for (int i =0; i < data.size(); i++){
      cout << data[i] << endl;
    }
}

int DataConsumer::ms_2_us(int timeMS) {
    return timeMS * 1000;
}

void DataConsumer::run() {
    while(true){
        array<double, 8> data = read_data();
        print_data(data);

        // delay
        usleep(ms_2_us(m_period));
    }
}