#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>
#include <string>
using namespace std;
#define MAXN 400001
bool cut[MAXN]; //there is a cut between bead i and i+1

//simplest verison, only calc num elements in link, NlogN cuz sets, could be O(n*inv_ack) dsu easy

int main() {
	int N, M;
	cin >> N >> M;

	set<int> b;
	set<int> e;
	b.insert(0);
	e.insert(N);
	for (int i = 0; i < M; i++)
	{
		char c;
		int a;
		cin >> c >> a;

		if (c == 'R')
			cut[a] = true;

		if (c == 'Q')
		{
			int ans = 0;
			int n = a - 1;
			while (n > 0 && !cut[n--]) ans++;
			n = a;
			while (n < N && !cut[n++]) ans++;
         	cout << ans + 1 << "\n";
		}
	}
	return 0;
}
