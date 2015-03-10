/*
Author:Michael Zuccarino
This program will calculate the mean and median of a class, and display some statistics about 
each student's performance compared to the class.

Use:
	Choose 'f' or 'm' to read from a file or enter data manually respectively
	In file, data must be formatted: each student per row, "firstname lastname score" to parse correctly

Functions:
	int retrieveMedian(const int *scoreList)
		This function is MY JAM I AM REALLY PROUD OF THINKING OF THIS!!!!!!!!!! I would imagine it's not knew but I applied it here!
		I used a concept from the Hough transform to sort the data without
		forcing order of computation to a minimum of O(N^2) as many traditional bubble sort and compare
		algorithms do. I even know some that must do O(N!) and that isn't fresh.
		The sort function contains a bin for every possible score value (domain(N)) and each bin gets a
		"vote" if there as an existing value for it. In this case I placed the index of referenced score
		into the bin array at the index of it's value. For example, if the 3rd student has 75, the value "3" is placed in index 75 of the bin.
		Then, after doing this (domain(N)) number of retrievals, I smash the array down,
		so that each occupied bin is adjacent to another. Essentially just incrementing until non-negative value found.
		This is then an O(N) of movements, thus now we
		have a sorted list of scores. :] If duplicates are present, the computation increase is just linear.

	retrieveIndexOfLowest(const int *scoreList) -> int lowestIndex
		This function returns the index on the supplied list of information of the student with the
		lowest score.

	retrieveIndexOfHighest(const int *scoreList) -> int highestIndex
		This function returns the index on the supplied list of information of the student with the
		highest score.

	retrieveTestAverage(const int *scoreList) -> int mean
		This function returns the average of all passed test scores.

Input File >> current directory >> "input.txt"
Output file >> current directory >> "output.txt"
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

int retrieveIndexOfLowest(const int *scoreList)
{
	int lowestScoreIdx = 0;
	int previousScore = 101;
	for (int idx = 0; idx < 1024; idx++)
	{
		if (scoreList[idx] == 0)
		{
			break;
		}
		else
		{
			if (previousScore > scoreList[idx])
			{
				previousScore = scoreList[idx];
				lowestScoreIdx = idx;
			}
		}
		cout << "LOWEST || prev score is: " << previousScore << ",returned index is: " << lowestScoreIdx << endl;
	}
	return lowestScoreIdx;
}

int retrieveIndexOfHighest(const int *scoreList)
{
	int highestScoreIdx = 0;
	int previousScore = 0;
	for (int idx = 0; idx < 1024; idx++)
	{
		if (scoreList[idx] == 0)
		{
			break;
		}
		else
		{
			if (previousScore < scoreList[idx])
			{
				previousScore = scoreList[idx];
				highestScoreIdx = idx;
			}
		}
		cout << "HIGHEST || prev score is: " << previousScore << ",returned index is: " << highestScoreIdx << endl;
	}
	return highestScoreIdx;
}

int retrieveTestAverage(const int *scoreList)
{
	int scoreTotal = 0;
	int count = 0;
	for (int idx = 0; idx < 1024; idx++)
	{
		if (scoreList[idx] == 0)
		{
			count = idx;
			break;
		}
		scoreTotal += scoreList[idx];
	}
	return scoreTotal / count;
}

int retrieveMedian(const int *scoreList)
{
	// This is my genius O(N * domain(N)) sort. I think more efficient than traditional compare and 
	// bubble sort functions of O(N^2) :]. Inspired by Hough Transform.
	int highestScoreIdx = 0;
	int previousScore = 0;
	int arrLength = 0;
	int bins[101];
	for (int k = 0; k < 101; k++)
	{
		bins[k] = -1;
	}
	for (int idx = 0; idx < 1024; idx++)
	{
		if (scoreList[idx] == 0)
		{
			break;
		}
		arrLength++;
	}
	for (int idx = 0; idx < arrLength; idx++)
	{
		bins[(scoreList[idx])] = idx;
		cout << "index " << idx << "stored in bin " << (scoreList[idx]) << endl;
	} 
	int idx = 0, counter = 0;
	int ordered[1024] = { 0 };
	while (counter <= 100)
	{
		if (bins[counter] == -1)
		{
			cout << "empty bin at " << counter << endl;
		}
		else
		{
			ordered[idx] = scoreList[bins[counter]];
			cout << "ordered bin row " << idx << "is " << scoreList[bins[counter]] << endl;
			idx++;
		}
		counter++;
	}
	// dump array
	for (int i = 0; i < arrLength; i++)
	{
		cout << "array dump i: " << i << " value: " << ordered[i] << endl;
	}
	int middle = arrLength / 2;
	cout << "middle is: " << middle << endl;
	int median = ordered[middle];
	cout << "median is " << median << endl;
	return median;
}

int main2()
{
	// Initialize workspace
	fstream inputFile;
	fstream outputFile;
	inputFile.open("input.txt", ios::in);
	string chunk;
	string studentName[1024] = { "" };
	int studentScores[1024] = { 0 };
	int nameCount = 0, scoreCount = 0;

	cout << "Welcome to the class statistic program!" << endl;
	cout << "Press \"f\" for file input, or \"m\" for manual input: ";
	char inputType;
	bool waitingInput = true;
	while (waitingInput)
	{
		cin >> inputType;
		switch (inputType)
		{
		case 'f':
			waitingInput = false;
			break;
		case 'm':
			waitingInput = false;
			break;
		default:
			cout << "Oops, try again: ";
		}
	}
	outputFile.open("output.txt", ios::out);
	if (inputType == 'f')
	{
		if (inputFile)
		{
			string firstName = "", lastName = "";
			int scoreTemp = 0;

			do
			{

				getline(inputFile, firstName, ' ');
				getline(inputFile, lastName, ' ');
				inputFile >> scoreTemp;
				inputFile.ignore(256, '\n');
				if (!inputFile.eof())
				{
					studentName[nameCount++] = firstName + " " + lastName;
					studentScores[scoreCount++] = scoreTemp;
					cout << "names: " << studentName[(nameCount - 1)] << "... score: " << studentScores[(scoreCount - 1)] << endl;
				}
			} while (!inputFile.eof());

			int lowestIdx = retrieveIndexOfLowest(studentScores);
			cout << "LOWEST || returned index is: " << lowestIdx << endl;

			int highestIdx = retrieveIndexOfHighest(studentScores);
			cout << "HIGHEST || returned index is: " << highestIdx << endl;

			int testAverage = retrieveTestAverage(studentScores);
			cout << "AVERAGE || returned index is: " << testAverage << endl;

			int median = retrieveMedian(studentScores);
			cout << "MEDIAN || returned index is: " << median << endl;

			outputFile << "CLASS REPORT: Lowest: " << studentScores[lowestIdx] << ", Highest: " << studentScores[highestIdx] << ", Average: " << testAverage << ", Median: " << median << endl;
			outputFile << "--STUDENT NAME                SCORE -| COMPARE TO |- LOWEST - HIGHEST - MEAN - MEDIAN -" << endl;
			for (int i = (scoreCount - 1); i >= 0; i--)
			{
				outputFile << studentName[i] << "----------------------" << studentScores[i] << "-----------------" << (i == lowestIdx ? "  yes     " : "  no     ") << (i == highestIdx ? "  yes     " : "  no     ") << (studentScores[i] == testAverage ? "  equal  " : (studentScores[i] <= testAverage ? "  below  " : "  above  ")) << (studentScores[i] == median ? "  equal  " : (studentScores[i] <= median ? "  below  " : "  above  ")) << endl;
			}
		}
	}
	else
	{
		string fullName = "";
		int scoreTemp = 0;
		cout << "Excellent, let's begin! Type the student's name: ";
		cin.ignore(256, '\n');
		getline(cin, fullName, '\n');
		cout << "Now the score: ";
		cin >> scoreTemp;
		studentName[nameCount++] = fullName;
		studentScores[scoreCount++] = scoreTemp;
		cout << "Ok so I have " << studentName[0] << ", and he/she got score: " << studentScores[0] << endl;
		cout << "add more? (y / n)" << endl;
		waitingInput = true;
		while (waitingInput)
		{
			cin >> inputType;
			if ((inputType == 'y') || (inputType == 'n'))
			{
				break;
			}
			cout << "oops, try again" << endl;
		}
		while (inputType == 'y')
		{
			cout << "Type the student's name: ";
			cin.ignore(256, '\n');
			getline(cin, fullName, '\n');
			cout << "Now the score: ";
			cin >> scoreTemp;
			studentName[nameCount++] = fullName;
			studentScores[scoreCount++] = scoreTemp;
			cout << "Ok so I have " << studentName[nameCount - 1] << ", and he/she got score: " << studentScores[scoreCount - 1] << endl;
			cout << "add more? (y / n)" << endl;
			waitingInput = true;
			while (waitingInput)
			{
				cin >> inputType;
				if ((inputType == 'y') || (inputType == 'n'))
				{
					break;
				}
				cout << "oops, try again" << endl;
			}
		}

		int lowestIdx = retrieveIndexOfLowest(studentScores);
		cout << "LOWEST || returned index is: " << lowestIdx << endl;

		int highestIdx = retrieveIndexOfHighest(studentScores);
		cout << "HIGHEST || returned index is: " << highestIdx << endl;

		int testAverage = retrieveTestAverage(studentScores);
		cout << "AVERAGE || returned index is: " << testAverage << endl;

		int median = retrieveMedian(studentScores);
		cout << "MEDIAN || returned index is: " << median << endl;

		outputFile << "CLASS REPORT: Lowest: " << studentScores[lowestIdx] << ", Highest: " << studentScores[highestIdx] << ", Average: " << testAverage << ", Median: " << median << endl;
		outputFile << "--STUDENT NAME                SCORE -| COMPARE TO |- LOWEST - HIGHEST - MEAN - MEDIAN -" << endl;
		for (int i = (scoreCount - 1); i >= 0; i--)
		{
			outputFile << studentName[i] << "----------------------" << studentScores[i] << "-----------------" << (i == lowestIdx ? "  yes     " : "  no     ") << (i == highestIdx ? "  yes     " : "  no     ") << (studentScores[i] == testAverage ? "  equal  " : (studentScores[i] <= testAverage ? "  below  " : "  above  ")) << (studentScores[i] == median ? "  equal  " : (studentScores[i] <= median ? "  below  " : "  above  ")) << endl;
		}
	}
	
	return 0;
}
