/*
Author:Michael Zuccarino
This program is designed for the restaurant Bob's Burgers, performing the operations of a cashier.
It will generate a receipt based off of the entered meal amount, tax and entered tip.
*/

#include <iostream>
#include <iomanip>
#include <fstream>

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
	cout << setw(26) << setfill('.') << fixed << setprecision(2) << "$" << mealTot << endl;
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
	cout << "\"Printing\" Receipt now..." << endl;

	ofstream receiptFile;
	receiptFile.open("receipt.txt", ios::out);
	receiptFile << "Author:Michael Zuccarino" << endl;
	receiptFile << "This program is designed for the restaurant Bob's Burgers, performing the operations of a cashier." << endl;
	receiptFile << "It will generate a receipt based off of the entered meal amount, tax and entered tip." << endl << endl;
	receiptFile << setw(30) << setfill(' ') << "Thank You for Eating at Bob\'s Burgers" << endl;
	receiptFile << setw(30) << setfill(' ') << "123 McCurrahee Lane, 555-4334" << endl;
	receiptFile << "Your meal total" << setw(14) << setfill('_') << "$" << fixed << setprecision(2) << mealTot << endl;
	receiptFile << "Total with tax" << setw(15) << setfill('_') << "$" << fixed << setprecision(2) << mealWithTax << endl;
	receiptFile << "Total with tip" << setw(15) << setfill('_') << "$" << fixed << setprecision(2) << mealWithTip << endl;
	receiptFile << setw(28) << setfill(' ') << "TOTAL CHARGED: " << "$" << fixed << setprecision(2) << mealWithTip << endl;
	receiptFile << setw(30) << setfill(' ') << "Please come back :)" << endl;
	receiptFile.close();

	cout << "Please eat with us again!" << endl;
	return 0;
}