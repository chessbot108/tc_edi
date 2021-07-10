//gyrating cat enthusiast
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <string>
#include <utility>
#include <cassert>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>
#include <queue>
#include <set>

#define ll long long
#define lb long double
#define pii pair<int, int>
#define pb push_back
#define mp make_pair
#define ins insert
#define cont continue
#define siz(vec) ((int)(vec.size()))

#define LC(n) (((n) << 1) + 1)
#define RC(n) (((n) << 1) + 2)
#define init(arr, val) memset(arr, val, sizeof(arr))
#define bckt(arr, val, sz) memset(arr, val, sizeof(arr[0]) * (sz+5))
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)
#define tern(a, b, c) ((a) ? (b) : (c))
#define feq(a, b) (fabs(a - b) < eps)
#define abs(x) tern((x) > 0, x, -(x))

#define moo printf
#define oom scanf
#define mool puts("") 
#define orz assert
#define fll fflush(stdout)

const lb eps = 1e-9;
const ll mod = 1e9 + 7, ll_max = (ll)1e18;
const int MX = 6e5 +10, int_max = 0x3f3f3f3f;

using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int dp[MX];


int main(){
  cin.tie(0) -> sync_with_stdio(0);
	int t = 0, cnt = 0;
	ll sum = 0;
	for(int i = 1; i<=5e5; i++){
		for(int j = 1; j<=i; j++){
			dp[j] = dp[i%j] + 1;
		}
		int q = max(t, *max_element(dp, dp + i + 1));
		if(q > t){
			cout << i << " " << q << endl;
			t = q;
		}
		if(q >= t){
			cnt++; 
			sum += i;
		}
	}
	cout << cnt << " " << sum << endl;
	cout <<t << "\n";
  return 0;
}


