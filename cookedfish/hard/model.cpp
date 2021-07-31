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
const int MX = 1e6 +10, int_max = 0x3f3f3f3f;

using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());


int T;
ll n, k;

ll arr[MX];

void k_1(){
	// if x is a power of 2, the only solution is for a == b == x
	// idea is (b-a+1)*(b+a) = 2*x you can find the divisors by noting one must be even and the other odd
	
	ll y = (n&(-n))*2; // even divisor = 2 * largest power of 2 that divides x
	ll z = n/(y/2); // odd divisor = x / largest power of 2 that divides it
	
	ll a = (abs(z-y)+1)/2; // 2*a-1 = difference between divisors
	ll b = max(z,y)-a; // largest divisor = b+a
	if(n&(n-1)) cout << a << " " << b+1 << "\n"; //dark magic saying n is not a power of 2
	else cout << "-1 -1\n";
}


__int128 sq(__int128 a){
	//sqrt of a
	__int128 ans = 0;
	for(__int128 i = 63; ~i; i--){
		__int128 p = ((__int128)1 << i);
		if((p + ans) * (p + ans) <= a) ans += p;
	}
	return ans;
}

void k_2(){ //for when k = 2
	__int128 s1 = 0, s2 = 0; //sum of integers and sum of squares
	ll a = -1, b = -1;
	for(__int128 i = 1; s2 <= n; i++){
		__int128 disc = (2ll * s1)*(2ll * s1) - (4ll * i * (s2 - n));
		if(disc%(i*i) == 0){
			__int128 tmp = sq(disc);
			__int128 A = (-(2ll * s1) + tmp);
			//quadratic formula yayy
			//moo("%lld %lld %lld %lld %lld\n", i, s1*2ll, s2 - n, disc, A);
			if(!(tmp*tmp != disc || A%(i * 2ll) != 0)){
				a = A/(i * 2ll);
				b = a + i;
				break;
			}
		}
		s1 += i;
		s2 += i*i;
	}
	if(a == 0) a++;
	cout << a << " " << b << "\n";
}

ll Pow(ll a){
	if(a == 0) return 0;
	ll ans = 1;
	for(int i = 0; i<k; i++){
		if(n/ans < a) return -1;
		ans *= a;
	}
	return ans;
}

void k_3(){ //for all cases k >= 3
	//here the important thing to note is that 1e18^6 -> 1e6, so you can now run a brute force
	//since (n^(1/k)) ^k will be >= n in a sense, it is impossible for any number > n^(1/k) to be in the answer
	int R = 0;
	for(int i = 0; Pow(i) >= 0; i++){
		arr[R++] = Pow(i);
	}
	
	ll l = 0, r = 0, tot = 0;

	for(int i = 0; i<R; i++){ //am *i* a joke to you
		while(r+1 < R && tot + arr[r+1] <= n){
			r++;
			tot += arr[r];
		}
		if(tot == n) break;
		tot -= arr[l];
		l++;
	}
	if(l == 0) l++;
	if(tot != n) cout << "-1 -1\n";
	else cout << l << " " << r + 1 << "\n";
}

int main(){
  cin.tie(0) -> sync_with_stdio(0);
	cin >> T;
	while(T--){
		cin >> n >> k;
		if(k == 1){
			k_1();
		}else if(k == 2){
			k_2();
		}else{
			k_3(); //great naming btw
		}
	}
  return 0;
}


