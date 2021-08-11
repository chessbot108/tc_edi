#include<bits/stdc++.h>
using namespace std;

// random number from 0 to 2^64-1 (be careful about it taking unsigned int / long long!)
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// random number from a to b
long long randint(long long a, long long b)
{
	return rng() % (b - a + 1) + a;
}


// put constraints under here
const int maxn = 2000;
int c[maxn][maxn]; // colors
int b[maxn][maxn]; // converted field
int hist[maxn]; // histogram of 1's
int next_smol[maxn], prev_smol[maxn]; // index of next or prev strictly smaller element
int t, n, largest_rect;



// takes a few seconds
void generate_test_small()
{
	int tot_sum = 0;
	vector<string> test_cases;

	while (1) 
	{
		int mx = randint(2, 3); // rectangles larger when mx is small
		int n = randint(1, 10);

		if (tot_sum + n * n > maxn * maxn) break; // exceed max sum of n^2

		tot_sum += n * n;

		test_cases.push_back(to_string(n) + "\n");
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				test_cases.back() += to_string(randint(1, mx)) + ' ';
			}
			test_cases.back() += '\n';
		}
	}

	cout << test_cases.size() << '\n';
	for (auto& test_case : test_cases) 
	{
		cout << test_case;
	}
}

// takes a few seconds
void generate_test_max()
{
	cout << 1 << '\n';

	cout << maxn << '\n';

	vector<vector<int>> a(maxn, vector<int>(maxn));

	for (int i = 0; i < maxn; i++)
	{
		for (int j = 0; j < maxn; j++)
		{
			a[i][j] = randint(1, 2);  // rectangles larger when only 2 values
		}
	}

	// answer for large n seems to always = n (just a row)
	// so, we create a special rectangle with larger area
	// we need to create a few otherwise there exists only a single large rectangle with area larger than n (heuristic might find it)
	
	for (int big_recs = 0; big_recs < 100; big_recs++)
	{
		// average side length is like 1/4 original square?
		int i, j, i2, j2;
		i = randint(0, maxn - 1);
		i2 = randint(i, maxn - 1);
		j = randint(0, maxn - 1);
		j2 = randint(j, maxn - 1);

		vector<int> row(j2 - j + 1); // random row for the rectangle
		for (auto& i : row)
		{
			i = randint(1, 2);
		}

		// place in the rectangle
		for (int i3 = i; i3 <= i2; i3++)
		{
			for (int j3 = j; j3 <= j2; j3++)
			{
				a[i3][j3] = row[j3 - j];
			}
		}
	}

	for (auto& row : a)
	{
		for (auto& el : row)
		{
			cout << el << ' ';
		}
		cout << '\n';
	}
}

// 5% of n^2 is small tests then rest 95% is one big test
void generate_test()
{
	int tot_sum = 0;
	vector<string> test_cases;

	while (1)
	{
		int mx = randint(2, 3); // rectangles larger when mx is small
		int n = randint(1, 10);

		if (tot_sum + n * n > (maxn * maxn)/20) break; // exceed max sum of n^2

		tot_sum += n * n;

		test_cases.push_back(to_string(n) + "\n");
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				test_cases.back() += to_string(randint(1, mx)) + ' ';
			}
			test_cases.back() += '\n';
		}
	}

	// print test cases to stdout (redirected to file)
	cout << test_cases.size() + 1 << '\n'; // + 1 cuz last test is large test (created right after)
	for (auto& test_case : test_cases)
	{
		cout << test_case;
	}

	int n = sqrt(maxn * maxn - tot_sum);

	vector<vector<int>> a(n, vector<int>(n));

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			a[i][j] = randint(1, 2);  // rectangles larger when only 2 values
		}
	}

	// answer for large n seems to always = n (just a row)
	// so, we create a special rectangle with larger area
	// we need to create a few otherwise there exists only a single large rectangle with area larger than n (heuristic might find it)

	// if too many big recs, then heuristic of just finding components of rectangles could pass 
	// the grid would just be a combination of big rectangles rather than a few big rectangles
	// that intersect with a decent amount of random 1's and 2's
	for (int big_recs = 0; big_recs < 20; big_recs++) 
	{
		// average side length is like 1/4 original square?
		int i, j, i2, j2;
		i = randint(0, n - 1);
		i2 = randint(i, n - 1);
		j = randint(0, n - 1);
		j2 = randint(j, n - 1);

		vector<int> row(j2 - j + 1); // random row for the rectangle
		for (auto& i : row)
		{
			i = randint(1, 2);
		}

		// place in the rectangle
		for (int i3 = i; i3 <= i2; i3++)
		{
			for (int j3 = j; j3 <= j2; j3++)
			{
				a[i3][j3] = row[j3 - j];
			}
		}
	}

	// print test case
	cout << n << '\n';

	for (auto& row : a)
	{
		for (auto& el : row)
		{
			cout << el << ' ';
		}
		cout << '\n';
	}
}

