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

ll arr[MX], psums[MX];

ll Pow(ll a, ll k){
	ll ans = 1;
	for(ll i = 1; i<=k; i <<= 1ll){
		if(k&i) (ans *= a) %= mod;
		(a *= a) %= mod;
	}
	return ans;
}

ll inv(ll a){
	return Pow(a, mod-2);
}

int main(){
  cin.tie(0) -> sync_with_stdio(0);
	//this should run in O(d * max(D) * log(max(D)))
	//which should be the previous codes sqrt of a complexity.
	//quite nicer i would think
	int T; cin >> T;
	while(T--){
		int d, k; cin >> d >> k;
		ll pfull = 0, ans = 0, P = 1;
		for(int i = 0; i<d; i++){
			cin >> arr[i];
			(P *= arr[i]) %= mod;
			arr[i]--;
			pfull += Pow(arr[i], k);
		}
		pfull %= mod;
		sort(arr, arr + d);
		
		for(int i = 0; i<d; i++){
			ll tot = 0;
			for(int j = 0; j<=arr[i]; j++){
				tot += Pow(max(arr[i] - (ll)j, (ll)j), k);
			}
			tot %= mod;
			ans += (((P*inv(arr[i] +1))%mod) * tot)%mod;
		} 
		ans -= (((1ll << (d-1)) %mod) * pfull)%mod;
		(ans += mod) %= mod;
		for(ll i = 0, j = (1ll << d)/4; j; i++, j >>= 1ll){
			ans += (j%mod) * ((pfull + Pow(arr[i]/2, k) + mod - Pow(arr[i], k))%mod);
			ans %= mod;
		}
		assert(ans >= 0 && ans < mod);
		cout << ans << "\n";
	}
  return 0;
}


