#include "DataProducer.h"
#include "csv_reader.h"

DataProducer::DataProducer(string sensorDataType, int targetCollumn, double periodicity, SharedMemory *sharedMemory, int dataIndex) {
    // init variables
    m_sensorDataType = sensorDataType;
    m_periodicity = periodicity;

    m_data = 100;

    m_sharedMemory = sharedMemory;

    m_targetCollumn = targetCollumn;

    m_csvFilePath = "car_data.csv";

    m_maxRowNumber = csv_read::maxRowCSV(m_csvFilePath);
    cout << "max row :" << m_maxRowNumber << endl;

    m_sharedMemory = sharedMemory;
    m_dataIndex = dataIndex;
}

int DataProducer::ms_2_us(int timeMS) {
    return timeMS * 1000;
}

double DataProducer::get_current_time(){
    // http://www.qnx.com/developers/docs/6.5.0/index.jsp?topic=%2Fcom.qnx.doc.neutrino_lib_ref%2Fc%2Fclock_gettime.html
    // http://www.qnx.com/developers/docs/6.5.0/index.jsp?topic=%2Fcom.qnx.doc.neutrino_lib_ref%2Ft%2Ftimespec.html
    // struct timeval time_now{};
    // gettimeofday(&time_now, nullptr);
    // time_t msecs_time = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
    // return msecs_time;

    struct timespec time_now{};
    clock_gettime(CLOCK_REALTIME, &time_now);
    time_t msecs_time = (time_now.tv_sec * 1000) + (time_now.tv_nsec / 1000000);
    return msecs_time;
}

void DataProducer::run() {

    int rowCount = 2; // we start at 2 since row=1 is headers of the csv file

    double startTime = this->get_current_time();
    double startTimePeriodicity = this->get_current_time();
    double currentTime;

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
      currentTime = this->get_current_time();
      
      elapsedSecondsDataChange = currentTime - startTime;
      elapsedPeriodicity = currentTime - startTimePeriodicity;

      // elapsedSecondsDataChange = chrono::system_clock::now() - startTime;
      // elapsedPeriodicity = chrono::system_clock::now() - startTimePeriodicity;

      // each second, we go to the next row to read the data (since each new row is 1s passed since data read from sensor)
      if(elapsedSecondsDataChange >= 1000){ // 1000ms = 1s
        // startTime = chrono::system_clock::now();
        startTime = this->get_current_time();

        // csvReaderFlag = m_csvReader->read_row(m_data); // here we read the csv data into m_data , csvReaderFlag will return false if it is the end of the csv file
        rowCount++;

        // FIXME : implement -> if reach the end -> exit
        if(rowCount >= m_maxRowNumber){
          csvEnd = true;
          // cout << "reached the end" << rowCount << endl;
        }
      }

      // each period, we read the data
      // NOTE : m_periodicity should be converted to seconds, since time.h time_t takes the current time in sec
      if(elapsedPeriodicity >= m_periodicity){
        // startTimePeriodicity = chrono::system_clock::now();
        startTimePeriodicity = this->get_current_time();
        
        // read data here
        m_data = csv_read::readCellCSV(m_csvFilePath, rowCount, m_targetCollumn);
        // cout << "data :" << m_data << endl;

        // write data in shared memory
        m_sharedMemory->access(0, m_dataIndex, m_data);
      }
    }
}
