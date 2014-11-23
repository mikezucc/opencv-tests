/*
Author:Michael Zuccarino
This program will copy a text file to another text file.
	Input File >> current directory >> "input.txt"
	Output file >> current directory >> "output.txt"
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

int main()
{
	// Initialize workspace
	fstream inputFile;
	fstream outputFile;
	inputFile.open("input.txt", ios::in);
	string chunk;
	if (inputFile)
	{
		outputFile.open("output.txt", ios::out);
		getline(inputFile, chunk);
		outputFile << chunk << endl;
		while (!inputFile.eof())
		{
			getline(inputFile, chunk);
			outputFile << chunk;
			if (!inputFile.eof())
			{
				outputFile << endl;
			}
		}
	}

	return 0;
}