#ifndef __CSVREAD_H_
#define __CSVREAD_H_

#include <string.h>
// #include <mutex> // FIXME : replace
#include <pthread.h>

using namespace std;

class CSVRead {

    // attributes
    pthread_mutex_t lock;

    public:
    CSVRead();
    const char* readColFromLine(char* line, int num);
    double readCellCSV(const char* fileName, int row, int col);
    int maxRowCSV(const char* fileName);
};

#endif // __CSVREAD_H_
