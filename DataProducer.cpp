#include "DataProducer.h"
#include "csv_reader.h"

DataProducer::DataProducer(string sensorDataType, int targetCollumn, double periodicity, SharedMemory *sharedMemory, int dataIndex) {
    // init variables
    m_sensorDataType = sensorDataType;
    m_periodicity = periodicity;

    m_data = 100;

    m_sharedMemory = sharedMemory;

    m_targetCollumn = targetCollumn;

    // setup the csv reader
    // m_csvReader = new io::CSVReader<1>(m_csvFilePath);
    // m_csvReader->read_header(io::ignore_extra_column, m_sensorDataType);

    m_maxRowNumber = csv_read::maxRowCSV(m_csvFilePath);

    m_sharedMemory = sharedMemory;
    m_dataIndex = dataIndex;
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

    time_t startTime;
    time(&startTime); // get the current time

    time_t startTimePeriodicity;
    time(&startTimePeriodicity); // get the current time

    // auto startTime = chrono::system_clock::now();
    // auto startTimePeriodicity = chrono::system_clock::now();

    double elapsedSecondsDataChange;
    double elapsedPeriodicity;

    bool csvEnd = false;
    bool csvReaderFlag;

    // read in the first data
    // csvReaderFlag = m_csvReader->read_row(m_data); // here we read the csv data into m_data , csvReaderFlag will return false if it is the end of the csv file

    // while not done reading the csv file
    while(!csvEnd){

      time_t currentTime;
      time(&currentTime); // get the current time
      
      elapsedSecondsDataChange = difftime(currentTime, startTime);
      elapsedPeriodicity = difftime(currentTime, startTimePeriodicity);

      // elapsedSecondsDataChange = chrono::system_clock::now() - startTime;
      // elapsedPeriodicity = chrono::system_clock::now() - startTimePeriodicity;

      // each second, we go to the next row to read the data (since each new row is 1s passed since data read from sensor)
      if(elapsedSecondsDataChange >= 1){
        // startTime = chrono::system_clock::now();
        time(&startTime); // get the current time

        // csvReaderFlag = m_csvReader->read_row(m_data); // here we read the csv data into m_data , csvReaderFlag will return false if it is the end of the csv file
        rowCount++;

        // FIXME : implement -> if reach the end -> exit
        if(rowCount > m_maxRowNumber){
          csvEnd = true;
          // cout << "reached the end" << rowCount << endl;
        }
      }

      // each period, we read the data
      // NOTE : m_periodicity should be converted to seconds, since time.h time_t takes the current time in seconds
      if(elapsedPeriodicity >= m_periodicity){
        // startTimePeriodicity = chrono::system_clock::now();
        time(&startTimePeriodicity);
        
        // read data here
        m_data = csv_read::readCellCSV(m_csvFilePath, rowCount, m_targetCollumn, m_maxRowNumber);

        // write data in shared memory
        m_sharedMemory->access(0, m_dataIndex, m_data);

      }
    }
}
