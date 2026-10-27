#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

using namespace std;

int main() {
    ifstream simulatedFile("NumberOfHousehold.csv");
    ifstream historicalFile("data/target_data.csv");

    if (!simulatedFile.is_open() || !historicalFile.is_open()) {
        cerr << "Error opening CSV files!" << endl;
        return 1;
    }

    map<int, int> historicalData;
    string line;
    int year, households;
    char comma;

    // Read historical data (no header)
    while (getline(historicalFile, line)) {
        stringstream ss(line);

        if (ss >> year >> comma >> households && comma == ',') {
            historicalData[year] = households;
        }
    }

    // Skip simulation file header
    getline(simulatedFile, line);

    // Create output CSV
    ofstream outputFile("outputs/comparison.csv");

    if (!outputFile.is_open()) {
        cerr << "Cannot create output file!" << endl;
        return 1;
    }

    outputFile << "Year,Simulated,Historical,Difference\n";

    // Compare data for matching years
    while (getline(simulatedFile, line)) {
        stringstream ss(line);

        if (ss >> year >> comma >> households && comma == ',') {
            if (historicalData.count(year) > 0) {
                int historical = historicalData[year];
                int difference = households - historical;

                outputFile << year << ","
                           << households << ","
                           << historical << ","
                           << difference << "\n";

                cout << "Year: " << year
                     << " Simulated: " << households
                     << " Historical: " << historical
                     << " Difference: " << difference
                     << endl;
            }
        }
    }

    outputFile.close();
    simulatedFile.close();
    historicalFile.close();

    cout << "Comparison saved to outputs/comparison.csv" << endl;

    return 0;
}