// read test case from stdin and print solution to stdout
void model_sol()
{
	// O(n)

	cin.tie(0)->sync_with_stdio(0);

	cin >> t;

	while (t--)
	{
		cin >> n;

		// read in c
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cin >> c[i][j];
			}
		}

		// create b
		for (int i = 0; i < n - 1; i++)
		{
			for (int j = 0; j < n; j++)
			{
				b[i][j] = c[i][j] == c[i + 1][j];
			}
		}

		// find largest rectangle with width >= 2 
		fill(hist, hist + n, 0); // set to 0
		largest_rect = 0;

		for (int i = 0; i < n - 1; i++)
		{
			// update histogram
			for (int j = 0; j < n; j++)
			{
				if (b[i][j])
				{
					hist[j]++;
				}
				else
				{
					hist[j] = 0;
				}
			}

			// find next_smol and prev_smol
			stack<int> s; // stores indices
			for (int j = 0; j < n; j++)
			{
				while (!s.empty() and hist[s.top()] > hist[j])
				{
					next_smol[s.top()] = j;
					s.pop();
				}

				s.push(j);
			}
			while (!s.empty())
			{
				next_smol[s.top()] = n; // assume border/edge is the bound
				s.pop();
			}

			for (int j = n - 1; j >= 0; j--)
			{
				while (!s.empty() and hist[s.top()] > hist[j])
				{
					prev_smol[s.top()] = j;
					s.pop();
				}

				s.push(j);
			}
			while (!s.empty())
			{
				prev_smol[s.top()] = -1; // assume border/edge is the bound
				s.pop();
			}

			// find largest rect with base at row i
			for (int j = 0; j < n; j++)
			{
				// (hist[j]+1) because we convert to true area in c
				largest_rect = max(largest_rect, (hist[j] + 1) * (next_smol[j] - prev_smol[j] - 1));
			}
		}


		cout << max(n, largest_rect) << '\n';
	}
}

// for checking tests look right
void read_and_print_file(string directory, string name)
{
	freopen((directory + name).c_str(), "r", stdin);

	string a;
	while (getline(cin, a))
	{
		cout << a << '\n';
	}

	exit(0);
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int num_tests = 10;

	string directory = R"(C:\Users\elija\Desktop\CODING\Competitive Programming Problemsetting\TeamsCode\2021 Summer\Kanna's Field of Flowers\Tests\)";

	//read_and_print_file(directory, "2.in"); 

	// I don't want non n^2 to get more than just this first test case
	for (int test_num = 1; test_num <= 1; test_num++)
	{
		// generate the input
		freopen((directory + to_string(test_num) + ".in").c_str(), "w", stdout);
		generate_test_small();
		cerr << "Generated input for test " << test_num << '\n';

		// generate the output
		freopen((directory + to_string(test_num) + ".in").c_str(), "r", stdin);
		freopen((directory + to_string(test_num) + ".out").c_str(), "w", stdout);
		model_sol();
		cerr << "Generated output for test " << test_num << '\n';
	}

	// last 9 are all large tests (5% small to create edge cases) so >= n^3 fails
	for (int test_num = 2; test_num <= num_tests; test_num++)
	{
		// generate the input
		freopen((directory + to_string(test_num) + ".in").c_str(), "w", stdout);
		generate_test();
		cerr << "Generated input for test " << test_num << '\n';

		// generate the output
		freopen((directory + to_string(test_num) + ".in").c_str(), "r", stdin);
		freopen((directory + to_string(test_num) + ".out").c_str(), "w", stdout);
		model_sol();
		cerr << "Generated output for test " << test_num << '\n';
	}

	/*// last 9 are all max tests so >= n^3 fails
	for (int test_num = 2; test_num <= num_tests; test_num++)
	{
		// generate the input
		freopen((directory + to_string(test_num) + ".in").c_str(), "w", stdout);
		generate_test_max();
		cerr << "Generated input for test " << test_num << '\n';

		// generate the output
		freopen((directory + to_string(test_num) + ".in").c_str(), "r", stdin);
		freopen((directory + to_string(test_num) + ".out").c_str(), "w", stdout);
		model_sol();
		cerr << "Generated output for test " << test_num << '\n';
	}*/

	cerr << "Cases generated!\n";
}