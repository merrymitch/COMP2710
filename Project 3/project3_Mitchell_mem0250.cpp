/*
 * File Name: project3_Mitchell_mem0250.cpp
 * Author:    Mary Mitchell
 * UserID:    mem0250
 * Class:     COMP 2710
 * Version:   2 July 2021
 *
 * Info:      Program to read input from two files, sort and merge them,
 *            and output the information to a separate file. 
 *
 * Sources:   I used information from the hint and from the project
 *            briefing to help write this program.
 *
 * Location:  home/u1/mem0250/Project3
 * Compile:   g++ project3_Mitchell_mem0250.cpp
 * Run:       ./a.out
 */

#include <fstream>
#include <iostream>
#include <cstdlib>
using namespace std;

/********** VARIBALES **********/

const int MAX_SIZE = 100;

/********** FUNCTION DECLARATIONS **********/

/*
 * Reads a file and checks that it opens correctly. If so 
 * it outputs the number of integers in the file. 
 */
int readfile(int inputArray[], ifstream& inStream);

/*
 * Combines and sorts two arrays and stores the merged values in a
 * new array.
 */
int sort(int inputArray1[], int inputArray1_size, int inputArray2[],
	int inputArray2_size, int outputArray[]);

/* 
 * Writes the new combined array into a file.
 */
void writefile(int outputArray[], int outputArray_size);

/********** MAIN METHOD **********/

/*
 * Takes input from two files, combines and sorts the numbers and then
 * outputs the result to a separate file.
 */
int main() {
	// Variables for the arrays, their sizes, and file names.
	int array1[MAX_SIZE];
	int array1_size;
	int array2[MAX_SIZE];
	int array2_size;
	int outArray[MAX_SIZE];
	int outArray_size;
	string fileName;

	// FIRST FILE
	// Begin user interface and get input for first file.
	ifstream inStream1;
	cout << "*** Welcome to Mary's sorting program ***\n";
	cout << "Enter the first input file name: ";
	cin >> fileName;
	// Open the file and read it. If the file fails to open terminate.
	inStream1.open(fileName.c_str());
	// This method also checks for the file opening
	array1_size = readfile(array1, inStream1);
	if (array1_size < 0) {
		exit(1);		
	}
	// Output the integers from the file
	cout << "The list of " << array1_size << " numbers in file " << fileName << " is: \n";	
	for (int i = 0; i < array1_size; i++) {
		cout << array1[i] << "\n";
	}
	// Close file 1
	inStream1.close();
	
	// SECOND FILE
	//Begin the user interface for second file and get its input.
	ifstream inStream2;
	cout << "\nEnter the second input file name: ";
	cin >> fileName;
	// Open the file and read it. If the file fails to open terminate.
	inStream2.open(fileName.c_str());
	// This method also checks for the file opeing
	array2_size = readfile(array2, inStream2);
	if (array2_size < 0) {
		exit(1);
	}
	// Output the integer from the file.
	cout << "The list of " << array2_size << " numbers in file " << fileName << " is: \n";
	for (int j = 0; j < array2_size; j++) {
		cout << array2[j] << "\n";
	}
	// Close the second file.
	inStream2.close();
	
	// OUTPUT TO THIRD FILE
	// Sort the arrays from the first and second files. Then output the new sorted 
	// array and write it into a new file.
        outArray_size = sort(array1, array1_size, array2, array2_size, outArray);
	if (outArray_size < 0) {
		cout << "\nThe combined files exceed the maximum amount of integers.\n";
		cout << "Try files that do not combine to over 100 integers.\n";
		exit(1);
	}
	cout << "\nThe sorted list of " << outArray_size << " numbers is: ";
	for (int k = 0; k < outArray_size; k++) {
		cout << outArray[k] << " ";
	}
	cout << "\n";
	writefile(outArray, outArray_size);
	return 0;
}

/********** FUNCTION DEFINITIONS **********/

int readfile(int inputArray[], ifstream& inStream) {
	// Checks if file is opening properly
	if (inStream.fail()) {
		cout << "The input file failed opening.\n";
		return -1;
	}
	else { // Otherwise it continues to read the file
		int index = 0;
		inStream >> inputArray[index];
		while (!inStream.eof()) {
			// Checks the size of the array
			if (index > MAX_SIZE - 1) {
				cout << "File contains too many integers.\n";
				cout << "Try a file with that does not exceed 100 integers.\n";
				return -1;
			}
			index++;
			inStream >> inputArray[index];
		}
		return index;
	}
}

int sort(int inputArray1[], int inputArray1_size, int inputArray2[],
	int inputArray2_size, int outputArray[]) {
	// Variables to maintain idexes while sorting the arrays
	int index1 = 0;
	int index2 = 0;
	int index3 = 0;
	int size = 0;
	// Add the two arrays to the output array. Check size as well.
	for (index1 = 0; index1 < inputArray1_size; index1++) {
		outputArray[index1] = inputArray1[index1];
		if (index1 > MAX_SIZE - 1) {
			return -1;
		}
	}
	for (index2 = 0; index2 < inputArray2_size; index2++) {
		outputArray[index1] = inputArray2[index2];
		if (index1 > MAX_SIZE - 1) {
			return -1;
		}
		index1++;
	}
	//Normal sort of the combined array
	size = index1;
	for (index2 = 0; index2 < (size - 1); index2++) {
		for (index1 = 0; index1 < (size - 1); index1++) {
			if (outputArray[index1] > outputArray[index1 + 1]) {
				index3 = outputArray[index1];
				outputArray[index1] = outputArray[index1 + 1];
				outputArray[index1 + 1] = index3;
			}
		}
	}
	return size;
} 

void writefile(int outputArray[], int outputArray_size) {
	// Output file stream
	ofstream outStream;
	string outFile;
	// Interface and input
	cout << "Enter the output file name: ";
	cin >> outFile;
	// Opens file and outputs the array accordingly
	outStream.open((char*)outFile.c_str());
	for (int i = 0; i < outputArray_size; i++) {
		outStream << outputArray[i] << "\n";
	}
	// Close the file and finish the interface
	outStream.close();
	cout << "*** Please check the new file - " << outFile << " ***\n";
	cout << "*** Goodbye ***\n";
}
