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
#define uid(a, b) uniform_int_distribution<ll>(a, b)(rng)
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

char inp[20];

int main(){
  cin.tie(0) -> sync_with_stdio(0);
	int t, SED; cin >> t >> SED;
	sprintf(inp, "%d.in", t);
	mt19937_64 rng(SED);
	freopen(inp, "w", stdout); //just makes t.in the output where t is inputted to the program

	int a, b, c; cin >> a >> b >> c;
	//a -> k=2, b -> k=3, c->k=1
	
	int T = 10; cout << T << "\n";
	const ll nmm = 1e18;
	for(int t = 0; t<T; t++){
		int op = uid(0, a+b+c);
		if(t%4 == 5){
			ll q = (ll)(rng()%(int)(1e8));
			cout << q*q << " " << uid(2, 10) << "\n";
		}else if(op <= a){
			int a = uid(1e6, 2e6), b = a + uid(1e6, a);
			ll tot = 0;
			for(int i = a; i<b && tot + ((ll)i*(ll)i) <= nmm; i++) tot += (ll)i*(ll)i;
			if(t%4 != 0) tot++;
			assert(tot <= (ll)(nmm));
			cout << tot << " 2\n";
		}else if(op <=a+b){
			int k = uid(2, 20), a = uid(1, 6), b = a;
			ll tot =0;
			for(int i = a;; i++){
				ll p = 1;
				for(int j = 0; j<k; j++){
					if(p > nmm/(ll)i){
						p = -1; break;
					}		
					p *= (ll)i;
				}
				if(tot + p <= nmm && p != -1){
					tot += p;
					b++;
				}else{
					break;
				}
			}
			cout << tot << " " << k << "\n";
		}else{
		ll q = (ll)(rng()%(int)(1e8));
		cout << q*q << " 1\n";	
		}
	}
	
  return 0;
}


