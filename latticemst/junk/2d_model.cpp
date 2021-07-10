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
const ll mod = 1e9 + 7, MOD = 1e9 +7, ll_max = (ll)1e18;
const int MX = 1e6 +10, int_max = 0x3f3f3f3f;

using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
//this is benq's short mint template
//https://github.com/bqi343/USACO/blob/master/Implementations/content/number-theory%20(11.1)/Modular%20Arithmetic/ModIntShort.h
struct mi {
 	int v; explicit operator int() const { return v; } 
	mi() { v = 0; }
	mi(ll _v):v(_v%MOD) { v += (v<0)*MOD; }
};
mi& operator+=(mi& a, mi b) { 
	if ((a.v += b.v) >= MOD) a.v -= MOD; 
	return a; }
mi& operator-=(mi& a, mi b) { 
	if ((a.v -= b.v) < 0) a.v += MOD; 
	return a; }
mi operator+(mi a, mi b) { return a += b; }
mi operator-(mi a, mi b) { return a -= b; }
mi operator*(mi a, mi b) { return mi((ll)a.v*b.v); }
mi& operator*=(mi& a, mi b) { return a = a*b; }
mi Pow(mi a, ll p) { assert(p >= 0); // asserts are important! 
	return p==0?1:Pow(a*a,p/2)*(p&1?a:1); }
mi inv(mi a) { assert(a.v != 0); return Pow(a,MOD-2); }
mi operator/(mi a, mi b) { return a*inv(b); }
//-------------------------------------------


vector<mi> sums;

int kthsum(int n, int k){ //sum of 1^k, 2^k, ... x^k
	sums.clear(); sums.pb(mi());
	
	mi co(1), ans, t;

	for(int i = 1; i<=k+1; i++){
		t += Pow(i, k); sums.pb(t);
	}		
	//orz(siz(sums) == k + 1);
	if(n < siz(sums)) return int(sums[n]);
	for(int i = 1; i<siz(sums); i++){
		co *= mi(n - i);
		co = co / mi(0 - i);
	}
	//cout << siz(sums) << endl;
	//for(const auto& it : sums){
		//cout << int(it) << " ";
	//} cout << endl;
	//cout << int(co) << endl;
	for(int i = 0; i<siz(sums); i++){
		ans += co * sums[i];
		if(i + 1 >= siz(sums)) break;		
		co *= mi(n - i)/mi(n - (i + 1));
		co *= mi(i - (siz(sums) - 1))/mi(i + 1);
	}
	return int(ans);
}

int pOw(int a, int k){
	ll ans = 1;
	while(k--) (ans *= a) %= mod;
	return (int)ans;
}

int eval(int x, int k){
	return ((kthsum(x, k) - kthsum(x/2, k))*2 + tern(x%2, 0, pOw(x/2, k)))%mod;
}

int solve(int n, int m, int k){
	n--, m--;
	ll ans = (eval(n, k) * (m+1))%mod + (eval(m, k) * (n+1))%mod;
	ans -= 2 * (pOw(n, k) + pOw(m, k));
	ans += max(pOw(n, k) + pOw(m/2, k), pOw(m, k) + pOw(n/2, k));
	return ans%mod;
}


int main(){
  cin.tie(0) -> sync_with_stdio(0);
	int T; cin >> T;
	while(T--){
		int n, m, k; cin >> n >> m >> k;
		cout << solve(n, m, k) << "\n";
	}
	return 0;
}


