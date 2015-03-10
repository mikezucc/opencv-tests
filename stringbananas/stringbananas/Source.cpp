/*
Basic C String functions
By: Michael Zuccarino

Description: This file contains 4 adaptations of basic C String functions: stringLength, stringNCopy, stringAdd, stringCompare.

int stringLength(const char * str)
	- Receives a pointer as input to a CString, iterates through memory until a null terminating character is found.
	- Outputs the length of character array up to the null terminator

void stringNCopy(char * str1, char * str2, int lengthStr2)
	- Receives the destination string as 'str1', the source string as 'str2', and the length as 'lengthStr2'
	- Iterates through str2 copying char to relevant index in str1 until lengthStr2 reached

void stringAdd(char * str1, char * str2)
	- Receives the destination string as 'str1', the source string as 'str2'
	- Appends the data from str2 to str1 for length of str1

int stringCompare(char * str1, char * str2)
	- Receives the strings 'str1', 'str2' as input
	- Iterates through both arrays, comparing each char as an int
	- Return types:
		-1 -> First character on str1 to be unequal was of lower ASCII value
		0 -> No mismatching characters were found, aka they are equal
		1 -> First character on str1 to be unequal was of higher ASCII value

void cleanString(char * str1)
	- Receives a C String as input
	- Iterates along every char in the C String, clearing its contents
	- This function is used every time the input sequence is run

int main
	- No inputs
	- Allocates two C Strings with 1024 chars, used for input
	- Manages control for calling of the string functions, as well as user inpt
	- Contains a goto statement to manage repetitive use
	- Returns 0 at end of runtime

*/
#include <iostream>
#include <string>

using namespace std;

int stringLength(const char * str)
{
	int idx = 0;
	while (true)
	{
		if (str[idx] == '\0'){
			break;
		}
		idx++;
	}

	return idx;
}

void stringNCopy(char * str1, char * str2, int lengthStr2)
{
	if (sizeof(str1) < lengthStr2)
	{
		return;
	}
	for (int i = 0; i < lengthStr2; i++)
	{
		str1[i] = str2[i];
	}
}

void stringAdd(char * str1, char * str2)
{
	int idx = 0, str1Length = 0, str2Length = 0;
	while (true)
	{
		if (str1[str1Length] == 0)
		{
			break;
		}
		str1Length++;
	}
	while (true)
	{
		if (str2[str2Length] == 0)
		{
			break;
		}
		str2Length++;
	}
	for (int i = str1Length; i < (str1Length + str2Length); i++)
	{
		str1[i] = str2[idx++];
	}
}

int stringCompare(char * str1, char * str2)
{
	for (int i = 0; i < sizeof(str1); i++)
	{
		if ((int)str1[i] < (int)str2[i])
		{
			return -1;
		}
		if ((int)str1[i] > (int)str2[i])
		{
			return 1;
		}
	}
	return 0;
}

void cleanString(char * str1)
{
	for (int i = 0; i < 1024; i++)
	{
		str1[i] = 0;
	}
}

int main()
{
	char firstString[1024];
	char secondString[1024];
	
	start:
	cleanString(firstString);
	cleanString(secondString);

	cout << "Enter the following:\n'1' for stringLength\n'2' for stringNCopy\n'3' for stringAdd\n'4' for stringCompare" << endl;
	
	int functionSelect = 0, length2Copy = 0;;
	cin >> functionSelect;
	switch (functionSelect)
	{
		case (1):
			cout << "Please Enter string to get length: " << endl;
			cin.ignore();
			cin.getline(firstString, 1024, '\n');
			cout << stringLength(firstString) << endl;
			break;
		case (2):
			cout << "Please Enter First String: " << endl;
			cin.ignore();
			cin.getline(firstString, 1024, '\n');
			cout << "Please Enter Second String: " << endl;
			cin.getline(secondString, 1024, '\n');
			cout << "Please Enter Number of Characters to Copy: " << endl;
			cin >> length2Copy;
			stringNCopy(firstString, secondString, length2Copy);
			cout << "First String is now: " << firstString << endl;
			break;
		case (3):
			cout << "Please Enter First String: " << endl;
			cin.ignore();
			cin.getline(firstString, 1024, '\n');
			cout << "Please Enter Second String: " << endl;
			cin.getline(secondString, 1024, '\n');
			stringAdd(firstString, secondString);
			cout << "First String is now: " << firstString << endl;
			break;
		case (4):
			cout << "Please Enter First String: " << endl;
			cin.ignore();
			cin.getline(firstString, 1024, '\n');
			cout << "Please Enter Second String: " << endl;
			cin.getline(secondString, 1024, '\n');
			int result = stringCompare(firstString, secondString);
			switch (result)
			{
				case(-1):
				{
					cout << "They are NOT equal" << endl;
					break;
				}
				case(0):
				{
					cout << "They are equal" << endl;
					break;
				}
				case(1):
				{
					cout << "They are NOT equal" << endl;
					break;
				}
			}
			break;
	}
	
	cout << "Would you like to try another or exit? (y/n)" << endl;
	char yninput;
	cin >> yninput;
	switch (yninput)
	{
		case('y') :
		{
			goto start;
		}
		case('n') :
		{
			cout << "Farewell!" << endl;
			break;
		}
	}

	return 0;
}