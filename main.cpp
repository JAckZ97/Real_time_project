#include <iostream>
#include <string>
#include <array>
using namespace std;
bool flag {true};
array<double, 8> n {0};

class sharedMemory{

   public:
   void access(){

      // if writeArray():
      //    flag = false
      //    writeArray()
      //    flag = true
      // else if readArray():
      //    flag = false
      //    readArray()
      //    flag = true
      // else:
      //    flag = true
      
      writeArray(3, 2.0);
      readArray();
   }

   private:
   void readArray(){
      for (int j = 0; j < n.size(); j++ ){
         cout << "n[" << j << "] = " << n[j] << endl;
      }
   }

   private:
   void writeArray(int index, double value){
      n[index] = value;
   }
};

int main () { 
   
   sharedMemory mem;
   mem.access();

   return 0;
}