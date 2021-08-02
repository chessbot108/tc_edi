#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;
#define MAXN 100001

int main() {
	int N;
	cin >> N;

	string s;
	cin >> s;

	int a = 0, b = 0, c = 0;
	int ansa = 0, ansb = 0, ansc = 0;
	for (int i = 0; i < N; i++)
	{
		//update the frequency of each letter up to this point
		if (s[i] == 'A') a++;
		if (s[i] == 'B') b++;
		if (s[i] == 'C') c++;

		int max_used = max(max(a, b), c);

		//update how many points each letter would get if that was the only letter they played
		if (a == max_used) ansa++;
		if (b == max_used) ansb++;
		if (c == max_used) ansc++;
	}

	cout << max(max(ansa, ansb), ansc) << "\n";
	return 0;
}
