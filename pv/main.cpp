// standard imports
#include <iostream>
#include <string>
// user import
#include "DataProducer.hpp"
#include <thread>

/*
 * NOTE : 3rd party library used
 * https://github.com/ben-strasser/fast-cpp-csv-parser
 *
 * FIXME : modified the header for Engine_coolant_temperature since there is duplicate (ie modified top Engine_coolant_temparature1)
 */

using namespace std;

int main(int argc, char *argv[]) {

    cout << "Start program" << endl;

    float data[3] = {0,0,0};
    float *p_data;

    p_data = data;

    DataProducer prod("Fuel_consumption", 10ms, (p_data + 0));
    DataProducer prod1("Engine_speed", 500ms, (p_data + 1));
    DataProducer prod2("Engine_coolant_temperature1", 2s, (p_data + 2));

    std::thread obj(&DataProducer::run, prod);
    std::thread obj1(&DataProducer::run, prod1);
    std::thread obj2(&DataProducer::run, prod2);

    while(true){
        sleep(1);
        cout << "--------------" << endl;
        cout << left;
        cout <<  setw(40) << "fuel consumption" << data[0] << endl;
        cout <<  setw(40) << "engine speed" << data[1] << endl;
        cout <<  setw(40) << "engine coolant temperature" << data[2] << endl;
    }

    obj.join();
    obj1.join();
    obj2.join();

    return 0;
}
