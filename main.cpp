// standard imports
#include <iostream>
#include <string>
#include<stdio.h>
// user import
#include "DataProducer.h"
#include "DataConsumer.h"
#include <thread>

using namespace std;

/*
 * NOTE : 3rd party library used
 * https://github.com/ben-strasser/fast-cpp-csv-parser
 *
 * FIXME : modified the header for Engine_coolant_temperature since there is duplicate (ie modified top Engine_coolant_temparature1)
 *
 * FIXME : add the std where necessary for more clarity
 *
 * NOTE : to compile and run the code
 * $ c++ -pthread *.cpp -o main && ./main
*/

/*
- TODO : add csv_read end check in data producer thread
- TODO : csv_read -> reading the first row gives error (the header row)
- TODO : map the dataproducer threads to the correct collumn number 
- TODO : glue everything together
- TODO : maxCollumn for csv_reader
- TODO : write to jack's share memory
- TODO : how to end the whole script correctly

- TODO : better printout
- TODO : add the proper data csv
- TODO : add all the threads needed
*/

int main(int argc, char *argv[]) {

    cout << "Start program" << endl;

    // Init. common database
    SharedMemory sharedMem; // NOTE : instead of declaring SharedMemory *sharedMem and passing as sharedMem -> SharedMemory and passing as &sharedMem does not trigger mutex error

    // creating the data producer threads
    // FIXME : for now I add the pointer to the data array so that the data can be changed to simulate the common database
    // future version we should get rid of this input parameter
    DataProducer prod0("Fuel_consumption",0, 10ms, &sharedMem, 0);
    DataProducer prod1("Engine_speed", 12, 500ms, &sharedMem, 1);
    DataProducer prod2("Engine_coolant_temperature1", 17, 2s, &sharedMem, 2);
    DataProducer prod3("Current_gear", 33, 100ms, &sharedMem, 3);
    DataProducer prod4("Transmission_oil_temperature", 34, 5s, &sharedMem, 4); // FIXME
    DataProducer prod5("Vehicule_speed", 43, 100ms, &sharedMem, 5);
    DataProducer prod6("Acceleration_speed_longitudinal", 44, 150ms, &sharedMem, 6);
    DataProducer prod7("Indication_of_break_switch", 45, 100ms, &sharedMem, 7);
    // FIXME : csv collumn starts at 0

    std::thread tp(&DataProducer::run, prod0);
    std::thread tp1(&DataProducer::run, prod1);
    std::thread tp2(&DataProducer::run, prod2);
    std::thread tp3(&DataProducer::run, prod3);
    std::thread tp4(&DataProducer::run, prod4);
    std::thread tp5(&DataProducer::run, prod5);
    std::thread tp6(&DataProducer::run, prod6);
    std::thread tp7(&DataProducer::run, prod7);

    // creating the data consumer thread
    int periodMS = 10;
    DataConsumer cons(&sharedMem, periodMS);
    std::thread tc(&DataConsumer::run, cons);

    // wait for producer threads
    tp.join();
    tp1.join();
    tp2.join();
    tp3.join();
    tp4.join();
    tp5.join();
    tp6.join();
    tp7.join();

    // wait for consumer thread
    tc.join();

    return 0;
}
