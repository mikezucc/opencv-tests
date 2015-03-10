#include <vector>
#include <iostream>

using namespace std;

template <class passVal> class templateFunctions {
	public:
		passVal val1;
		passVal val2;
		vector <double> templateHistory;

		passVal minimum();
		passVal maximum();
		passVal absolute();
		double total();

		void printMin() { cout << "Minimum: " << minimum() << endl; };
		void printMax() { cout << "Maximum: " << maximum() << endl; };
		void printAbs() { cout << "Absolute: " << absolute() << endl; };
		void printTotal() { cout << "Total: " << total() << endl; };
};

template <class passVal> passVal  templateFunctions<passVal>::minimum()
{
	passVal smallValue;
	smallValue = (val1 > val2 ? val2 : val1);
	return smallValue;
}

template <class passVal> passVal templateFunctions<passVal>::maximum()
{
	passVal bigValue;
	bigValue = (val1 > val2 ? val1 : val2);
	return bigValue;
}

template <class passVal> passVal templateFunctions<passVal>::absolute()
{
	passVal absValue;
	absValue = (val1 >= 0 ? val1 : -val1);
	return absValue;
}

template <class passVal> double templateFunctions<passVal>::total()
{
	double absValue = 0;
	int numToRead = 0;
	cout << "enter number to read: ";
	cin >> numToRead;
	for (int i = 0; (i < numToRead) && (i < templateHistory.size()); i++)
	{
		absValue = absValue + templateHistory[i];
	}
	return absValue;
}

int main() {
	templateFunctions <char> tempFnChar;
	templateFunctions <int> tempFnInt;
	templateFunctions <long> tempFnLong;
	templateFunctions <double> tempFnDouble;
	vector<double> history;

	cout << "Welcome beginning template fun" << endl;
	cout << "Enter a char: ";
	char firstChar;
	cin >> firstChar;
	history.push_back((double)firstChar);
	cout << "Enter another char: ";
	char secondChar;
	cin >> secondChar;
	history.push_back((double)secondChar);
	tempFnChar.val1 = firstChar;
	tempFnChar.val2 = secondChar;
	tempFnChar.templateHistory = history;
	tempFnChar.printMin();
	tempFnChar.printMax();
	tempFnChar.printAbs();
	tempFnChar.printTotal();

	cout << endl << endl;

	cout << "Enter an int: ";
	int firstInt;
	cin >> firstInt;
	history.push_back((double)firstInt);
	cout << "Enter another int: ";
	int secondInt;
	cin >> secondInt;
	history.push_back((double)secondInt);
	tempFnInt.val1 = firstInt;
	tempFnInt.val2 = secondInt;
	tempFnInt.templateHistory = history;
	tempFnInt.printMin();
	tempFnInt.printMax();
	tempFnInt.printAbs();
	tempFnInt.printTotal();

	cout << endl << endl;

	cout << "Enter a long: ";
	long firstLong;
	cin >> firstLong;
	history.push_back((double)firstLong);
	cout << "Enter another long: ";
	long secondLong;
	cin >> secondLong;
	history.push_back((double)secondLong);
	tempFnLong.val1 = firstLong;
	tempFnLong.val2 = secondLong;
	tempFnLong.templateHistory = history;
	tempFnLong.printMin();
	tempFnLong.printMax();
	tempFnLong.printAbs();
	tempFnLong.printTotal();

	cout << endl << endl;

	cout << "Enter a double: ";
	double firstDouble;
	cin >> firstDouble;
	history.push_back((double)firstDouble);
	cout << "Enter another double: ";
	double secondDouble;
	cin >> secondDouble;
	history.push_back((double)secondDouble);
	tempFnDouble.val1 = firstDouble;
	tempFnDouble.val2 = secondDouble;
	tempFnDouble.templateHistory = history;
	tempFnDouble.printMin();
	tempFnDouble.printMax();
	tempFnDouble.printAbs();
	tempFnDouble.printTotal();

	cout << endl << endl;

	system("pause");

	return 0;
}