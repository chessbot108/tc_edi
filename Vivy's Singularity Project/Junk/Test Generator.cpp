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
const int maxn = 1e5, maxx = 1e9;
const int mod = 1e9 + 7;

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
		n = randint(1, 30); // there are n^2 ish "distinct" inputs for a given n so make n such that potential inputs isn't < num test cases
		x = randint(1, randint(1, n) + randint(0, 1) * randint(maxn, maxx - n)); // test some x < n and some x > n

		if (tot_n + n > (test_num == 1 ? maxn : maxn/20))
		{
			break;
		}
		else
		{
			tot_n += n;
		}

		test_cases.push_back(to_string(n) + ' ' + to_string(x) + '\n');
	}

	test_cases.push_back(to_string(maxn - tot_n) + ' ' + to_string(randint(maxn, maxx)) + '\n');

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

	string directory = R"(C:\Users\elija\Desktop\CODING\Competitive Programming Problemsetting\TeamsCode\2021 Summer\Vivy's Singularity Project\Tests\)";

	// read_and_print_file(directory, "1.in"); 

	for (int test_num = 1; test_num <= num_tests; test_num++)
	{
		// generate the input
		freopen((directory + to_string(test_num) + ".in").c_str(), "w", stdout);
		generate_test(test_num);
		cerr << "Generated input for test " << test_num << '\n';

		// generate the output
		freopen((directory + to_string(test_num) + ".in").c_str(), "r", stdin);
		freopen((directory + to_string(test_num) + ".out").c_str(), "w", stdout);
		model_sol();
		cerr << "Generated output for test " << test_num << '\n';
	}


	cerr << "Tests generated!\n";
}