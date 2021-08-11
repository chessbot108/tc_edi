#include<bits/stdc++.h>
using namespace std;

bool fail = 0;

// random number from 0 to 2^64-1 (be careful about it taking unsigned int / long long!)
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// random number from a to b
long long randint(long long a, long long b)
{
	return uniform_int_distribution<long long>(a, b)(rng);
}


// put constraints under here
const int maxn = 2000;
int c[maxn][maxn]; // colors
int b[maxn][maxn]; // converted field
int hist[maxn]; // histogram of 1's
int next_smol[maxn], prev_smol[maxn]; // index of next or prev strictly smaller element
int t, n, largest_rect, ans;

int largest_ans = 0;

// print test case to stdout
void generate_test()
{
	int test_cases = 80;
	
	cout << test_cases << '\n';

	for (int n = 1; n <= test_cases; n++)
	{
		int mx = randint(1, 2); // rectangles larger when mx is small
		if (n == test_cases) {
			mx = 1e6; // still want to test max values tho just in case
		}

		cout << n << '\n';

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cout << randint(0, mx) << ' ';
			}
			cout << '\n';
		}
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
		largest_ans = max(largest_ans, max(n, largest_rect));
	}
}

// read test case from stin and print solution to stdout
void brute_sol()
{
	// O(n^6/constant)

	cin.tie(0)->sync_with_stdio(0);

	cin >> t;

	while (t--)
	{
		ans = 0;

		cin >> n;

		// read in c
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cin >> c[i][j];
			}
		}

		// check retangle top left = (i,j) bottom right = (i2,j2)
		for (int i = 0; i < n; i++)
		{
			for (int i2 = i; i2 < n; i2++)
			{
				for (int j = 0; j < n; j++)
				{
					for (int j2 = j; j2 < n; j2++)
					{
						bool all_rows_same = 1;

						for (int i3 = i + 1; i3 <= i2; i3++)
						{
							for (int j3 = j; j3 <= j2; j3++)
							{
								if (c[i][j3] != c[i3][j3])
								{
									all_rows_same = 0;
									goto stopped_checking;
								}
							}
						}

					stopped_checking:
						if (all_rows_same)
						{
							ans = max(ans, (i2 - i + 1) * (j2 - j + 1));
						}
					}
				}
			}
		}

		cout << ans << '\n';
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

	string directory = R"(C:\Users\elija\Desktop\CODING\Competitive Programming Problemsetting\TeamsCode\2021 Summer\Kanna's Field of Flowers\Checking Model with Brute Tests\)";

	//read_and_print_file(directory, "1brute.out"); 

	for (int test_num = 1; test_num <= num_tests; test_num++)
	{
		// generate the input
		freopen((directory + to_string(test_num) + ".in").c_str(), "w", stdout);
		generate_test();

		// generate the output for the model
		freopen((directory + to_string(test_num) + ".in").c_str(), "r", stdin);
		freopen((directory + to_string(test_num) + "model" + ".out").c_str(), "w", stdout);
		model_sol();
		fflush(stdout); // because otherwise when reading output for model/brute last line might still be in the buffer
		// generate the output for the brute
		freopen((directory + to_string(test_num) + ".in").c_str(), "r", stdin);
		freopen((directory + to_string(test_num) + "brute" + ".out").c_str(), "w", stdout);
		brute_sol();
		fflush(stdout); // because otherwise when reading output for model/brute last line might still be in the buffer

		vector<string> model_output, brute_output;
		string temp;

		// read output for the model
		ifstream fin((directory + to_string(test_num) + "model" + ".out").c_str());
		while (fin >> temp)
		{
			model_output.push_back(temp);
		}
		fin.close();
		// read output for the brute
		fin.open((directory + to_string(test_num) + "brute" + ".out").c_str());
		while (fin >> temp)
		{
			brute_output.push_back(temp);
		}
		fin.close();

		// compare outputs
		cerr << "model and brute sizes: " << model_output.size() << ' ' << brute_output.size() << '\n';
		for (int i = 0; i < min(model_output.size(), brute_output.size()); i++)
		{
			
			if (model_output[i] != brute_output[i])
			{
				cerr << "The model and the brute do not agree!\n";
				cerr << "Differ Test: " << test_num << '\n';
				cerr << "Differ Index: " << i << '\n';
				cerr << "Differ Values: " << model_output[i] << ' ' << brute_output[i] << '\n';
				fail = 1;
			}
		}
	}

	if (!fail) {
		cerr << "The model and the brute agree!\n";
	}

	cerr << "Largest Ans: " << largest_ans << '\n'; // (based on this there's a good chance that ans = n for large n if u rng)
}