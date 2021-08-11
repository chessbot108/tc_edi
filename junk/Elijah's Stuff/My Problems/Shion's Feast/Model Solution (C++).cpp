// O(n)
#include<bits/stdc++.h>
using namespace std;

int main() 
{
	cin.tie(0)->sync_with_stdio(0);

	int t, k, n, mx;

	cin >> t;
	
	while (t--)
	{
		cin >> n >> k;

		mx = 0;
		for (int i = 0; i < n; i++)
		{
			int a; cin >> a;

			mx = max(mx, a);
		}

		if (mx == 1)
		{
			cout << k * mx << '\n';
		}
		else
		{
			cout << k * mx - 1 << '\n';
		}
	}
}