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


vector<pair<int, pii>> edges;
int par[MX], sz[MX];

int find(int x){ if(par[x] != x) par[x] = find(par[x]); return par[x]; }
void mkdsu(){ for(int i = 0; i<=2e5; i++) par[i] = i, sz[i] = 1; }
void Union(int a, int b){
	a = find(a), b = find(b);
	if(a == b) return ;
	if(sz[a] < sz[b]) swap(a, b);
	par[b] = a;
}


int Pow(int a, int k){
	int ans = 1;
	for(int i = 1; i<=k; i *= 2){
		if(k&i) ans *= a;
		a *= a;
	}
	return ans;
}

bool cmp(const pair<int, pii>& a, const pair<int, pii>& b){
	return a.first > b.first; 
}

int main(){
  cin.tie(0) -> sync_with_stdio(0);
	int T; cin >> T;
	while(T--){
		int d, k, n, m, l, O; //d will probably always be 4
		cin >> d >> k >> n >> m >> l >> O;
		//l = m = n; //loool
		//n <= m <= l
		mkdsu(); edges.clear();
		for(int i = 0; i<n; i++){
			for(int j = 0; j<m; j++){
				for(int h = 0; h<l; h++){
					for(int o = 0; o<O; o++){
						for(int a = 0; a<n; a++){
							for(int b = 0; b<m; b++){
								for(int c = 0; c<l; c++){
									for(int e = 0; e<O; e++){
										int A = i*l*m*O + j*l*O + h*O + o, B = a*l*m*O + b*l*O + c*O + e;
										int C = abs(i - a), D = abs(j - b), E = abs(h - c), F = abs(o - e);
										edges.pb(mp(Pow(C, k) + Pow(D, k) + Pow(E, k) + Pow(F, k), mp(A, B)));
									}
								}
							}
						}
					}
				}
			}
		}
		sort(edges.begin(), edges.end(), cmp);
		ll ans = 0;
		for(int i = 0; i<siz(edges); i++){
			int u = edges[i].second.second, v = edges[i].second.first, w = edges[i].first;
			
			//moo("%d, {%d %d %d} {%d %d %d}: %d \n", find(u) != find(v), u/(m*l), (u%(m*l))/l, u%l, v/(m*l), (v%(m*l))/l, v%l, w);
			if(find(u) != find(v)){
				//moo("{%d %d %d} {%d %d %d}: %d \n", u/(m*l), (u%(m*l))/l, u%l, v/(m*l), (v%(m*l))/l, v%l, w);
				Union(u, v);
				ans += w;
			}
		}
		cout << ans << "\n";
	}
  return 0;
}


