#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <vector>
#include <random>
#include <map>
#include <set>
#include <chrono>
using namespace std;
#define MAXN 1000
#define MAXK 400000
#define NUM_CASES 10
#define WALL_PROB 10 //out of 100
#define pii pair<int, int>
map<pii, int> r, group;
map<pii, pii> par;
set<pii> taken;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

pii find(pii n)
{
	return par[n] = (par[n] == n ? n : par[n] = find(par[n]));
}

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
			test_data = "5 5 3\n..#..\n.#...\n...#.\n.##..\n#....\n4 1 5 2\n5 2 4 4\n1 2 5 2";
		else if (i == 2 || i == 3)
		{
			N = rand(10, 50);
			M = rand(10, 50);
			K = rand(20, 40);
		}
		else if (i == 8 || i == 10)
		{
			N = MAXN;
			M = MAXN;
			K = MAXK;
		}
		else
		{
			N = rand(700, MAXN);
			M = rand(700, MAXN);
			K = rand(300000, min(N*M - 15000, MAXK));
		}

		vector<pair<int, int> > tel_in, tel_out;
		if (i != 1)
		{
			test_data += to_string(N) + " " + to_string(M) + " " + to_string(K) + "\n";

			int cx = 0;
			int cy = 0;
			taken.insert({ cx, cy });
			//create a path
			for (int i = 0; i < M / 2; i++)
			{
				cy++;
				taken.insert({ cx, cy });
			}
			for (int i = 0; i < N / 2; i++)
			{
				cx++;
				taken.insert({ cx, cy });
			}
			while (cy > 0)
			{
				cy--;
				taken.insert({ cx, cy });
			}
			while (cx < N - 1)
			{
				cx++;
				taken.insert({ cx, cy });
			}
			while (cy < M - 1)
			{
				cy++;
				taken.insert({ cx, cy });
			}

			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < M; j++)
				{
					par[{i, j}] = { i, j };
					group[{ i, j }] = MAXN * i + j;
					if (taken.count(make_pair(i, j)))
					{
						test_data += ".";
						tel_out.push_back({ i + 1, j + 1});
					}
					else if (rand(1, 100) <= WALL_PROB) test_data += "#";
					else
					{
						test_data += ".";
						tel_in.push_back({ i + 1, j + 1 });
						tel_out.push_back({ i + 1, j + 1 });
					}
				}
				test_data += "\n";
			}

			shuffle(tel_in.begin(), tel_in.end(), rng);

			for (int i = 0; i < K; i++)
			{
				test_data += to_string(tel_in[i].first) + " " + to_string(tel_out[i].second) + " "; //tel start
				if (i < 3*K / 4)
				{
					test_data += to_string(tel_in[i + 1].first) + " " + to_string(tel_out[i + 1].second) + "\n";
					par[tel_in[i]] = par[tel_in[i + 1]];
				}
				else  
				{
					pii out = tel_out[rand(0, tel_out.size() - 1)];
					while (group[find(out)] == group[find(tel_in[i])])
						out = tel_out[rand(0, tel_out.size() - 1)];

					test_data += to_string(out.first) + " " + to_string(out.second);
					if (i != K - 1) test_data += "\n";
					par[tel_in[i]] = out;
				}
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