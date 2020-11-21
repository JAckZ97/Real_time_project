// standard imports
#include <iostream>
#include <string>
#include<stdio.h>
// user import
#include "DataProducer.hpp"
#include <thread>

/*
 * NOTE : 3rd party library used
 * https://github.com/ben-strasser/fast-cpp-csv-parser
 *
 * FIXME : modified the header for Engine_coolant_temperature since there is duplicate (ie modified top Engine_coolant_temparature1)
 *
 * FIXME : add the std where necessary for more clarity
 *
 * NOTE : to run the code
 * $ c++ -pthread *.cpp -o main
 * $ ./main
*/

/*
- TODO : add csv_read end check in data producer thread
- TODO : csv_read -> reading the first row gives error (the header row)
- TODO : map the dataproducer threads to the correct collumn number 
- TODO : glue everything together
*/

using namespace std;

int main(int argc, char *argv[]) {

    cout << "Start program" << endl;

    // simulating the "common database"
    float data[3] = {0,0,0};
    float *p_data;
    p_data = data;

    // creating the data producer threads
    // FIXME : for now I add the pointer to the data array so that the data can be changed to simulate the common database
    // future version we should get rid of this input parameter
    DataProducer prod("Fuel_consumption",0, 10ms, (p_data + 0));
    DataProducer prod1("Engine_speed", 1, 500ms, (p_data + 1));
    DataProducer prod2("Engine_coolant_temperature1",2, 2s, (p_data + 2));
    // FIXME : NOT the current collumn numbers !

    std::thread obj(&DataProducer::run, prod);
    std::thread obj1(&DataProducer::run, prod1);
    std::thread obj2(&DataProducer::run, prod2);

    // showing what the common database has atm
    while(true){
        usleep(10000);
        // cout << "--------------" << endl;
        // cout << left;
        // cout <<  setw(40) << "fuel consumption" << data[0] << endl;
        // cout <<  setw(40) << "engine speed" << data[1] << endl;
        // cout <<  setw(40) << "engine coolant temperature" << data[2] << endl;

        cout << left;
        cout <<  "\r" << setw(10) << "fc" << data[0] <<  " | " << setw(10) << "es" << data[1] <<  " | " << setw(10) << "ect" << data[2] << flush;
    }

    obj.join();
    obj1.join();
    obj2.join();

    return 0;
}
