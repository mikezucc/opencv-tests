/*
Author: Michael Zuccarino
Description: This program uses a While Loop to calculcate a salary that compounds daily by 1 cent. User provides Number of days.
*/

#include <iostream>
#include <iomanip>

using namespace std;

int MainWhile()
{
	int userInputDays, dayN = 1;
	float payValue = 0.00, salaryTotal = 0.00;

	cout << "Author: Michael Zuccarino" << endl << "Description: This program uses a While Loop to calculcate a salary that compounds daily by 1 cent. User provides Number of days." << endl;

	cout << "Hello! Please enter in number of days: ";
	cin >> userInputDays;

	while (1)
	{
		if (userInputDays < 1)
		{
			cout << "You can not enter less than 1 day!" << endl;
			cout << "Please enter in number of days : ";
			cin >> userInputDays;
			continue;
		}
		while (dayN <= userInputDays)
		{
			payValue += 0.01;
			salaryTotal += payValue;
			cout << fixed << setprecision(2);
			cout << "On day " << dayN << ", person was paid $" << salaryTotal << endl;
			dayN++;
		}
		break;
	}

	return 0;
}