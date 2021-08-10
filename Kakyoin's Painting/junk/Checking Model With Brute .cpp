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



// print test case to stdout
void generate_test(int test_cases)
{
	cout << test_cases << '\n';
	for (int i = 1; i <= test_cases; i++) {
		cout << i << '\n';
	}
}

const int mod = 1e9 + 7;
const int maxn = 2e6;
long long fac[maxn + 1];
long long inv_fac[maxn + 1];

const int maxn2 = 1e4 + 1;
long long dp[maxn2][maxn2][2]; // dp[curr point][num disjoint intervals][interval includes i]

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
	cin.tie(0)->sync_with_stdio(0);
	// O(n)

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

// read test case from stin and print solution to stdout
void brute_sol()
{
	cin.tie(0)->sync_with_stdio(0);
	// O(n^2)

	// solution
	int t, n;
	//cerr << "hi\n";
	cin >> t;
	//cerr << t << '\n';
	while (t--)
	{
		cin >> n;
		//cerr << n << '\n';
		long long ans = 0;
		for (int num_recs = 1; num_recs <= n; num_recs++)
		{
			long long contribution = num_recs;
			contribution = contribution * (dp[n][num_recs][0] + dp[n][num_recs][1]) % mod;
			contribution = contribution * (dp[n][num_recs][0] + dp[n][num_recs][1]) % mod;
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
	// precompute factorials and inv factorials modulo 1e9+7
	fac[0] = 1;
	for (int i = 1; i <= maxn; i++) {
		fac[i] = fac[i - 1] * i % mod;
	}

	inv_fac[maxn] = powm(fac[maxn], mod - 2);
	for (int i = maxn - 1; i >= 0; i--) {
		inv_fac[i] = inv_fac[i + 1] * (i + 1) % mod;
	}

	// run dp
	dp[1][1][1] = 1;
	dp[1][0][0] = 1;
	for (int i = 0; i < maxn2 - 1; i++)
	{
		for (int j = 0; j < maxn2 - 1; j++)
		{
			dp[i + 1][j][1] = (dp[i + 1][j][1] + dp[i][j][1]) % mod; // extend current one
			dp[i + 1][j + 1][1] = (dp[i + 1][j + 1][1] + dp[i][j][0] + dp[i][j][1]) % mod; // start new one
			dp[i + 1][j][0] = (dp[i + 1][j][0] + dp[i][j][0] + dp[i][j][1]) % mod; // end current one(if exists) and don't start new one
		}
	}

	int num_tests = 1;

	string directory = R"(C:\Users\elija\Desktop\CODING\Competitive Programming Problemsetting\TeamsCode\2021 Summer\Kakyoin's Painting\Checking Model With Brute Tests\)";

	// read_and_print_file(directory, "1model.out"); 

	for (int test_num = 1; test_num <= num_tests; test_num++)
	{
		// generate the input
		freopen((directory + to_string(test_num) + ".in").c_str(), "w", stdout);
		generate_test(maxn2-1);

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
			//cerr << temp << '\n';
			brute_output.push_back(temp);
		}
		fin.close();

		// compare outputs
		cerr << model_output.size() << ' ' << brute_output.size() << '\n';
		for (int i = 0; i < min(model_output.size(), brute_output.size()); i++) 
		{
			if (model_output[i] != brute_output[i])
			{
				cerr << "The model and the brute do not agree!\n";
				cerr << model_output[i] << ' ' << brute_output[i] << '\n';
				fail = 1;
			}
		}
	}

	if (!fail) {
		cerr << "The model and the brute agree!\n";
	}
}