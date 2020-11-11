#include "DataConsumer.hpp"

DataConsumer::DataConsumer(string filePath){
  // init variables
  m_filePath = filePath;
}

void DataConsumer::get_data() {
}

void DataConsumer::read_data() {
    }

int DataConsumer::ms_2_us(int timeMS) {
    return timeMS * 1000;
}

void DataConsumer::run() {
}
