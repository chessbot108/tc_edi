#include<bits/stdc++.h>
using namespace std;

// random number from 0 to 2^64-1 (be careful about it taking unsigned int / long long!)
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// random number from a to b
long long randint(long long a, long long b)
{
	return uniform_int_distribution<long long>(a, b)(rng);
}


// put constraints under here
int maxt = 1e4, maxa = 1e5, maxn = 1e5, maxk = 10;


// print test case to stdout
void generate_test(int test_num) 
{
	int tot_n = 0;
	vector<string> test_cases;

	while (tot_n != maxn)
	{
		int n = randint(1, 10);
		bool all_1s = randint(1, 20) == 1;
		
		if (test_num == 1)
		{
			if (n + tot_n > maxn)
			{
				n = maxn - tot_n; // while loop condition will be met after this test is made
				// be careful is n must be > 1 since this can create n = 1
			}
		}
		else
		{
			if (n + tot_n > maxn / 20)
			{
				n = maxn - tot_n; // while loop condition will be met after this test is made
				all_1s = 0;
			}
		}

		tot_n += n;


		test_cases.push_back(to_string(n) + ' ' + to_string(randint(2, 10)) + '\n');

		for (int i = 0; i < n; i++)
		{
			if (all_1s)
			{
				test_cases.back() += "1 ";
			}
			else
			{
				test_cases.back() += to_string(randint(1,maxa)) + ' ';
			}
		}
		test_cases.back() += '\n';
	}

	cout << test_cases.size() << '\n';
	for (auto& test_case : test_cases)
	{
		cout << test_case;
	}
}

// read test case from stdin and print solution to stdout
void model_sol() 
{
	cin.tie(0)->sync_with_stdio(0);

	int t, k, n, mx;

	cin >> t;

	while (t--)
	{
		cin >> n >> k;

		mx = 0;
		for (int i = 0; i < n; i++)
		{
			int a; cin >> a;

			mx = max(mx, a);
		}

		if (mx == 1)
		{
			cout << k * mx << '\n';
		}
		else
		{
			cout << k * mx - 1 << '\n';
		}
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

	string directory = R"(C:\Users\elija\Desktop\CODING\Competitive Programming Problemsetting\TeamsCode\2021 Summer\Shion's Feast\Tests\)";

	// read_and_print_file(directory, "2.in");

	// first test is all small test cases, then rest are 5% small 95% one large test case
	for (int test_num = 1; test_num <= num_tests; test_num++) 
	{
		freopen((directory + to_string(test_num) + ".in").c_str(), "w", stdout);
		generate_test(test_num);
		cerr << "Generated input for test " << test_num << '\n';

		freopen((directory + to_string(test_num) + ".in").c_str(), "r", stdin);
		freopen((directory + to_string(test_num) + ".out").c_str(), "w", stdout);
		model_sol();
		cerr << "Generated output for test " << test_num << '\n';
	}

	cerr << "Tests generated!\n";
}