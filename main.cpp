// standard imports
#include <iostream>
#include <string> // FIXME
#include<stdio.h>
// user import
#include "DataProducer.h"
#include "DataConsumer.h"
// #include <thread>
#include <pthread.h> 

using namespace std;

/*
 *
 * NOTE : modified the header for Engine_coolant_temperature since there is duplicate (ie modified top Engine_coolant_temparature1)
 * 
 * NOTE : to compile and run the code
 * $ c++ -pthread *.cpp -o main && ./main
*/

void* start_dp(void* arg){
    DataProducer *this_ = (DataProducer *)arg;
    this_->run();
    return 0;
}

void* start_dc(void* arg){
    DataConsumer *this_ = (DataConsumer *)arg;
    this_->run();
    return 0;
}

double s_2_ms(double timeMS){
    return timeMS * 1000;
}

int main(int argc, char *argv[]) {

    cout << "Start program" << endl;

    // Init. common database
    SharedMemory sharedMem; // NOTE : instead of declaring SharedMemory *sharedMem and passing as sharedMem -> SharedMemory and passing as &sharedMem does not trigger mutex error
    CSVRead csvRead;

    // creating the data producer threads
    DataProducer prod0("Fuel_consumption",1, 10, &sharedMem, 0, &csvRead);
    DataProducer *ptrProd0 = &prod0;              
    DataProducer prod1("Engine_speed", 13, 500, &sharedMem, 1, &csvRead);
    DataProducer *ptrProd1 = &prod1;
    DataProducer prod2("Engine_coolant_temperature1", 18, s_2_ms(2), &sharedMem, 2, &csvRead);
    DataProducer *ptrProd2 = &prod2;
    DataProducer prod3("Current_gear", 34, 100, &sharedMem, 3, &csvRead);
    DataProducer *ptrProd3 = &prod3;
    DataProducer prod4("Transmission_oil_temperature", 35, s_2_ms(5), &sharedMem, 4, &csvRead); 
    DataProducer *ptrProd4 = &prod4;
    DataProducer prod5("Vehicule_speed", 44, 100, &sharedMem, 5, &csvRead);
    DataProducer *ptrProd5 = &prod5;
    DataProducer prod6("Acceleration_speed_longitudinal", 45, 150, &sharedMem, 6, &csvRead);
    DataProducer *ptrProd6 = &prod6;
    DataProducer prod7("Indication_of_break_switch", 46, 100, &sharedMem, 7, &csvRead);
    DataProducer *ptrProd7 = &prod7;

    pthread_t ptid0, ptid1, ptid2, ptid3, ptid4, ptid5, ptid6, ptid7 ; 
    pthread_create(&ptid0, NULL, &start_dp, (void *)ptrProd0);
    pthread_create(&ptid1, NULL, &start_dp, (void *)ptrProd1);
    pthread_create(&ptid2, NULL, &start_dp, (void *)ptrProd2);
    pthread_create(&ptid3, NULL, &start_dp, (void *)ptrProd3);
    pthread_create(&ptid4, NULL, &start_dp, (void *)ptrProd4);
    pthread_create(&ptid5, NULL, &start_dp, (void *)ptrProd5);
    pthread_create(&ptid6, NULL, &start_dp, (void *)ptrProd6);
    pthread_create(&ptid7, NULL, &start_dp, (void *)ptrProd7);

    // creating the data consumer thread
    int periodMS = 10;
    DataConsumer cons(&sharedMem, periodMS);
    DataConsumer *ptrCons = &cons;
    pthread_t ptidCons;
    pthread_create(&ptidCons, NULL, &start_dc, (void *)ptrCons);

    // wait for producer threads
    pthread_join(ptid0, NULL); 
    pthread_join(ptid1, NULL); 
    pthread_join(ptid2, NULL); 
    pthread_join(ptid3, NULL); 
    pthread_join(ptid4, NULL); 
    pthread_join(ptid5, NULL); 
    pthread_join(ptid6, NULL); 
    pthread_join(ptid7, NULL); 

    // wait for consumer thread
    pthread_join(ptidCons, NULL); 

    pthread_exit(NULL); 

    return 0;
}
