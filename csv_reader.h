#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

namespace csv_read
{
    // read specific row of a CSV file
    std::vector<double> readRowCSV(string fileName, int rowNumber, int maxRowNumber) {
        std::vector<double> rowData;

        if(rowNumber <= maxRowNumber){
            ifstream myFile;
            myFile.open(fileName);
            string targetLine = "";
            
            int a = 0;

            while (getline(myFile, targetLine)) {
                a++;
                if (a == rowNumber) {
                    // cout << targetLine << endl;
                    std::stringstream ss(targetLine);

                    for (double i; ss >> i;) {
                        rowData.push_back(i);
                        if (ss.peek() == ',')
                            ss.ignore();
                    }
                }
            }
        }
        else{
            cout << "invalid row access" << endl;
        }

        return rowData;
    }

    // read specific cell of the csv file
    double readCellCSV(string fileName, int rowNumber, int collumnNumber, int maxRowNumber) {
        double data = 0;
        int maxCollumn = 5;

        // NOTE : collumnNumber starts at 0 ! 

        // check if the collumn number is valid
        if(collumnNumber < maxCollumn){
            std::vector<double> rowData = csv_read::readRowCSV(fileName, rowNumber, maxRowNumber);
            data = rowData[collumnNumber];
        }
        else{
            cout << "invalid cell" << endl;
        }

        return data;
    }

    // get maximum row number of csv file
    int maxRowCSV(string fileName) {
        ifstream myFile;
        myFile.open(fileName);

        string line;
        int counter = 0;

        while (getline(myFile, line)) {
            counter++;
        }

        return counter;
    }
}
