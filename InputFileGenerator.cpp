#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>
#include <string>

using namespace std;

// function to make the files
// takes in size, number of desired files, plus the name of the file before adding specifics to name
void generateInputFiles(int size, int numFiles, const string& baseFilename) {
    // make random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dis(-100.0, 100.0);
    
    // loop until correct number of files are made
    for (int i = 1; i <= numFiles; i++) {
        // name the file
        string filename = baseFilename + "_size" + to_string(size) + "_file" + to_string(i) + ".txt";
        ofstream outFile(filename);

        // make sure you can write
        if (!outFile) {
            cerr << "Error creating file: " << filename << endl;
            continue;
        }

        // append the correct amount of random numbers
        for (int j = 0; j < size; j++) {
            outFile << fixed << setprecision(6) << dis(gen) << " ";
        }
        outFile.close();
    }
}

// main function to be called
int main() {
    // numbers given in instructions
    const int inputSizes[] = {10, 100, 1000};
    const int numFiles = 25;

    // make 25 of each size file
    for (int size : inputSizes) {
        generateInputFiles(size, numFiles, "input");
    }

    // output that the function ran successfully
    cout << "Input files made successfully!" << endl;
    return 0;
}
