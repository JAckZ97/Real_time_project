#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

namespace csv_read
{
    // read specific row of a CSV file
    std::vector<float> readRowCSV(string fileName, int rowNumber) {
        ifstream myFile;
        myFile.open(fileName);
        string targetLine = "";
        std::vector<float> rowData;
        int a = 0;

        while (getline(myFile, targetLine)) {
            a++;
            if (a == rowNumber) {
                // cout << targetLine << endl;
                std::stringstream ss(targetLine);

                for (float i; ss >> i;) {
                    rowData.push_back(i);
                    if (ss.peek() == ',')
                        ss.ignore();
                }
            }
        }

        return rowData;
    }

    // read specific cell of the csv file
    float readCellCSV(string fileName, int rowNumber, int collumnNumber) {
        float data = 0;
        int maxCollumn = 5;

        // NOTE : collumnNumber starts at 0 ! 

        // check if the collumn number is valid
        if(collumnNumber < maxCollumn){
            std::vector<float> rowData = csv_read::readRowCSV(fileName, rowNumber);
            data = rowData[collumnNumber];
        }
        else{
            cout << "invalid cell" << endl;
        }

        return data;
    }
}
