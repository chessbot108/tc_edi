#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <string>
using namespace std;
#define MAXN 200001
#define MAX_INT 2000000000
vector<int> adj[MAXN];
pair<int, int> removed = { -1, -1 };
map<pair<int, int>, int> wt, flow, ind;
map<pair<int, int>, bool> is_path;
vector<pair<int, int> > edges, path;
int dist[MAXN], end_dist[MAXN], par[MAXN], npar[MAXN], st[4*MAXN], llast[2*MAXN], rfirst[2*MAXN];
int N, M, K;

bool init_dij(int min_flow, int n)
{
	set<pair<int, int> > vis;
	end_dist[n] = 0;
	vis.insert({ 0, n });

	while (vis.size())
	{
		int curr = vis.begin()->second;
		int distance = vis.begin()->first;
		vis.erase(vis.begin());
		if (!curr && distance <= K) return true;
		else if (!curr) return false;

		for (int c : adj[curr])
		{
			if (c == par[curr]) continue;
			if ((end_dist[c] == 33686018 || end_dist[curr] + wt[{curr, c}] < end_dist[c]) && flow[{curr, c}] <= min_flow && make_pair(curr, c) != removed && make_pair(c, curr) != removed)
			{
				end_dist[c] = end_dist[curr] + wt[{curr, c}];
				vis.insert({ end_dist[c], c });
				par[c] = curr;
			}
		}
	}

	return false;
}

int main() {
	cin >> N >> M >> K;

	for (int i = 0; i < M; i++)
	{
		int a, b, w, f;
		cin >> a >> b >> w >> f;

		adj[--a].push_back(--b);
		adj[b].push_back(a);
		edges.push_back({ a, b });
		edges.push_back({ b, a });
		ind[{a, b}] = edges.size() - 2;
		ind[{b, a}] = edges.size() - 1;

		wt[{a, b}] = w;
		wt[{b, a}] = w;
		flow[{a, b}] = f;
		flow[{b, a}] = f;
		is_path[{a, b}] = false;
		is_path[{b, a}] = false;
	}

	int lo = 0;
	int hi = 1e9;
	while (lo + 1 < hi)
	{
		int m = (lo + hi) / 2;

		//reset everything
		path.clear();
		is_path.clear();
		memset(par, -1, sizeof par);
		memset(npar, -1, sizeof npar);
		fill(end_dist, end_dist + MAXN, MAX_INT);
		fill(dist, dist + MAXN, MAX_INT);
		fill(st, st + 4 * MAXN, MAX_INT);

		if (!init_dij(m, N - 1))
		{
			lo = m;
			continue;
		}

		int n = 0;
		while (n != N - 1)
		{
			int prev = n;
			n = par[n];

			if (n == prev) break;
			path.push_back({ prev, n });
			is_path[{ prev, n }] = true;
			is_path[{ n, prev }] = true;

			llast[ind[{n, prev}]] = path.size() - 2;
			llast[ind[{prev, n}]] = path.size() - 2;
			rfirst[ind[{n, prev}]] = path.size() - 1;
			rfirst[ind[{prev, n}]] = path.size() - 1;

		}

		memset(par, -1, sizeof par);
		memset(npar, -1, sizeof npar);
		memset(end_dist, 2, sizeof end_dist);
		memset(dist, 2, sizeof dist);

		int bin_ans = 0;
		bool works = true;
		for (int i = 0; i < path.size(); i++)
		{
			removed = path[i];

			if (!init_dij(m, N - 1))
			{
				lo = m;
				works = false;
				break;
			}
			memset(end_dist, 2, sizeof end_dist);
		}

		if (works)
			hi = m;
	}

	cout << hi << "\n";
	return 0;
}
