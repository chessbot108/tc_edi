// O(n^6/constant)
#include<bits/stdc++.h>
using namespace std;

const int maxn = 2000;
int c[maxn][maxn]; // colors
int t, n, ans;

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	cin >> t;

	while (t--)
	{
		ans = 0;

		cin >> n;

		// read in c
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				cin >> c[i][j];
			}
		}

		// check retangle top left = (i,j) bottom right = (i2,j2)
		for (int i = 0; i < n; i++) 
		{
			for (int i2 = i; i2 < n; i2++) 
			{
				for (int j = 0; j < n; j++)
				{
					for (int j2 = j; j2 < n; j2++)
					{
						bool all_rows_same = 1;

						for (int i3 = i+1; i3 <= i2; i3++)
						{
							for (int j3 = j; j3 <= j2; j3++)
							{
								if (c[i][j3] != c[i3][j3])
								{
									all_rows_same = 0;
									goto stopped_checking;
								}
							}
						}

					stopped_checking:
						if (all_rows_same)
						{
							ans = max(ans, (i2 - i + 1) * (j2 - j + 1));
						}
					}
				}
			}
		}

		cout << ans << '\n';
	}
}