#include "SharedMemory.h"

SharedMemory::SharedMemory(){
}

double* SharedMemory::readArray(){
    return memory;
}

void SharedMemory::writeArray(int index, double value){
    memory[index] = value;
}

double* SharedMemory::access(int mode, int index, double value){
    // mode = 0 -> write
    // mode = 1 -> read
    
    pthread_mutex_lock(&lock);

    // init temp
    double *tempMem;

    // switch case mode
    if(mode == 0){
        writeArray(index, value);
    }
    else if (mode == 1)
    {
        tempMem = readArray();
    }

    pthread_mutex_unlock(&lock);

    return tempMem;
}