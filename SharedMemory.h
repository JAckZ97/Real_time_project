#ifndef __SHAREDMEMORY_H_
#define __SHAREDMEMORY_H_

#include <iostream>
#include <string>
#include <array>
#include <mutex>
using namespace std;

class SharedMemory{

   public:
   // variables
   array<double, 8> memory {0};
   mutex mu;

   // methods
   array<double, 8> access(int mode, int index, double value){
      // mode = 0 -> write
      // mode = 1 -> read
      
      mu.lock();

      // init temp
      array<double, 8> tempMem {0};

      // switch case mode
      if(mode == 0){
         writeArray(index, value);
      }
      else if (mode == 1)
      {
         tempMem = readArray();
      }

      mu.unlock();

      return tempMem;
   }

   private:
   array<double, 8> readArray(){
      return memory;
   }

   void writeArray(int index, double value){
      memory[index] = value;
   }
};

#endif // __SHAREDMEMORY_H_
