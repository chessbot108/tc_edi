#include<bits/stdc++.h>
using namespace std;

// random number from 0 to 2^64-1 (be careful about it taking unsigned int / long long!)
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

// random number from a to b
long long randint(long long a, long long b)
{
	return rng() % (b - a + 1) + a;
}


// put constraints under here
const int maxk = 3e5;
#define MAXN 1001
string grid[MAXN];
pair<int, int> par[MAXN][MAXN];
int ans[MAXN][MAXN];
bool vis[MAXN][MAXN]; //for bfs

int dx[4] = { 0, 1, 0, -1 };
int dy[4] = { 1, 0, -1, 0 };

pair<int, int> find(const pair<int, int> p)
{
	pair<int, int> n = par[p.first][p.second];
	pair<int, int> prev = p;

	set<pair<int, int> > cycle;
	vector<pair<int, int> > path;
	path.push_back(p);
	while (n != prev)
	{
		// cerr << n.first << ' ' << n.second << '\n';

		if (cycle.count(n))
		{
			cerr << "egg" << '\n';
			throw "bad";
		}
		// assert(!cycle.count(n));
		cycle.insert(n);
		prev = n;
		n = par[n.first][n.second];
		path.push_back(n);
	}

	for (auto i : path)
		par[i.first][i.second] = n;

	return par[p.first][p.second];
	// cerr << "bye\n";
}

// print test case to stdout (redirected to file)
// top left quarter (quadrant) is an isolated component
// 1e5 edges go from it to the start of a chain of 1e5 edges -> 1e10 worst case
// endpoint is in top right so that heuristic of "stop when found exit" shouldn't work (dist if far away)
// thus we only generate 100 more teleporters after this just so the exit is far away

// no cycles because the main construction has no cycles then every other "extra" teleporter
// links to a higher index so it's a dag

// O((maxk/2)^2) for brute
// dist to finish is 280->850 with average 500 for max test and 140 ish for /10 test
void generate_test(int test_num)
{

	if (test_num == 1)
	{
		cout << R"(5 5 3
..#..
.#...
...#.
.##..
#....
4 1 5 2
5 2 4 4
1 2 5 2
)";
		return;
	}

	int n = MAXN - 1;
	int m = n;
	int num_extra_tel = maxk/3000;
	int factor = 1;

	if (test_num == 2 or test_num == 3) {
		n /= 10;
		m /= 10; 
		factor = 10; 
		// technicaly should be ^2 for num_extra_tel since prop to area, 
		// but already there's only 100
	}

	vector<string> teleporters;
	vector<string> grid(n, string(n, '.'));


	// create isolated top left
	for (int i = 0; i <= n / 2; i++)
	{
		grid[i][n / 2] = grid[n / 2][i] = '#';
	}

	// add extra rocks
	// be careful if num rocks is high (want enough empty spaces for teleporters)
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (abs(n - 1 - i) + abs(n - 1 - j) <= 20 or abs(i) + abs(j) <= 20)
			{
				continue; // want to make sure start and end point is not blocked
			}

			if (i < n / 2 or j < n / 2)
			{
				continue; // we want no rocks here so we can guarantee we reach as many teleporters
				// as possible for worst case to be reached for brute
			}

			if (randint(1, 10) <= 2)
			{
				grid[i][j] = '#'; 
				// was going to make more rocks (40%) because -> decent sized components, but still enough of them
				// however then we need many many more teleporters to guarantee a path to exit
				// which leads our graph to having a much shorter path to exit
			}
		}
		// cerr << grid[i] << '\n';
	}

	// add teleporters
	vector<pair<int,int>> in_top_left, in_chain, external;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (grid[i][j] == '.')
			{	
				if (abs(n - 1 - i) + abs(n - 1 - j) <= 20 or abs(i) + abs(j) <= 20)
				{
					continue; // want to make sure start and end point is not blocked
				}
				else if (i == 0 and j == n - 1)
				{
					continue; // endpoint of chain
				}
				else if (i < n / 2 and j < n / 2)
				{
					// in_top_left.push_back({ i+1,j+1 });

					// we need to construct it such that all teleporters are reachable and are close
					// to the start so we can guarantee we reach as many teleporters
					// as possible for worst case to be reached for brute
					if (i % 2 == 0 and i != j)
					{
						in_top_left.push_back({ i + 1, j + 1 });
					}
				}
				else if (randint(1,2) <= 1)
				{
					in_chain.push_back({ i+1,j+1 });
				}
				else
				{
					external.push_back({ i+1,j+1 });
				}
			}
		}
	}
	
	shuffle(in_top_left.begin(), in_top_left.end(), rng); // so we can take random subset
	sort(in_top_left.begin(), in_top_left.end(),
		[&](const pair<int, int>& a, const pair<int, int>& b)
		{
			return a.first + a.second < b.first + b.second;
		}
	); // sort it so that the closer ones are used so we can reach worst case
	shuffle(in_chain.begin(), in_chain.end(), rng); // so we can take random subset
	shuffle(external.begin(), external.end(), rng); // so we can take random subset

	cerr << in_chain.size() << ' ' << in_top_left.size() << ' ' << '\n';
	in_chain.resize(min((int)in_chain.size(), (maxk/ (factor * factor) - num_extra_tel/factor)/2 - 10));
	in_chain.push_back({ 1,n });
	in_top_left.resize(min((int)in_top_left.size(), (maxk/ (factor * factor) - num_extra_tel/factor)/2 - 10));

	// connect to start of chain
	for (auto [i,j] : in_top_left)
	{
		teleporters.push_back(to_string(i) + ' ' + to_string(j) + ' ' + 
			to_string(in_chain[0].first) + ' ' + to_string(in_chain[0].second));
	}
	
	// connect chain
	for (int i = 0; i < in_chain.size() - 1; i++)
	{
		teleporters.push_back(to_string(in_chain[i].first) + ' ' + to_string(in_chain[i].second) + 
			' ' + to_string(in_chain[i+1].first) + ' ' + to_string(in_chain[i+1].second));
	}

	// other teleporters
	for (int i = 0; i < external.size()-1; i++)
	{
		if (randint(1, external.size()) <= num_extra_tel/factor and teleporters.size() < maxk/(factor*factor))
		{
			int j = randint(i+1, external.size()-1);

			teleporters.push_back(to_string(external[i].first) + ' ' + to_string(external[i].second) +
				' ' + to_string(external[j].first) + ' ' + to_string(external[j].second));
		}
	}


	// print output
	shuffle(teleporters.begin(), teleporters.end(), rng); // so that it's more random

	cout << n << ' ' << m << ' ' << teleporters.size() << '\n';

	for (auto row : grid)
	{
		cout << row << '\n';
	}

	for (auto teleporter : teleporters)
	{
		cout << teleporter << '\n';
	}
}

