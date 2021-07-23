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
const int MX = 2e5 +10, int_max = 0x3f3f3f3f;

using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int is_prime(int x){
	for(int i = 2; i*i <=x; i++){
		if(x%i == 0) return 0;
	}
	return 1;
}	
int main(){
  cin.tie(0) -> sync_with_stdio(0);
	int t; cin >> t;
	char inp[20], oup[20];
	sprintf(inp, "%d.in", t);
	sprintf(oup, "%d.out", t);
	FILE * I = fopen(inp, "w");
	int T; T = 10;
	fprintf(I, "%d\n", T);
	while(T--){
		int p = uid(1, 2);
		int a = uid(1, 1e3/p);
		while(!is_prime(a)){a++;}
		fprintf(I, "%d %d\n", a*(1 << p), 1);
	}
  return 0;
}


