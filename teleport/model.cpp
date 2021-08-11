#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <queue>
#include <set>
#include <cassert>
#include <cstring>
using namespace std;
#define MAXN 1001
string grid[MAXN];
pair<int, int> par[MAXN][MAXN];
int ans[MAXN][MAXN];
bool vis[MAXN][MAXN]; //for bfs

int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };

//get where a square ends up after taking teleporter
pair<int, int> find(const pair<int, int> p)
{
	pair<int, int> n = par[p.first][p.second];
	pair<int, int> prev = p;

	set<pair<int, int> > cycle;
	vector<pair<int, int> > path; //path to assign all parents to
	path.push_back(p);
	while (n != prev)
	{
		assert(!cycle.count(n));
		cycle.insert(n);
		prev = n;
		n = par[n.first][n.second];
		path.push_back(n);
	}

	for (auto i : path) //assign parents
		par[i.first][i.second] = n;

	return par[p.first][p.second];
}

int main() {
	memset(par, 0, sizeof par);
	memset(vis, false, sizeof vis);
	memset(ans, 0, sizeof ans);

	int N, M, K;
	cin >> N >> M >> K;

	for (int i = 0; i < N; i++)
		cin >> grid[i];

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			par[i][j] = { i, j };

	for (int i = 0; i < K; i++)
	{
		int ax, ay, bx, by;
		cin >> ax >> ay >> bx >> by;

		par[--ax][--ay] = par[--bx][--by];
	}

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			find({ i, j });

	queue<pair<int, int> > q;
	q.push({ 0, 0 });
	ans[0][0] = 0;
	vis[0][0] = true;

	while (q.size())
	{
		pair<int, int> curr = q.front();
		q.pop();
		vis[curr.first][curr.second] = true;

		for (int d = 0; d < 4; d++)
		{
			int newx = curr.first + dx[d];
			int newy = curr.second + dy[d];

			pair<int, int> end_pair;
			if (newx >= 0 && newx < N && newy >= 0 && newy < M)
				end_pair = par[newx][newy];

			if (newx >= 0 && newx < N && newy >= 0 && newy < M && grid[newx][newy] != '#' && !vis[end_pair.first][end_pair.second])
			{
				vis[end_pair.first][end_pair.second] = true;

				q.push(end_pair);
				ans[end_pair.first][end_pair.second] = ans[curr.first][curr.second] + 1;
			}
		}
	}
	
	cout << ans[N - 1][M - 1] << "\n";
	return 0;
}
