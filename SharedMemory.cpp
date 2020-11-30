#include "SharedMemory.h"

SharedMemory::SharedMemory(){
    // dont know why we can do, memory = {0}; 
    memory[0] = 0;
    memory[1] = 0;
    memory[2] = 0;
    memory[3] = 0;
    memory[4] = 0;
    memory[5] = 0;
    memory[6] = 0;
    memory[7] = 0;

    // lock = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_init(&lock, NULL);
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
    // mu.lock(); // FIXME : replace

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
    // mu.unlock(); // FIXME : replace

    return tempMem;
}