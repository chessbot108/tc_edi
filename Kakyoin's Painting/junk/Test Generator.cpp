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
const int true_maxn = 1e6;
const int mod = 1e9 + 7;
const int maxn = 2e6;
long long fac[maxn + 1];
long long inv_fac[maxn + 1];


// print test case to stdout
void generate_test_small() 
{
	int test_cases = 1400;
	cout << test_cases << '\n';
	for (int i = 1; i <= test_cases; i++)
	{
		cout << i << '\n';
	}
}

void generate_test_medium()
{
	// create test cases
	vector<int> test_cases;
	int tot_sum = 0;

	while (1) 
	{
		int new_n = randint(2e4, 2e5);

		if (tot_sum + new_n <= true_maxn) 
		{
			test_cases.push_back(new_n);
			tot_sum += new_n;
		}
		else
		{
			break;
		}
	}
	test_cases.push_back(true_maxn - tot_sum);
	tot_sum = true_maxn;
	
	// print test cases
	cout << test_cases.size() << '\n';
	for (auto& i : test_cases) {
		cout << i << '\n';
	}
}

void generate_test_large()
{
	cout << 1 << '\n';
	cout << randint(5e5, 1e6) << '\n';
}

void generate_test_mx()
{
	cout << 1 << '\n';
	cout << int(1e6) << '\n';
}

// print test case to stdout (redirected to file)
// for the first test, generates 100% small tests
// for the rest, generates x% small tests and then the last 100-x% is just 1 large test
void generate_test(int test_num, int x = 5)
{
	vector<string> test_cases;
	int tot_n = 0;

	for (int i = 1; i <= 320; i++)
	{
		test_cases.push_back(to_string(i) + '\n');
		tot_n += i;
	}

	//cerr << true_maxn << ' ' << tot_n << '\n';
	test_cases.push_back(to_string(randint((true_maxn - tot_n) * 99 / 100, true_maxn - tot_n)) + '\n');

	// print test cases to stdout (redirected to file)
	cout << test_cases.size() << '\n';
	for (auto& test_case : test_cases)
	{
		cout << test_case;
	}
}

long long powm(long long b, long long e) {
	b %= mod;

	long long ans = 1;

	while (e) {
		if (e & 1) {
			ans = (ans * b) % mod;
		}

		e >>= 1;
		b = (b * b) % mod;
	}

	return ans;
}

long long choose(int n, int k) {
	assert(0 <= k and k <= n);
	return (fac[n] * inv_fac[n - k] % mod) * inv_fac[k] % mod;
}

// read test case from stdin and print solution to stdout
void model_sol()
{
	// O(n)
	cin.tie(0)->sync_with_stdio(0);

	// precompute factorials and inv factorials modulo 1e9+7
	fac[0] = 1;
	for (int i = 1; i <= maxn; i++) {
		fac[i] = fac[i - 1] * i % mod;
	}

	inv_fac[maxn] = powm(fac[maxn], mod - 2);
	for (int i = maxn - 1; i >= 0; i--) {
		inv_fac[i] = inv_fac[i + 1] * (i + 1) % mod;
	}


	// solution
	int t, n;

	cin >> t;
	while (t--) {
		cin >> n;

		long long ans = 0;
		for (int num_recs = 1; num_recs <= n; num_recs++) {
			long long contribution = num_recs;
			contribution = contribution * choose(n + num_recs, 2 * num_recs) % mod;
			contribution = contribution * choose(n + num_recs, 2 * num_recs) % mod;
			contribution = contribution * fac[num_recs] % mod;

			ans = (ans + contribution) % mod;
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

	string directory = R"(C:\Users\elija\Desktop\CODING\Competitive Programming Problemsetting\TeamsCode\2021 Summer\Kakyoin's Painting\Tests\)";

	// read_and_print_file(directory, "2.out"); 

	// generate the input
	freopen((directory + to_string(1) + ".in").c_str(), "w", stdout);
	generate_test_small();

	// generate the output
	freopen((directory + to_string(1) + ".in").c_str(), "r", stdin);
	freopen((directory + to_string(1) + ".out").c_str(), "w", stdout);
	model_sol();

	for (int test_num = 2; test_num <= num_tests; test_num++)
	{
		// generate the input
		freopen((directory + to_string(test_num) + ".in").c_str(), "w", stdout);
		generate_test(test_num);

		// generate the output
		freopen((directory + to_string(test_num) + ".in").c_str(), "r", stdin);
		freopen((directory + to_string(test_num) + ".out").c_str(), "w", stdout);
		model_sol();
	}

	/*for (int test_num = 2; test_num <= num_tests/2; test_num++)
	{
		// generate the input
		freopen((directory + to_string(test_num) + ".in").c_str(), "w", stdout);
		generate_test_medium();

		// generate the output
		freopen((directory + to_string(test_num) + ".in").c_str(), "r", stdin);
		freopen((directory + to_string(test_num) + ".out").c_str(), "w", stdout);
		model_sol();
	}

	for (int test_num = num_tests/2+1; test_num <= num_tests-1; test_num++)
	{
		// generate the input
		freopen((directory + to_string(test_num) + ".in").c_str(), "w", stdout);
		generate_test_large();

		// generate the output
		freopen((directory + to_string(test_num) + ".in").c_str(), "r", stdin);
		freopen((directory + to_string(test_num) + ".out").c_str(), "w", stdout);
		model_sol();
	}

	// generate the input
	freopen((directory + to_string(num_tests) + ".in").c_str(), "w", stdout);
	generate_test_mx();

	// generate the output
	freopen((directory + to_string(num_tests) + ".in").c_str(), "r", stdin);
	freopen((directory + to_string(num_tests) + ".out").c_str(), "w", stdout);
	model_sol();*/

	cerr << "Cases generated!\n";
}