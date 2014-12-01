/*
Author:Michael Zuccarino
This program will read a text file of a maximum word count of 128. It will then return an output file with
every word from the input file on a line and the character count next to it.
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
	string stringStore[128];
	int characterCountStore[128] = { 0 };
	int wordCount = 0;
	if (inputFile)
	{
		outputFile.open("output.txt", ios::out);

		do
		{
			getline(inputFile, chunk);
			int charCount = 0;
			string word;
			if (wordCount == 128) break; // overflow
			for (int i = 0; i < chunk.length(); i++)
			{
				if (chunk[i] != ' ')
				{
					word += chunk[i];
					charCount++;
				}
				else
				{
					// found a whitespace, cut word
					if (charCount != 0)
					{
						cout << word << "charcount:" << charCount << endl;
						stringStore[wordCount] = word;
						characterCountStore[wordCount] = charCount;
						wordCount++;
						charCount = 0;
						word = "";
					}
					else
					{
						charCount = 0;
						word = "";
					}
				}

			}
		} while (!inputFile.eof());

		for (int k = wordCount-1; k >= 0; k--)
		{
			outputFile << stringStore[k] << " " << characterCountStore[k] << endl;
		}

	}

	return 0;
}