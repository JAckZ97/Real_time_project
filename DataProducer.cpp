#include "DataProducer.h"
#include "csv_reader.h"

DataProducer::DataProducer(string sensorDataType, int targetCollumn, double periodicity, SharedMemory *sharedMemory, int dataIndex, CSVRead *csvRead) {
    // init variables
    m_sensorDataType = sensorDataType;
    m_periodicity = periodicity;

    m_data = 100;

    m_sharedMemory = sharedMemory;

    m_csvRead = csvRead;

    m_targetCollumn = targetCollumn;

    m_csvFilePath = "car_data.csv";

    m_maxRowNumber = csv_read::maxRowCSV(m_csvFilePath);

    m_sharedMemory = sharedMemory;
    m_dataIndex = dataIndex;
}

int DataProducer::ms_2_us(int timeMS) {
    return timeMS * 1000;
}

double DataProducer::get_current_time(){

    // we get the time in seconds since epoch and the amount of time nano from the seocnd that passed, to get better accuracy
    struct timespec time_now;
    clock_gettime(CLOCK_REALTIME, &time_now);
    time_t msecs_time = (time_now.tv_sec * 1000) + (time_now.tv_nsec / 1000000);
    return msecs_time;
}

void DataProducer::run() {

    int rowCount = 2; // we start at 2 since row=1 is headers of the csv file

    double startTime = this->get_current_time();
    double startTimePeriodicity = this->get_current_time();
    double currentTime;

    double elapsedSecondsDataChange;
    double elapsedPeriodicity;

    bool csvEnd = false;
    bool csvReaderFlag;

    // while not done reading the csv file
    while(!csvEnd){
      currentTime = this->get_current_time();
      
      elapsedSecondsDataChange = currentTime - startTime;
      elapsedPeriodicity = currentTime - startTimePeriodicity;

      // each second, we go to the next row to read the data (since each new row is 1s passed since data read from sensor)
      if(elapsedSecondsDataChange >= 1000){ // 1000ms = 1s
        // startTime = chrono::system_clock::now();
        startTime = this->get_current_time();

        // csvReaderFlag = m_csvReader->read_row(m_data); // here we read the csv data into m_data , csvReaderFlag will return false if it is the end of the csv file
        rowCount++;

        if(rowCount >= m_maxRowNumber){
          csvEnd = true;
        }
      }

      // each period, we read the data
      // NOTE : m_periodicity should be converted to seconds, since time.h time_t takes the current time in sec
      if(elapsedPeriodicity >= m_periodicity){
        // startTimePeriodicity = chrono::system_clock::now();
        startTimePeriodicity = this->get_current_time();
        
        // read data here
        m_data = m_csvRead->readCellCSV(m_csvFilePath, rowCount, m_targetCollumn);

        // write data in shared memory
        m_sharedMemory->access(0, m_dataIndex, m_data);
      }
    }
}
