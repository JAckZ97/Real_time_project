#include <string.h>
using namespace std;

namespace csv_read
{
    const char* readColFromLine(char* line, int num)
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
    double readCellCSV(const char* fileName, int row, int col)
        {
            FILE* stream = fopen(fileName, "r");

            char line[1024];
            int count = 1;
            while (fgets(line, 1024, stream))
            {
                if(count == row){
                    char* tmp = strdup(line);
                    double data = atof(readColFromLine(tmp, col));
                    free(tmp);
                    return data;
                }
                count = count + 1;
            }
            return -9999; // invalid number FIXME : quick fix
        }

    int maxRowCSV(const char* fileName)
        {
            FILE* stream = fopen(fileName, "r");

            char line[1024];
            int count = 0;
            while (fgets(line, 1024, stream))
            {
                count = count + 1;
            }
            return count;
        }
}