// read test case from stdin and print solution to stdout (redirected to file)
bool model_sol()
{
	/*
	* bfs with walls and stuff
	* also there are one way teleporters which can chain together
	* N^2
	* medium
	*/

	//cerr << "starting\n";
	memset(par, 0, sizeof par);
	memset(vis, false, sizeof vis);
	memset(ans, 0, sizeof ans);

	int N, M, K;
	cin >> N >> M >> K;
	cerr << "n m and k: " << N << ' ' << M << ' ' << K << "\n";

	for (int i = 0; i < N; i++)
	{
		cin >> grid[i];
		// cerr << i << '\n';
	}

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			par[i][j] = { i, j };

	for (int i = 0; i < K; i++)
	{
		int ax, ay, bx, by;
		cin >> ax >> ay >> bx >> by;
		/*if (i % 10000 == 0)
		{
			cerr << "teleporter: " << i << " max: " << K << '\n';
		}*/
		if (ax <= 0 or ay <= 0 or bx <= 0 or by <= 0 or
			ax > N or ay > M or bx > N or by > M)
		{
			throw "bad";
		}
		par[--ax][--ay] = par[--bx][--by];
	}

	//cerr << "done with teleporters\n";

	for (int i = 0; i < N; i++) 
	{
		// cerr << i << '\n';
		for (int j = 0; j < M; j++)
		{
			if (i % 200 == 0 and j % 200 == 0)
			{
				//cerr << "finding: " << i << ' ' << j << " max j: " << M << '\n';
			}
			find({ i, j });
		}
	}
	//cerr << "done with find\n";

	queue<pair<int, int> > q;
	q.push({ 0, 0 });
	ans[0][0] = 0;
	vis[0][0] = true;
	//cerr << "trying\n";
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
	cerr << "the answer " << ans[N - 1][M - 1] << '\n';

	// bad means we didn't find a path from start to exit
	if (ans[N - 1][M - 1] == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

// for checking tests look right
void read_and_print_file(string directory, string name)
{
	freopen((directory + name).c_str(), "r", stdin);

	string a;
	while (getline(cin, a))
	{
		cout << a << '\n';
	}

	exit(0);
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);

	int num_tests = 10;

	string directory = R"(C:\Users\elija\Desktop\CODING\Competitive Programming Problemsetting\TeamsCode\2021 Summer\Other's Problems\Teleport\Tests\)";

	// read_and_print_file(directory, "2.out"); 

	for (int test_num = 1; test_num <= num_tests; test_num++)
	{
		// generate the input
		freopen((directory + to_string(test_num) + ".in").c_str(), "w", stdout);
		generate_test(test_num);
		fflush(stdout);
		cerr << "Generated input for test " << test_num << '\n';

		// generate the output
		freopen((directory + to_string(test_num) + ".in").c_str(), "r", stdin);
		freopen((directory + to_string(test_num) + ".out").c_str(), "w", stdout);
		bool found_exit = model_sol();
		fflush(stdout);

		if (!found_exit) {
			cerr << "Couldn't find an exit retrying\n";
			test_num--;
		}
		else {
			cerr << "Generated output for test " << test_num << '\n';
		}
	}


	cerr << "Tests generated!\n";
}