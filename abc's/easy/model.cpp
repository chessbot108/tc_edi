/*
* a game where you play A, B, C
* player knows oppenets moves, gets a point everytime plays a card the opponent has placed at least the most(ties included)
* tries to get most points
*/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;
#define MAXN 100001

//cant switch cards, must choose only one to play O(N) very easy
int main() {
	for (int t = 1; t <= 10; t++)
	{
		ofstream cout(to_string(t) + ".out");
		ifstream cin(to_string(t) + ".in");

		int N;
		cin >> N;

		string s;
		cin >> s;

		int a = 0, b = 0, c = 0;
		int ansa = 0, ansb = 0, ansc = 0;
		for (int i = 0; i < N; i++)
		{
			if (s[i] == 'A') a++;
			if (s[i] == 'B') b++;
			if (s[i] == 'C') c++;

			int max_used = max(max(a, b), c);

			if (a == max_used) ansa++;
			if (b == max_used) ansb++;
			if (c == max_used) ansc++;
		}

		cout << max(max(ansa, ansb), ansc) << "\n";
	}
	return 0;
}

