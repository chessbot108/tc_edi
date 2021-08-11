#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
using namespace std;
#define NUM_TESTS 10
#define MAXN 1000
/*
* first 3 cases pretty easy
* next 7
*/

int main()
{
	ofstream cout;
	string format = ".in";
	srand(time(NULL));

	for (int i = 1; i <= NUM_TESTS; i++)
	{
		cout.open(to_string(i) + format);

		if (cout)
		{
			string test_data = "";
			int T = 0;

			if (i == 1) //sample case
				test_data = "6\n8 2 3 9 10 3";
			else if (i == 2 || i == 3) //easy tests
				T = rand() % 46 + 5;
			else if (i == 8 || i == 10) //hardest
				T = MAXN;
			else //pretty hard
				T = rand() % 500 + 501;
			if (i != 1)
			{
				test_data += to_string(T) + "\n";
				for (int j = 0; j < T; j++)
				{
					test_data += to_string(rand() % 100 + 1);
					if (j != T - 1) test_data += " ";
				}
			}

			cout << test_data << "\n";
			cout.close();
		}
	}
	return 0;
}