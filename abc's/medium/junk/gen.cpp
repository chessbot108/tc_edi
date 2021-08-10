#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
using namespace std;
#define MAXN 100000
#define NUM_CASES 10

//inclusive
int rand(int a, int b)
{
	return (rand() % (b - a + 1) + a);
}

int main() {
	srand(time(NULL));
	ofstream cout;

	for (int i = 1; i <= NUM_CASES; i++)
	{
		string format = ".in";
		string test_data = "";
		int N = 0, K = 0;

		if (i == 1)
			test_data = "9 3\nABBCCCBAB";
		else if (i == 2 || i == 3)
		{
			N = rand(20, 100);
			K = rand(2, N);
		}
		else if (i == 8 || i == 10)
		{
			N = MAXN;
			K = rand(10000, 30000);
		}
		else
		{
			N = rand(90000, MAXN);
			K = rand(10000, 20000);
		}

		if (i != 1)
		{
			test_data += to_string(N) + " " + to_string(K) + "\n";
			string letters[3] = { "A", "B", "C" };
			for (int i = 0; i < N; i++)
				test_data += letters[rand(0, 2)];
		}

		cout.open(to_string(i) + format);
		if (cout)
		{
			cout << test_data << "\n";
			cout.close();
		}
	}
}
