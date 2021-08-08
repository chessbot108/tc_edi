// O(n)
#include<bits/stdc++.h>
using namespace std;

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int t; cin >> t;

	while (t--)
	{
		int n, m; cin >> n >> m;

		vector<int> outdegree(n+1), indegree(n+1); // without adding extra edges

		// read in edges
		while (m--)
		{
			int u, v; cin >> u >> v;

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

		// find the longest increasing subsequence
		vector<int> dp; // dp[i] = current minimum last element of a subsequence of length i+1

		for (int i : perm)
		{
			auto loc = lower_bound(dp.begin(), dp.end(), i);
			
			if (loc == dp.end())
			{
				dp.push_back(i);
			}
			else
			{
				*loc = i;
			}
		}

		cout << n - dp.size() << '\n'; // n - LIS = size of min vertex cover
	}
}