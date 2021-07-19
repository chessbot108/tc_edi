/*
* Try to get from node 1 to node n, each edge has a weight, and a flow
* need to have weights less than K, but with max flow
* flow is the min flow of all edges in path
* also one edge might be deleted, calculate max flow in worst case possible
* N(logN)^2, logN for binary search, NlogN for dij/segment tree
* very hard
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <string>
using namespace std;
#define MAXN 50001
vector<int> adj[MAXN];
map<pair<int, int>, int> wt, flow, ind;
map<pair<int, int>, bool> is_path;
vector<pair<int, int> > edges, path;
int dist[MAXN], end_dist[MAXN], par[MAXN], npar[MAXN], st[4*MAXN], llast[MAXN], rfirst[MAXN];
int N, M, K;

void update(int l, int r, int ul, int ur, int si, int val)
{
	if (ul <= l && r <= ur)
	{
		st[si] = min(st[si], val);
		return;
	}
	if (ul > r || l > ur) return;

	int m = (l + r) / 2;
	update(l, m, ul, ur, 2 * si + 1, val);
	update(m + 1, r, ul, ur, 2 * si + 2, val);
}

int query(int l, int r, int si, int e)
{
	if (l == r) return st[si];

	int m = (l + r) / 2;
	return min(st[si], e < m ? query(l, m, 2 * si + 1, e) : query(m + 1, r, 2 * si + 2, e));
}

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
		else if (!curr) continue;

		for (int c : adj[curr])
		{
			if (c == par[curr]) continue;
			if ((end_dist[c] == 33686018 || end_dist[curr] + wt[{curr, c}] < end_dist[c]) && flow[{curr, c}] <= min_flow)
			{
				end_dist[c] = end_dist[curr] + wt[{curr, c}];
				vis.insert({ end_dist[c], c });
				par[c] = curr;
			}
		}
	}

	return false;
}

void main_dij(int min_flow, int n)
{
	set<pair<int, pair<int, int> > > vis;
	vis.insert({ 0, { n, -1 }});

	if (n == N - 1)
	{
		end_dist[n] = 0;
		while (vis.size())
		{
			int curr = vis.begin()->second.first;
			int prev = vis.begin()->second.second;
			vis.erase(vis.begin());

			/*
			if (adj[78].size() > 100)
				curr = 1273;
			*/
			if (curr == 5433)
				curr = 5433;

			for (int c : adj[curr])
			{
				if (c == par[curr]) continue;
				if (flow[{curr, c}] > min_flow) continue;

				if (end_dist[c] == 33686018 || end_dist[curr] + wt[{curr, c}] < end_dist[c])
				{
					if (prev == -1 && !is_path[{curr, c}])
					{
						rfirst[ind[{curr, c}]] = path.size();
						rfirst[ind[{c, curr}]] = path.size();
					}
					else if (!is_path[{curr, c}])
					{
						rfirst[ind[{curr, c}]] = rfirst[ind[{ prev, curr }]];
						rfirst[ind[{c, curr}]] = rfirst[ind[{ prev, curr }]];
					}

					end_dist[c] = end_dist[curr] + wt[{curr, c}];
					vis.insert({ end_dist[c], { c, curr } });
					par[c] = curr;
				}
			}
		}
	}
	else
	{
		dist[n] = 0;
		while (vis.size())
		{
			int curr = vis.begin()->second.first;
			int prev = vis.begin()->second.second;
			vis.erase(vis.begin());

			for (int c : adj[curr])
			{
				if (c == npar[curr]) continue;
				if (flow[{curr, c}] > min_flow) continue;

				if ((dist[c] == 33686018 || dist[curr] + wt[{curr, c}] < dist[c]))
				{
					if (prev == -1 && !is_path[{curr, c}])
					{
						llast[ind[{curr, c}]] = -1;
						llast[ind[{c, curr}]] = -1;
					}
					else if (!is_path[{curr, c}])
					{
						llast[ind[{curr, c}]] = llast[ind[{ prev, curr }]];
						llast[ind[{c, curr}]] = llast[ind[{ prev, curr }]];
					}
					dist[c] = dist[curr] + wt[{curr, c}];
					vis.insert({ dist[c], { c, curr } });
					npar[curr] = c;
				}
			}
		}
	}
}

int main() {
	for (int t = 1; t <= 10; t++)
	{
		edges.clear();
		path.clear();
		wt.clear();
		flow.clear();
		ind.clear();
		memset(llast, 0, sizeof llast);
		memset(rfirst, 0, sizeof rfirst);
		for (int i = 0; i < MAXN; i++) adj[i].clear();
		ifstream cin(to_string(t) + ".in");
		ofstream cout(to_string(t) + ".out");

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
			memset(end_dist, 2, sizeof end_dist);
			memset(dist, 2, sizeof dist);
			memset(st, 2, sizeof st);

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
			memset(llast, 0, sizeof llast);
			memset(rfirst, 0, sizeof rfirst);
			main_dij(m, N - 1);
			main_dij(m, 0);

			for (int i = 0; i < edges.size(); i++)
				update(0, N - 1, llast[i] + 1, rfirst[i], 0, dist[edges[i].first] + wt[edges[i]] + end_dist[edges[i].second]);

			int bin_ans = 0;
			for (int i = 0; i < path.size(); i++)
				bin_ans = max(bin_ans, query(0, N - 1, 0, i));

			if (bin_ans > K)
				lo = m;
			else
				hi = m;
		}

		cout << hi << "\n";
	}
	return 0;
}