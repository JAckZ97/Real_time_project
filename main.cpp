#include <fstream>
#include <iostream>
#include <string>
using namespace std;

void readRowCSV(string fileName, int rowNumber) {
	ifstream myFile;
	myFile.open(fileName);
	string line;
	int a = 0;

	while (getline(myFile, line)) {
		a++;
		if (a == rowNumber) {
			cout << line << endl;
			break;
		}

	}
}
void countAndShowCSV(string fileName, int rowNumber) {
	ifstream myFile;
	myFile.open(fileName);

	string line;
	int counter = 0;

	while (getline(myFile, line)) {
		counter++;
	}

	if (rowNumber > counter) {
		cout << "Row does not exist" << endl;
	}
	else {
		readRowCSV(fileName, rowNumber);
	}
}


int main() {

	countAndShowCSV("test.csv", 3);
	countAndShowCSV("test.csv", 2);

	return 0;
}
