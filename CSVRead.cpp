#include "CSVRead.h"

CSVRead::CSVRead(){
    // lock = PTHREAD_MUTEX_INITIALIZER;
    pthread_mutex_init(&lock, NULL);

}

const char* CSVRead::readColFromLine(char* line, int num)
    {
        const char* tok;
        for (tok = strtok(line, ",");
                tok && *tok;
                tok = strtok(NULL, ",\n"))
        {
            if (!--num)
                return tok;
        }
        return NULL;
    }

// the csv starts at row 1 and col 1 (not at 0's)
// FIXME : we cant read (1,1)
double CSVRead::readCellCSV(const char* fileName, int row, int col)
    {
        pthread_mutex_lock(&lock);
        FILE* stream = fopen(fileName, "r");

        char line[3072];
        int count = 1;
        while (fgets(line, 3072, stream))
        {
            if(count == row){
                char* tmp = strdup(line);
                double data = atof(readColFromLine(tmp, col));
                free(tmp);

                fclose(stream);
                pthread_mutex_unlock(&lock);
                return data;
            }
            count = count + 1;
        }
        fclose(stream);
        pthread_mutex_unlock(&lock);
        return -9999; // invalid number FIXME : quick fix
    }

int CSVRead::maxRowCSV(const char* fileName)
    {
        pthread_mutex_lock(&lock);
        FILE* stream = fopen(fileName, "r");

        char line[1024];
        int count = 0;
        while (fgets(line, 1024, stream))
        {
            count = count + 1;
        }
        fclose(stream);
        pthread_mutex_lock(&lock);
        return count;
    }

