// O(n)
#include<bits/stdc++.h>
using namespace std;

const int maxn = 2000;
int c[maxn][maxn]; // colors
int b[maxn][maxn]; // converted field
int hist[maxn]; // histogram of 1's
int next_smol[maxn], prev_smol[maxn]; // index of next or prev strictly smaller element
int t, n, largest_rect;

int main() 
{
	cin.tie(0)->sync_with_stdio(0);

	cin >> t;

	while (t--) 
	{
		cin >> n;

		// read in c
		for (int i = 0; i < n; i++) 
		{
			for (int j = 0; j < n; j++)
			{
				cin >> c[i][j];
			}
		}

		// create b
		for (int i = 0; i < n - 1; i++) 
		{
			for (int j = 0; j < n; j++) 
			{
				b[i][j] = c[i][j] == c[i + 1][j];
			}
		}

		// find largest rectangle with width >= 2 
		fill(hist, hist + n, 0); // set to 0
		largest_rect = 0;

		for (int i = 0; i < n - 1; i++) 
		{
			// update histogram
			for (int j = 0; j < n; j++) 
			{
				if (b[i][j]) 
				{
					hist[j]++;
				}
				else 
				{
					hist[j] = 0;
				}
			}

			// find next_smol and prev_smol
			stack<int> s; // stores indices
			for (int j = 0; j < n; j++) 
			{
				while (!s.empty() and hist[s.top()] > hist[j])
				{
					next_smol[s.top()] = j;
					s.pop();
				}

				s.push(j);
			}
			while (!s.empty())
			{
				next_smol[s.top()] = n; // assume border/edge is the bound
				s.pop();
			}

			for (int j = n-1; j >= 0; j--)
			{
				while (!s.empty() and hist[s.top()] > hist[j])
				{
					prev_smol[s.top()] = j;
					s.pop();
				}

				s.push(j);
			}
			while (!s.empty())
			{
				prev_smol[s.top()] = -1; // assume border/edge is the bound
				s.pop();
			}

			// find largest rect with base at row i
			for (int j = 0; j < n; j++) 
			{
				// (hist[j]+1) because we convert to true area in c
				largest_rect = max(largest_rect, (hist[j] + 1) * (next_smol[j] - prev_smol[j] - 1));
			}
		}


		cout << max(n, largest_rect) << '\n';
	}
}