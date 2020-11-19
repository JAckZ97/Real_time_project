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
int main() {
	readRowCSV("test.csv", 2);

	return 0;
}


//void readRowCSV(string fileName, int rowNumber) {
//	ifstream myFile;
//	myFile.open(fileName);
//	string line;
//	int a = 0;
//
//	while (getline(myFile, line)) {
//		a++;
//		if (a == rowNumber) {
//			cout << line << endl;
//			break;
//		}
//
//	}
//}