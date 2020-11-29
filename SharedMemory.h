#ifndef __SHAREDMEMORY_H_
#define __SHAREDMEMORY_H_

#include <iostream>
#include <string>
#include <mutex> // FIXME : replace
#include <pthread.h>
using namespace std;

class SharedMemory{

   // variables
   static const int SIZE = 8;
   double memory[SIZE];
   pthread_mutex_t lock;
   mutex mu; // FIXME : replace

   public:
   SharedMemory();
   double* readArray();
   void writeArray(int index, double value);
   double* access(int mode, int index, double value);

};

#endif // __SHAREDMEMORY_H_
