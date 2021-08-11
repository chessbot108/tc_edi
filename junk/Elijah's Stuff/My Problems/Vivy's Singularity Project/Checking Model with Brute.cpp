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
const int mod = 1e9 + 7;
long long dp1[maxn], dp2[maxn];

long long powm(long long b, long long e)
{
	b %= mod;
	long long ret = 1;

	while (e)
	{
		if (e & 1)
		{
			ret = ret * b % mod;
		}

		e >>= 1;
		b = b * b % mod;
	}

	return ret;
}

struct segtree
{
	int n;
	vector<long long> t, lazy;

	segtree(int n)
	{
		this->n = n;
		t.resize(4 * n);
		lazy.resize(4 * n, 1);
	}

	void propagate(int v, int tl, int tr)
	{
		if (lazy[v] != 1)
		{
			t[v] = t[v] * lazy[v] % mod; // update

			if (tl != tr)
			{
				// non leaf so pass lazy tag to children
				lazy[2 * v] = lazy[2 * v] * lazy[v] % mod;
				lazy[2 * v + 1] = lazy[2 * v + 1] * lazy[v] % mod;
			}

			lazy[v] = 1; // remove tag
		}
	}

	void assign(int idx, int amt)
	{
		assign(1, 0, n - 1, idx, amt);
	}
	void assign(int v, int tl, int tr, int idx, int amt)
	{
		propagate(v, tl, tr); // non-associative invalidates lazy tag

		if (tl == tr)
		{
			t[v] = amt;
			return;
		}

		int tm = (tl + tr) / 2;
		if (idx <= tm)
		{
			assign(2 * v, tl, tm, idx, amt);
		}
		else
		{
			assign(2 * v + 1, tm + 1, tr, idx, amt);
		}

		t[v] = (t[2 * v] + t[2 * v + 1]) % mod;
	}

	void multiply(int l, int r, int amt)
	{
		multiply(1, 0, n - 1, l, r, amt);
	}
	void multiply(int v, int tl, int tr, int l, int r, int amt)
	{
		propagate(v, tl, tr); // need to propagate so we can update value of current node correctly 
		// (find correct value for descendants then build back up)

		if (tr < l or r < tl)
		{
			return;
		}

		if (l <= tl and tr <= r)
		{
			lazy[v] = lazy[v] * amt % mod;
			propagate(v, tl, tr); // set value since we use it to build back up
			return;
		}

		int tm = (tl + tr) / 2;
		multiply(2 * v, tl, tm, l, r, amt);
		multiply(2 * v + 1, tm + 1, tr, l, r, amt);

		t[v] = (t[2 * v] + t[2 * v + 1]) % mod;
	}

	long long sum(int l, int r)
	{
		return sum(1, 0, n - 1, l, r);
	}
	long long sum(int v, int tl, int tr, int l, int r)
	{
		propagate(v, tl, tr); // propagate so that nodes we take sum from are updated to right value

		if (tr < l or r < tl)
		{
			return 0;
		}

		if (l <= tl and tr <= r)
		{
			return t[v];
		}

		int tm = (tl + tr) / 2;
		return (sum(2 * v, tl, tm, l, r) + sum(2 * v + 1, tm + 1, tr, l, r)) % mod;
	}
};


// print test case to stdout (redirected to file)
void generate_test(int test_num)
{
	vector<string> test_cases;
	int tot_n = 0;
	while (1)
	{
		int n, x;
		if (test_num == 40)
		{
			// max test
			n = maxn;
			x = randint(1e5, 1e9);
		}
		else {
			n = randint(1, pow(10, (test_num - 1) / 10 + 1));
			x = randint(1, randint(1,n) + randint(0, 1) * randint(1,1e9-n)); // test some x < n and some x > n
		}

		if (tot_n + n > maxn)
		{
			break;
		}
		else
		{
			tot_n += n;
		}

		test_cases.push_back(to_string(n) + ' ' + to_string(x) + '\n');
	}

	cout << test_cases.size() << '\n';
	for (auto& test_case : test_cases)
	{
		cout << test_case;
	}
}

// read test case from stdin and print solution to stdout (redirected to file)
void model_sol()
{
	cin.tie(0)->sync_with_stdio(0);

	int t; cin >> t;

	while (t--)
	{
		int n, x; cin >> n >> x;

		long long inv_x = powm(x, mod - 2);

		segtree st(n);

		// do dp
		st.assign(0, 1); // base case
		for (int event = 2; event <= n; event++)
		{
			// edge case of x < event is handled automatically (prob becomes 0)
			st.assign(event - 1, ((st.sum(0, x % event - 1) * (x / event + 1) +
				st.sum(x % event, event - 2) * (x / event)) % mod) * inv_x % mod);

			st.multiply(0, event - 2, (x / event + (event - 1 < (x % event))) * inv_x % mod);

			// now array that st represents = dp[event]
		}

		cout << st.sum(0, n - 1) << '\n';
	}
}

// read test case from stin and print solution to stdout (redirected to file)
void brute_sol()
{
	cin.tie(0)->sync_with_stdio(0);

	int t; cin >> t;

	while (t--)
	{
		int n, x; cin >> n >> x;

		long long inv_x = powm(x, mod - 2);

		// do dp
		dp1[0] = 1;
		for (int event = 2; event <= n; event++)
		{
			// edge case of x < event is handled automatically (prob becomes 0)
			long long prob = (x / event + (event - 1 < x % event)) * inv_x % mod;

			for (int i = 0; i < x % event; i++)
			{
				dp2[event - 1] = (dp2[event - 1] + (x / event + 1) * dp1[i]) % mod;
				dp2[i] = prob * dp1[i] % mod;
			}
			for (int i = x % event; i <= event - 2; i++)
			{
				dp2[event - 1] = (dp2[event - 1] + (x / event) * dp1[i]) % mod;
				dp2[i] = prob * dp1[i] % mod;
			}
			dp2[event - 1] %= mod;
			dp2[event - 1] = dp2[event - 1] * inv_x % mod;

			memcpy(dp1, dp2, 8 * event);
		}

		cout << accumulate(dp1, dp1 + n, 0ll) % mod << '\n';
		fill(dp1, dp1 + n, 0);
		fill(dp2, dp2 + n, 0);
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

	int num_tests = 40;

	string directory = R"(C:\Users\elija\Desktop\CODING\Competitive Programming Problemsetting\TeamsCode\2021 Summer\Vivy's Singularity Project\Checking Model with Brute Tests\)";

	// read_and_print_file(directory, "40brute.out"); 

	for (int test_num = 1; test_num <= num_tests; test_num++)
	{
		// generate the input
		freopen((directory + to_string(test_num) + ".in").c_str(), "w", stdout);
		generate_test(test_num);

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
}