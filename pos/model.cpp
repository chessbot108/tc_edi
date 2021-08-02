#include <iostream>
#include <fstream>
#include <memory.h>
#include <string>
using namespace std;
#define MAXN 1000001
#define MOD 1000000007
int A[MAXN];
long long fact[MAXN];
int freq[MAXN];

int main() {
	int N;
	cin >> N;

	for (int i = 0; i < N; i++)
	{
		string s;
		cin >> s;
		cin >> A[i];
		freq[A[i]]++;
	}

	fact[0] = 1;
	//precompute factorials
	for (long long i = 1; i < MAXN; i++)
	{
		fact[i] = fact[i - 1] * i;
		fact[i] %= MOD;
	}

	long long ans = 1;
	for (int i = 0; i < MAXN; i++)
	{
		ans *= fact[freq[i]];
		ans %= MOD;
	}

	cout << ans << "\n";
	return 0;
}
