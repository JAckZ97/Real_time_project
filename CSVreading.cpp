#include <fstream>

int main() {
    // Create an output filestream object
    std::ofstream myFile("Driving Data(KIA SOUL)_(150728-160714)_(10 Drivers_A-J).csv");
    
    // Send data to the stream
    myFile << "readCSVfile\n";
    myFile << "1\n";
    myFile << "2\n";
    myFile << "3\n";
    
    // Close the file
    myFile.close();
    
    return 0;
}