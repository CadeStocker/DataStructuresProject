# compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

all: InputFileGenerator QuickSort

InputFileGenerator: InputFileGenerator.cpp
	$(CXX) $(CXXFLAGS) -o InputFileGenerator InputFileGenerator.cpp

QuickSort: stocker_cade_QuickSort.cpp
	$(CXX) $(CXXFLAGS) -o QuickSort stocker_cade_QuickSort.cpp

# clean up files made during program running
clean:
	rm -f InputFileGenerator QuickSort *.o
	> Stocker_Cade_executionTime.txt
	> Stocker_Cade_averageExecutionTime.txt
	rm -f input_size*_file*.txt
