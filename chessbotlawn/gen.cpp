#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
using namespace std;
#define MAXN 1000
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
		int N = 0, M = 0, Q = 0;

		if (i == 1)
			test_data = "4 5 3\n2 3 1 6 2\n3 2 1 5 3\n5 6 2 3 1\n9 6 3 7 2\n4 2\n1 3\n4 3";
		else if (i == 2 || i == 3)
		{
			N = rand(5, 20);
			M = rand(5, 20);
			Q = rand(5, 10);
		}
		else if (i == 8 || i == 10)
		{
			N = MAXN;
			M = MAXN;
			Q = MAXN;
		}
		else
		{
			N = rand(750, 1000);
			M = rand(750, 1000);
			Q = rand(500, 1000);
		}

		if (i != 1)
		{
			test_data += to_string(N) + " " + to_string(M) + " " + to_string(Q) + "\n";
			for (int i = 0; i < N; i++)
				for (int j = 0; j < M; j++)
					test_data += to_string(rand(0, 1e9)) + (j == M - 1 ? "\n" : " ");

			for (int q = 0; q < Q; q++)
			{
				test_data += to_string(rand(1, N)) + " " + to_string(rand(1, M)) + (q != Q - 1 ? "\n" : "");
			}
		}

		cout.open(to_string(i) + format);
		if (cout)
		{
			cout << test_data << "\n";
			cout.close();
		}
	}
}