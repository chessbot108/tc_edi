#include <iostream>
#include <fstream>
#include <memory.h>
#include <string>
using namespace std;
#define MAXN 1001
int A[MAXN][MAXN];
int pre[MAXN][MAXN];

int main()
{
	int N, M, Q;
	cin >> N >> M >> Q;

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			cin >> A[i][j];

	memset(pre, 2, sizeof pre);
	pre[0][0] = A[0][0];
	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
		{
			if (!i && !j) continue;

			pre[i][j] = min(pre[i][j], A[i][j]);
			if (i) pre[i][j] = min(pre[i][j], pre[i - 1][j]);
			if (j) pre[i][j] = min(pre[i][j], pre[i][j - 1]);
		}

	for (int i = 0; i < Q; i++)
	{
		int a, b;
		cin >> a >> b;

		cout << pre[a - 1][b - 1] << "\n";
	}
	return 0;
}
