// O(n^2/2)
#include<bits/stdc++.h>
using namespace std;

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

int main()
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

			for (int f = 2; f <= i and f <= k; f++) {
				e = (e + dp[i / f]) % mod;
			}

			// new health = 0 takes 0 extra forms

			e = ((k - 1 + e) * inv_k) % mod;

			// arithmetico geometric series formula
			dp[i] = (((k * e % mod) * inv_k_mi_1 % mod) + (k * inv_k_mi_1_sq % mod)) % mod;
		}

		long long ans = 0;

		for (int i = 0; i < n; i++)
		{
			ans += dp[h[i]];
		}

		cout << ans % mod << '\n';
	}
}