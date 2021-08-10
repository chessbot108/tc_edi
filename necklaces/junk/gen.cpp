#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;
#define MAXN 400000
#define NUM_CASES 10
#define R_INT 50
int a[MAXN - 1];
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

//inclusive
int rand(int a, int b)
{
	return (rng() % (b - a + 1) + a);
}

int main() {
	srand(time(NULL));
	unsigned seed = chrono::system_clock::now().time_since_epoch().count();
	ofstream cout;

	for (int i = 1; i <= NUM_CASES; i++)
	{
		for (int i = 0; i < MAXN - 1; i++)
			a[i] = i + 1;
		string format = ".in";
		string test_data = "";
		int N = 0, M = 0;

		if (i == 1)
			test_data = "6 6\nR 2\nR 4\nQ 1\nR 1\nQ 6\nQ 2";
		else if (i == 2 || i == 3)
		{
			N = rand(10, 100);
			M = rand(10, 99);
		}
		else if (i == 8 || i == 10)
		{
			N = MAXN;
			M = MAXN - 1;
		}
		else
		{
			N = rand(100000, MAXN);
			M = rand(100000, N - 1);
		}

		if (i != 1)
		{
			shuffle(a, a + N - 1, rng);
			int inds[2] = { 1, N - 1 };
			int ind = 0; //ind for where on random array we go to remove

			test_data += to_string(N) + " " + to_string(M) + "\n";
			for (int i = 0; i < M; i++)
			{
				string chars[2] = { "R", "Q" };
				string type = (i % R_INT == R_INT - 1 ? chars[0] : chars[1]);
				
				int v = 0;
				if (type == "R")
					if (rand(0, 1) == 0) v = inds[0]++;
					else v = inds[1]--;
				else v = rand(1, N);
				test_data += type + " " + to_string(v) + (i == M - 1 ? "" : "\n");
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
