// O(n^3/2)
#include<bits/stdc++.h>
using namespace std;
#define int long long

const int maxn = 1e5;
const int mod = 1e9 + 7;
int h[maxn];
long long dp[maxn + 1];

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

int32_t main()
{
	cin.tie(0)->sync_with_stdio(0);

	int t; cin >> t;

	while (t--)
	{
		// read in input
		int n, k; cin >> n >> k;

		for (int i = 0; i < n; i++)
		{
			cin >> h[i];
		}

		// precompute helpful inverses
		long long inv_k = powm(k, mod - 2);
		long long inv_k_mi_1 = powm(k - 1, mod - 2);
		long long inv_k_mi_1_sq = powm(inv_k_mi_1, 2);

		// compute dp
		dp[0] = 0;
		for (int i = 1; i <= n; i++)
		{
			long long e = 0; // expected attacks assuming Rengoku chooses F != 1

			for (int f = 2; f * f <= i and f <= k; f++)
			{
				if ((i / f) * (i / f) >= i) 
				{ // edge case where if N < sqrt(n) * (sqrt(n) + 1), new health < sqrt(i) for f = floor(sqrt(i))
					e = (e + dp[i / f]) % mod; // new health >= sqrt(i)
				}
			}

			for (int j = 1; j * j < i; j++)
			{
				int f_largest = i / j; // largest f such that i/f = j
				int f_smallest = i / (j + 1) + 1; // smallest f such that i/f = j

				if (f_smallest <= k)
				{
					// get intersection between possible forms (1..k) and forms that reach health j
					e = (e + (min(f_largest,k) - f_smallest + 1) * dp[i / f_largest]) % mod; // new health < sqrt(i)
				}
			}

			// new health = 0 takes 0 extra attacks

			e = ((k - 1 + e) * inv_k) % mod;

			// arithmetico geometric series formula
			dp[i] = (((k * e % mod) * inv_k_mi_1 % mod) + (1 * inv_k_mi_1 % mod)) % mod; 
		}

		long long ans = 0;
		
		for (int i = 0; i < n; i++)
		{
			ans += dp[h[i]];
		}

		cout << ans % mod << '\n';
	}
}
