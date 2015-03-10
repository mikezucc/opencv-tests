/*
Author:Michael Zuccarino
This program will return a sorted list of words from a desginated input file.

Use:
Provide an input and output file name. The input file should be a text file to sort.
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

vector<string> sortList;

void selectionSort(const string *document, int numberOfWords)
{
	for (int idx = 0; idx < numberOfWords; idx++)
	{
		int minIdx = idx;
		string valueSuper = document[idx];
		//cout << valueSuper << " WORD to compare" << endl;
		char charSuper = valueSuper.at(0);
		//cout << charSuper << " CHAR to compare" << endl;
		if (sortList.size() == 0)
		{
			sortList.push_back(valueSuper);
		}
		vector<string> temp;
		bool gradient = true;
		for (int idn = 0; idn < (int)sortList.size(); idn++)
		{
			string valueCompare = sortList[idn];
			char charCompare = sortList[idn].at(0);
			//cout << "comparing to " << sortList[idn] << endl;
			if ((charSuper < charCompare) && gradient)
			{
				temp.push_back(valueSuper);
				gradient = false;
			}
			temp.push_back(valueCompare);
		}
		if (gradient)
		{
			temp.push_back(valueSuper);
		}
		
		sortList = temp;
	}
	
	for (int k = 0; k < (int)sortList.size(); k++)
	{
		cout <<  "k: " << k << ", " << sortList[k] << endl;
	}
	
}

int main()
{
	// Initialize workspace
	fstream inputFile;
	fstream outputFile;

	cout << "Please enter the name of input file" << endl;
	string inputfileName;
	getline(cin, inputfileName);
	cout << "Please enter the name of output file" << endl;
	string outputFileName;
	getline(cin, outputFileName);

	inputFile.open(inputfileName, ios::in);
	outputFile.open(outputFileName, ios::out);
	string werds[1024] = { "" };
	int numberOfWords = 0;
	if (inputFile)
	{
		string chunk = "";

		do
		{
			getline(inputFile, chunk, ' ');
			//cout << "chunk is " << chunk << endl;
			if (chunk.size() > 1)
			{
				werds[numberOfWords++] = chunk;
			}
		} while (!inputFile.eof());
	}
	//cout << numberOfWords << "number of words" << endl;
	selectionSort(werds, numberOfWords);

	for (int k = 0; k < sortList.size(); k++)
	{
		outputFile << sortList[k];
	}

	outputFile.close();
	inputFile.close();

	return 0;
}