#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	// Initialize workspace
	double sharePrice, sharesPurchased, totalPurchased, sharesSold, sellPrice, totalSold, commissionTotal;
	double commissionRate = 0.02;

	// Purchasing Program
	cout << "Welcome to Bob's Stock Program" << endl;
	cout << "Please Enter exchange price: $";
	cin >> sharePrice;																							  // retrieve sharePrice
	cout << endl;
	cout << "Please Enter Number of Shares to Purchase: ";
	cin >> sharesPurchased;																						  // retrive number of shares purchased
	cout << endl;
	totalPurchased = (sharesPurchased * sharePrice);															  // determine total purchase cost
	cout << "You purchased: $" << totalPurchased << endl;
	cout << "Applying Program Commission rate: " << (100 * commissionRate) << "%" << endl;
	commissionTotal = commissionRate * totalPurchased;															  // calculate commission cost
	cout << "Commission Paid is: $" << commissionTotal << ". Thank you :)" << endl;

	// Selling Program
	cout << "-- TWO WEEKS LATER --" << endl;
	cout << "Welcome To Bob's Stock Program" << endl;
	cout << "Please Enter Sell Price: $";
	cin >> sellPrice;																							  // retrieve sharePrice
	cout << "Please Enter Number of Shares to Sell: ";
	cin >> sharesSold;																					  		  // retrive number of shares sold
	while (sharesSold < sharesPurchased)
	{
		cout << "Wait a minute! You can't do that ;)";
		cout << "Try another smaller number: ";
		cin >> sharesSold;
	}
	totalSold = (sharesSold * sellPrice);																		  // determine total sell cost
	cout << "Total Volume Sold: $" << totalSold << endl;
	cout << "Commission paid: $" << totalSold * commissionRate << ", @" << (100 * commissionRate) << "%" << endl; // calculate and display commission cost
	cout << "Your leaving balance is: $" << -1 * (totalPurchased - totalSold) << endl;
	cout << "Great doing business with you!" << endl;
	cout << "Zuccarino Enterprises, LLC." << endl;



	return 0;
}