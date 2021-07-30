// O(n)
#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 7;
const int maxn = 2e6;
long long fac[maxn + 1];
long long inv_fac[maxn + 1];

long long powm(long long b, long long e)
{
	b %= mod;

	long long ans = 1;

	while (e) 
	{
		if (e & 1) 
		{
			ans = (ans * b) % mod;
		}

		e >>= 1;
		b = (b * b) % mod;
	}

	return ans;
}

long long choose(int n, int k)
{
	assert(0 <= k and k <= n);
	return (fac[n] * inv_fac[n - k] % mod) * inv_fac[k] % mod;
}

int main() 
{
	cin.tie(0)->sync_with_stdio(0);

	// precompute factorials and inv factorials modulo 1e9+7
	fac[0] = 1;
	for (int i = 1; i <= maxn; i++) 
	{
		fac[i] = fac[i - 1] * i % mod;
	}

	inv_fac[maxn] = powm(fac[maxn], mod - 2);
	for (int i = maxn - 1; i >= 0; i--)
	{
		inv_fac[i] = inv_fac[i + 1] * (i + 1) % mod;
	}


	// solution
	int t, n;

	cin >> t;
	while (t--) 
	{
		cin >> n;

		long long ans = 0;
		for (int num_recs = 1; num_recs <= n; num_recs++) 
		{
			long long contribution = num_recs;
			contribution = contribution * choose(n + num_recs, 2 * num_recs) % mod;
			contribution = contribution * choose(n + num_recs, 2 * num_recs) % mod;
			contribution = contribution * fac[num_recs] % mod;

			ans = (ans + contribution) % mod;
		}

		cout << ans << '\n';
	}
}