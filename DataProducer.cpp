#include "DataProducer.hpp"
#include "csv_reader.h"

DataProducer::DataProducer(string sensorDataType, int targetCollumn, std::chrono::duration<double> periodicity, double *extData) {
    // init variables
    m_sensorDataType = sensorDataType;
    m_periodicity = periodicity;

    m_data = 100;

    m_extData = extData;

    m_targetCollumn = targetCollumn;

    // setup the csv reader
    // m_csvReader = new io::CSVReader<1>(m_csvFilePath);
    // m_csvReader->read_header(io::ignore_extra_column, m_sensorDataType);

    m_maxRowNumber = csv_read::maxRowCSV(m_csvFilePath);
}

void DataProducer::print_data() {
    cout << left;
    cout <<  setw(20) << m_sensorDataType << to_string(m_data) << endl;
}

int DataProducer::ms_2_us(int timeMS) {
    return timeMS * 1000;
}

void DataProducer::run() {

    int rowCount = 2; // we start at 1 because for better reference with the csv file, which the row starts with 1 label.

    auto startTime = chrono::system_clock::now();
    auto startTimePeriodicity = chrono::system_clock::now();
    std::chrono::duration<double> elapsedSecondsDataChange;
    std::chrono::duration<double> elapsedPeriodicity;
    bool csvEnd = false;
    bool csvReaderFlag;


    // read in the first data
    // csvReaderFlag = m_csvReader->read_row(m_data); // here we read the csv data into m_data , csvReaderFlag will return false if it is the end of the csv file

    // while not done reading the csv file
    while(!csvEnd){
      
      elapsedSecondsDataChange = chrono::system_clock::now() - startTime;
      elapsedPeriodicity = chrono::system_clock::now() - startTimePeriodicity;

      // each second, we go to the next row to read the data (since each new row is 1s passed since data read from sensor)
      if(elapsedSecondsDataChange >= 1s){
        startTime = chrono::system_clock::now();

        // csvReaderFlag = m_csvReader->read_row(m_data); // here we read the csv data into m_data , csvReaderFlag will return false if it is the end of the csv file
        rowCount++;

        // FIXME : implement -> if reach the end -> exit
        if(rowCount > m_maxRowNumber){
          csvEnd = true;
          // cout << "reached the end" << rowCount << endl;
        }
      }

      // each period, we read the data
      if(elapsedPeriodicity >= m_periodicity){
        startTimePeriodicity = chrono::system_clock::now();
        
        // read data here
        m_data = csv_read::readCellCSV(m_csvFilePath, rowCount, m_targetCollumn, m_maxRowNumber);

        // write data in shared memory
        
      }
    }
}
