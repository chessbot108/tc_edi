#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <vector>
#include <random>
#include <chrono>
using namespace std;
#define MAXN 100000
#define MAXK 1000000000
#define NUM_CASES 10
#define WALL_PROB 10 //out of 100
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

//inclusive
int rand(int a, int b)
{
	return (rng() % (b - a + 1) + a);
}

int main() {
	srand(time(NULL));
	ofstream cout;

	for (int i = 1; i <= NUM_CASES; i++)
	{
		string format = ".in";
		string test_data = "";
		int N = 0, M = 0, K = 0;

		if (i == 1)
			test_data = "4 6 9\n1 2 4 2\n1 3 8 1\n1 4 8 4\n2 3 3 2\n2 4 7 2\n3 4 2 3";
		else if (i == 2 || i == 3)
		{
			N = rand(10, 50);
			M = rand(N - 1, 50);
			K = rand(2500*M, 10000*M);
		}
		else if (i == 8 || i == 10)
		{
			N = MAXN;
			M = MAXN;
			K = rand(500000000, MAXK);
		}
		else
		{
			N = rand(30000, MAXN);
			M = rand(N - 1, MAXN);
			K = rand(2500*M, 10000*M);
		}

		vector<pair<int, int> > tel_in, tel_out;
		if (i != 1)
		{
			test_data += to_string(N) + " " + to_string(M) + " " + to_string(K) + "\n";
			for (int i = 0; i < M; i++)
			{
				int a = rand(1, N);
				int b = rand(1, N);
				while (b == a) b = rand(1, N);

				int w = rand(1, 10000);
				int f = rand(1, 1000000000);
				
				test_data += to_string(a) + " " + to_string(b) + " " + to_string(w) + " " + to_string(f);
				if (i != M - 1) test_data += "\n";
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