/*
Speed of Sound Distance to Time convert
Written by: Michael Zuccarino
*/

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main()
{
	string userInputMedium;
	const float airSpeed = 1100, waterSpeed = 4900, steelSpeed = 16400;
	float userInputDistance, timeTraveled;

	cout << "Welcome to the Speed of Sound Time Traveled Calculator!" << endl;
	cout << "Please select a medium: air, water, or steel: ";
	cin >> userInputMedium;
	cout << "Please select a distance: ";
	cin >> setprecision(4) >> fixed >> userInputDistance;
	while (1)
	{
		if (userInputDistance > 0)
		{
			if (userInputMedium == "air")
			{
				timeTraveled = (userInputDistance / airSpeed);
			}
			else if (userInputMedium == "water")
			{
				timeTraveled = (userInputDistance / waterSpeed);
			}
			else if (userInputMedium == "steel")
			{
				timeTraveled = (userInputDistance / steelSpeed);
			}
			cout << "Time traveled: " << setprecision(4) << fixed << timeTraveled << "s";
			break;
		}
		else
		{
			cout << "This is not a valid distance." << endl;
			cout << "Please select a distance: ";
			cin >> setprecision(4) >> fixed >> userInputDistance;
		}
	}

	return 0;
}