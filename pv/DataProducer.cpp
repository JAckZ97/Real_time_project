#include "DataProducer.hpp"

DataProducer::DataProducer(string sensorDataType, std::chrono::duration<double> periodicity, float *extData) {
    // init variables
    m_sensorDataType = sensorDataType;
    m_periodicity = periodicity;

    m_data = 100;

    m_extData = extData;

    // setup the csv reader
    m_csvReader = new io::CSVReader<1>(m_csvFilePath);
    m_csvReader->read_header(io::ignore_extra_column, m_sensorDataType);
}

void DataProducer::print_data() {
    cout << left;
    cout <<  setw(20) << m_sensorDataType << to_string(m_data) << endl;
}

int DataProducer::ms_2_us(int timeMS) {
    return timeMS * 1000;
}

void DataProducer::run() {

    int rowCount = 1; // we start at 1 because for better reference with the csv file, which the row starts with 1 label.

    auto startTime = chrono::system_clock::now();
    auto startTimePeriodicity = chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecondsDataChange;
    std::chrono::duration<double> elapsedPeriodicity;
    bool csvEnd = false;
    bool csvReaderFlag;

    // read in the first data
    csvReaderFlag = m_csvReader->read_row(m_data); // here we read the csv data into m_data , csvReaderFlag will return false if it is the end of the csv file

    while(!csvEnd){
      elapsedSecondsDataChange = chrono::system_clock::now() - startTime;
      elapsedPeriodicity = chrono::system_clock::now() - startTimePeriodicity;

      if(elapsedSecondsDataChange >= 1s){
        startTime = chrono::system_clock::now();

        csvReaderFlag = m_csvReader->read_row(m_data); // here we read the csv data into m_data , csvReaderFlag will return false if it is the end of the csv file
        rowCount++;
        if(!csvReaderFlag){
          csvEnd = true;
          cout << "reached the end" << endl;
        }
      }

      if(elapsedPeriodicity >= m_periodicity){
        startTimePeriodicity = chrono::system_clock::now();
        // this->print_data();
        *m_extData = m_data;
      }
    }
}
