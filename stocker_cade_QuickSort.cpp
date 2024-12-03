#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>

using namespace std;

class QuickSort {
private:
    // file names are constants
    const string EXECUTION_TIME_FILE = "Stocker_Cade_executionTime.txt";
    const string AVERAGE_TIME_FILE = "Stocker_Cade_averageExecutionTime.txt";

public:
    // function to find median of three
    int medianOfThree(float array[], int left, int right) {
        int middle = left + (right - left) / 2;

        if (array[left] > array[middle]) swap(array[left], array[middle]);
        if (array[left] > array[right]) swap(array[left], array[right]);
        if (array[middle] > array[right]) swap(array[middle], array[right]);

        return middle;
    }

    // partition the array, using median of three
    int partition(float array[], int left, int right) {
        // use median of three
        int pivotIndex = medianOfThree(array, left, right);
        // find value in pivot index
        float pivotValue = array[pivotIndex];
        // swap with left
        swap(array[pivotIndex], array[left]);
        int i = left + 1;

        // swap if value of i is less than the pivot
        for (int j = left + 1; j <= right; j++) {
            if (array[j] < pivotValue) {
                swap(array[i], array[j]);
                i++;
            }
        }

        // swap left and i - 1
        swap(array[left], array[i - 1]);
        return i - 1;
    }

    // quicksort algorithm
    void quickSort(float array[], int left, int right) {
        if (left < right) {
            int pivotIndex = partition(array, left, right);
            quickSort(array, left, pivotIndex - 1);
            quickSort(array, pivotIndex + 1, right);
        }
    }

    // function to read files
    int readFile(const string& filename, float array[]) {
        ifstream inputFile(filename);
        if (!inputFile) {
            cerr << "Error opening file: " << filename << endl;
            return -1;
        }

        int size = 0;
        while (inputFile >> array[size]) {
            size++;
        }

        inputFile.close();
        return size;
    }

    // write the time it takes to sort
    void recordExecutionTime(int inputSize, double duration) {
        ofstream outFile(EXECUTION_TIME_FILE, ios::app);
        // see if the file can be opened
        if (!outFile) {
            cout << "trouble opening file: " << EXECUTION_TIME_FILE << endl;
            return;
        }
        // spaces in between numbers
        outFile << inputSize << "    " << fixed << setprecision(8) << duration << endl;
        outFile.close();
    }

    // process the input files and find times
    void processFiles(const vector<string>& files, int inputSize) {
        const int MAX_SIZE = 10000; // assignment says max of 1,000
        float array[MAX_SIZE];

        // iterate through files
        for (const auto& file : files) {
            int size = readFile(file, array);
            if (size == -1) continue;

            // start the clock
            auto start = chrono::high_resolution_clock::now();
            // sort the numbers
            quickSort(array, 0, size - 1);
            // end the clock
            auto end = chrono::high_resolution_clock::now();

            // calculate the duration
            double duration = chrono::duration_cast<chrono::microseconds>(end - start).count();
            // call the function above
            recordExecutionTime(inputSize, duration);
        }
    }

    // calculate average execution times
    void calculateAverages() {
        // make sure the file works
        ifstream inFile(EXECUTION_TIME_FILE);
        if (!inFile) {
            cerr << "Error opening file: " << EXECUTION_TIME_FILE << endl;
            return;
        }

        // make sure the file works
        ofstream outFile(AVERAGE_TIME_FILE);
        if (!outFile) {
            cerr << "Error opening file: " << AVERAGE_TIME_FILE << endl;
            return;
        }

        // the 3 input sizes given in instructions
        vector<int> inputSizes = {10, 100, 1000};
        // for each size, make 25 files (or given amount)
        for (int size : inputSizes) {
            double total = 0.0;
            int count = 0;
            string line;

            // print the input size and time it took
            while (getline(inFile, line)) {
                istringstream iss(line);
                int inputSize;
                double time;

                iss >> inputSize >> time;
                if (inputSize == size) {
                    total += time;
                    count++;
                }
            }

            // find the average
            if (count > 0) {
                double average = total / count;
                outFile << size << "    " << fixed << setprecision(8) << average << endl;
            }

            inFile.clear();
            inFile.seekg(0);
        }

        inFile.close();
        outFile.close();
    }
};

int main() {
    // quicksort object
    QuickSort sorter;

    // input sizes from instructions
    const int inputSizes[] = {10, 100, 1000};
    const int numFiles = 25;

    // for each size, make 25 file names
    for (int size : inputSizes) {
        vector<string> files;
        for (int i = 1; i <= numFiles; i++) {
            files.push_back("input_size" + to_string(size) + "_file" + to_string(i) + ".txt");
        }
        // sort the files
        sorter.processFiles(files, size);
    }

    // find averages and store them
    sorter.calculateAverages();

    cout << "Execution times and averages recorded successfully!" << endl;
    return 0;
}
