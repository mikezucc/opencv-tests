#include <iostream>
using namespace std;

int main()
{
	cout << "hue hue hue" << endl;
	int x[] = { 3, 8, 2, 4, 9, 1, 0, 0, 0, 0 };
	int n = 6;
	int m = 0;
	int above = 0, below = 0;
	double median = 0;
	int sortList[10] = { -1 };
	for (int idx = 0; idx < n; idx++)
	{
		sortList[x[idx]] = 1;
	}
	int newList[10] = { -1 };
	int separate = 0;
	for (int idx = 0; idx < n; idx++)
	{
		if (sortList[idx] != 0)
		{
			newList[separate++] = idx;
		}
	}
	for (int i = 0; i < n + 30; i++)
	{
		if (newList[i] <= 0) continue;
		m = x[i];
		if (m < newList[i])
		{
			above++;
		}
		else
		{
			below++;
		}
		if ((above + below) == floor(n / 2))
		{
			if ((n % 2) != 0)
			{
				// its odd
				cout << "its even" << endl;
				median = m;
			}
			else
			{
				cout << "its odd" << endl;
				median = (double)(x[i] + x[i - 1]) / 2;
			}
			break;
		}
	}
	for (int k = 0; k < 10; k++)
	{
		cout << "k: " << k << ", " << newList[k] << endl;
	}
	/*
	for (int i = 0; i < n + 30; i++)
	{
		if (sortList[i] > 0) continue;
		if (m < sortList[i])
		{
			above++;
		}
		else
		{
			below++;
		}
		if ((above + below) == floor(n / 2))
		{
			median = m;
			break;
		}
		m = x[i];

	}*/
	return 0;
}