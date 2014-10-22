#include <iostream>
#include <iomanip>

using namespace std;

int main() {

	gameStart:
	double numP, numN, numD, numQ, totalVal;

	cout << "Welcome to the spooky coin game" << endl;
	cout << "Enter number of pennies: ";
	cin >> numP;
	bool isValid = false;
	while (!isValid)
	{
		if (((100 - numP) > 1) && (numP >= 0))
		{
			isValid = true;
			break;
		}
		else
		{
			cout << "Please enter value 0-99: ";
			cin >> numP;
		}
	}
	cout << "Enter number of nickels: ";
	cin >> numN;
	isValid = false;
	while (!isValid)
	{
		if (((100 - numN) > 1) && (numN >= 0))
		{
			isValid = true;
			break;
		}
		else
		{
			cout << "Please enter value 0-19: ";
			cin >> numN;
		}
	}
	cout << "Enter number of dimes: ";
	cin >> numD;
	isValid = false;
	while (!isValid)
	{
		if (((100 - numD) > 1) && (numD >= 0))
		{
			isValid = true;
			break;
		}
		else
		{
			cout << "Please enter value 0-9: ";
			cin >> numD;
		}
	}
	cout << "Enter number of quarters: ";
	cin >> numQ;
	isValid = false;
	while (!isValid)
	{
		if (((100 - numQ) > 1) && (numQ >= 0))
		{
			isValid = true;
			break;
		}
		else
		{
			cout << "Please enter value 0-3: ";
			cin >> numQ;
		}
	}
	totalVal = numP + (numN * 5) + (numD * 10) + (numQ*25);
	if (totalVal == 100)
	{
		cout << "Congrats! It adds up! ";
		cout << "Press y to play again: ";
		char received;
		cin >> received;
		if (received == 'y')
		{
			goto gameStart;
		}
		else
		{
			cout << "Goodbye" << endl;
			return 0;
		}
	}
	else
	{
		cout << "Oops that only totals to: $" << (totalVal * 0.01) << endl;
		cout << "Press y to play again: ";
		char received;
		cin >> received;
		if (received == 'y')
		{
			goto gameStart;
		}
		else
		{
			cout << "Goodbye" << endl;
			return 0;
		}
	}



}