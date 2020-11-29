#include "DataConsumer.h"

DataConsumer::DataConsumer(SharedMemory *sharedMemory, int period){
  // init variables
  m_period = period;
  m_sharedMemory =  sharedMemory;

  m_count = 0;
}

double* DataConsumer::read_data() {
    return m_sharedMemory->access(1, 0, 0);
}

void DataConsumer::print_data (double *data) {
    // quick hack to simulate a "clear terminal" so that next set data can be displayed, without appending to the terminal
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);

    // ascii art car
    cout<<"   ___   _   ___  " << endl;
    cout<<"  / __| /_\\ | _ \\ " << endl;
    cout<<" | (__ / _ \\|   / " << endl;
    cout<<"  \\___/_/ \\_\\_|_\\ " << endl << endl;
    
    // print car data
    cout << left;
    cout <<  setw(40) << "fuel consumption" << data[0] << endl;
    cout <<  setw(40) << "engine speed" << data[1] << endl;
    cout <<  setw(40) << "engine coolant temperature" << data[2] << endl;
    cout <<  setw(40) << "current gear" << data[3] << endl;
    cout <<  setw(40) << "transmission oil temperature" << data[4] << endl;
    cout <<  setw(40) << "vehicule speed" << data[5] << endl;
    cout <<  setw(40) << "acceleration speed longitudinal" << data[6] << endl;
    cout <<  setw(40) << "indication of break switch" << data[7] << endl;

    // we put this count to show how the dataconsumer is going at 10ms
    m_count = m_count + 1;
    cout <<  setw(40) << "count" << m_count << endl;

    // cout <<  "\r" << data[0] << " - " << data[1] << " - " << data[2] << " - " << data[3] << " - " << data[4] << " - " << data[5] << " - " << data[6] << " - " << data[7] << flush;
}

int DataConsumer::ms_2_us(int timeMS) {
    return timeMS * 1000;
}

void DataConsumer::run() {
    while(true){
        // array<double, 8> data = read_data();
        print_data(read_data());

        // delay
        usleep(ms_2_us(m_period));
    }
}