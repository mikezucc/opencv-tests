/*
Bob's Burgers Receipt Program
Author: Michael Zuccarino
Purpose: Program to generate a receipt factoring in the initial meal cost, tax, and an automatically or manually entered tip.

Constants:
	Tax: 6.75%
	Tip (auto): 15%

PreProcessor Headers used: 
	iostream (cout, cin)
	iomanip (setfill(), fixed, setprecision)
*/

#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	// Initialize workspace
	double mealTot, mealWithTax, mealWithTip;
	double taxRate = 0.0675;
	double kTipRate = 1.15;

	// Receipt Header
	cout << "Thank You for Eating at Bob\'s Burgers" << endl;

	// Meal Total and Tax Calculation
	cout << "Please enter the meal total: $";
	cin >> mealTot;
	cout << "Meal Total: ";
	cout << setw(26) << std::setfill('.') << std::fixed << std::setprecision(2) << "$" <<mealTot << endl;
	mealWithTax = (mealTot * taxRate) + mealTot;
	cout << "Applying Tax rate (@6.75% -> &" << (mealTot * taxRate) << "): " << "$" << mealWithTax << endl; \

	// Manual or Automatic Tip Calculation
	bool hasEnteredValid = false;
	cout << "Press 'm' to manually enter tip," << endl;
	cout << " or 'a' to automatically compute it : ";
	while (!hasEnteredValid)
	{
		char retKey;
		cin >> retKey;
		switch (retKey) {
		case 'a':
			mealWithTip = mealWithTax * kTipRate;
			hasEnteredValid = true;
			break;
		case 'm':
			double cTipAmount;
			cout << "Cool, enter in custom tip amount: $";
			cin >> cTipAmount;
			mealWithTip = mealWithTax + cTipAmount;
			cout << "New Meal Total with Tip: " << setw(11) << std::setfill('.') << "$" << mealWithTip << endl;
			hasEnteredValid = true;
			break;
		default:
			cout << "Please enter a valid key :[" << endl;
		}
	}

	// Display Gran Total and Receipt Footer
	cout << "Your Grand Total is: " << setw(15) << std::setfill('.') << "$" << mealWithTip << endl;
	cout << "Please eat with us again!" << endl;
	return 0;
}
