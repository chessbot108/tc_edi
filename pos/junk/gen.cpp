#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
using namespace std;
#define MAXN 1000000
#define NUM_CASES 10

//inclusive
int rand(int a, int b) { return (rand() % (b - a + 1) + a); }

int main() {
	srand(time(NULL));
	ofstream cout;

	for (int i = 1; i <= NUM_CASES; i++)
	{
		string format = ".in";
		string test_data = "";
		int N = 0, M = 0, Q = 0;

		if (i == 1)
			test_data = "9\nAverage 1\nPremins 9\nCosts 2\nOrdering 3\nBooks 3\nABCs 2\nMulitples 5\nTeleport 2\nP=NP 9";
		else if (i == 2 || i == 3)
			N = rand(10, 100);
		else if (i == 8 || i == 10)
			N = MAXN;
		else
			N = rand(MAXN/2, MAXN);

		if (i != 1)
		{
			test_data += to_string(N) + "\n";
			for (int i = 0; i < N; i++)
				test_data += to_string(i) + " " + to_string(rand(1, N)) + (i == N - 1 ? "" : "\n");
		}

		cout.open(to_string(i) + format);
		if (cout)
		{
			cout << test_data << "\n";
			cout.close();
		}
	}
}
