// O(n^2)
#include<bits/stdc++.h>
using namespace std;

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

int main()
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
			for (int i = x % event; i <= event-2; i++)
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