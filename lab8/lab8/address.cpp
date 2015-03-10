#include <iostream>

using namespace std;

void rotatethis(int *num1, int *num2)
{
	int *ptr1, *ptr2;

	ptr1 = num1;
	ptr2 = num2;
	*ptr2 = *ptr1;
}

int main()
{
	int alpha = 2, beta = 3;
	rotatethis(&alpha, &beta);
	cout << alpha << "  " << beta;
	return 0;
}