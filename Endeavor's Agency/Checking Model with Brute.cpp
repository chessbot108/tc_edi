// we don't actually use a brute here because we can be certain logic is right based on wikipedia 
// and LIS is right based on CSES test
// Thus, we are just testing that we can restore the permutation uniquely and properly

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
const int maxn = 1e5;
const int maxm = 5e5;

string directory = R"(C:\Users\elija\Desktop\CODING\Competitive Programming Problemsetting\TeamsCode\2021 Summer\Endeavor's Agency\Checking Model with Brute Tests\)";


// print test case to stdout (redirected to file)
void generate_test(int test_num)
{
	vector<string> test_cases;
	vector<string> perm_for_test_cases;
	int tot_n = 0;
	// generate test cases until constraint (like maxn) is met
	// good idea to generate in largest range of n possible
	while (1)
	{
		// value of n
		int n = randint(1, pow(10, (test_num - 1) / 10 + 1));
		if (test_num > 45)
		{
			n = 1e5;
		}

		if (tot_n + n > maxn)
		{
			break;
		}
		else
		{
			tot_n += n;
		}

		// create perm
		vector<int> perm(n);
		iota(perm.begin(), perm.end(), 1);

		// for our perm we'll create 1 to 10 segments that'll be shuffled and ensure sum of inversions per each is <= 5*n
		vector<pair<int,int>> inversions;

		int num_segs = randint(1, max(1,min(n/3, 10))); // don't want too many segs cuz then components are small (lis in component ~ 2*sqrt(n))
		// guaranteed not to intersect with start of next seg
		int len_seg = min(n / num_segs, int(sqrt(4 * 5 * n / num_segs))); // expected # inversions = n*(n-1)/4 for random perm of len n

		for (int seg_start = 0, seg_num = 1; seg_num <= num_segs; seg_num++)
		{
			// try to shuffle this seg

			vector<int> shuffled(perm.begin() + seg_start, perm.begin() + seg_start + len_seg);
			shuffle(shuffled.begin(), shuffled.end(), rng);

			vector<pair<int, int>> curr_inversions;
			for (int j = 0; j < len_seg; j++)
			{
				for (int k = j + 1; k < len_seg; k++)
				{
					if (shuffled[j] > shuffled[k])
					{
						// make sure data seems random so they can't reverse engineer
						if (randint(0, 1))
						{
							curr_inversions.push_back({ shuffled[j],shuffled[k] });
						}
						else
						{
							curr_inversions.push_back({ shuffled[k],shuffled[j] });
						}
					}
				}
			}

			if (inversions.size() + curr_inversions.size() > 5 * n)
			{
				break; // too main inversions/edges
			}
			else
			{
				for (int j = 0; j < len_seg; j++)
				{
					perm[seg_start + j] = shuffled[j]; // use this shuffle
				}

				inversions.insert(inversions.end(), curr_inversions.begin(), curr_inversions.end()); // keep track of inversions/edges
			}

			seg_start += n / num_segs;
		}

		shuffle(inversions.begin(), inversions.end(), rng); // make sure data seems random so they can't reverse engineer

		int m = inversions.size();
		test_cases.push_back(to_string(n) + ' ' + to_string(m) + '\n');
		for (auto [u, v] : inversions)
		{
			test_cases.back() += to_string(u) + ' ' + to_string(v) + '\n';
		}


		perm_for_test_cases.push_back("");
		for (auto& i : perm)
		{
			perm_for_test_cases.back() += to_string(i) + ' ';
		}
		perm_for_test_cases.back() += '\n';

		// create permutation graph for the perm

	}

	cout << test_cases.size() << '\n';
	for (auto& test_case : test_cases)
	{
		cout << test_case;
	}

	fflush(stdout);
	freopen((directory + to_string(test_num) + "brute" + ".out").c_str(), "w", stdout);
	for (auto& perm : perm_for_test_cases)
	{
		cout << perm;
	}
	fflush(stdout); // because otherwise when reading output for model/brute last line might still be in the buffer
}

// read test case from stdin and print solution to stdout (redirected to file)
void model_sol()
{
	cin.tie(0)->sync_with_stdio(0);

	int t; cin >> t;

	while (t--)
	{
		int n, m; cin >> n >> m;
		//cerr << n << ' ' << m << '\n';

		vector<int> outdegree(n + 1), indegree(n + 1); // without adding extra edges

		// read in edges
		while (m--)
		{
			int u, v; cin >> u >> v;
			//cerr << u << ' ' << v << '\n';
			if (u > v) {
				swap(u, v);
			}

			outdegree[u]++;
			indegree[v]++;
		}

		// restore permutation
		vector<int> perm(n);

		for (int i = 1; i <= n; i++)
		{
			perm[outdegree[i] + i - 1 - indegree[i]] = i;
		}

		for (auto& i : perm)
		{
			cout << i << ' ';
			//cerr << i << ' ';
		}
		cout << '\n';
		//cerr << '\n';
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

	int num_tests = 50;

	read_and_print_file(directory, "1model.out"); 

	for (int test_num = 1; test_num <= num_tests; test_num++)
	{
		// generate the input
		freopen((directory + to_string(test_num) + ".in").c_str(), "w", stdout);
		generate_test(test_num);

		// generate the output for the brute
		// (already generated in generate test)

		// generate the output for the model
		freopen((directory + to_string(test_num) + ".in").c_str(), "r", stdin);
		freopen((directory + to_string(test_num) + "model" + ".out").c_str(), "w", stdout);
		model_sol();
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
}