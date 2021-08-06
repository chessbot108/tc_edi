#include <set>
#include <iomanip>
#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <chrono>
#include <random>
#define uid(a, b) uniform_int_distribution<int>(a, b)(rng)
#define ll long long
#define pb push_back
#define lb long double
#define mp make_pair
using namespace std;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

struct pt {
    double x, y;
};

bool cmp(pt a, pt b) {
    return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool cw(pt a, pt b, pt c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) < 0;
}

bool ccw(pt a, pt b, pt c) {
    return a.x*(b.y-c.y)+b.x*(c.y-a.y)+c.x*(a.y-b.y) > 0;
}

void convex_hull(vector<pt>& a) {
    if (a.size() == 1)
        return;

    sort(a.begin(), a.end(), &cmp);
    pt p1 = a[0], p2 = a.back();
    vector<pt> up, down;
    up.push_back(p1);
    down.push_back(p1);
    for (int i = 1; i < (int)a.size(); i++) {
        if (i == a.size() - 1 || cw(p1, a[i], p2)) {
            while (up.size() >= 2 && !cw(up[up.size()-2], up[up.size()-1], a[i]))
                up.pop_back();
            up.push_back(a[i]);
        }
        if (i == a.size() - 1 || ccw(p1, a[i], p2)) {
            while(down.size() >= 2 && !ccw(down[down.size()-2], down[down.size()-1], a[i]))
                down.pop_back();
            down.push_back(a[i]);
        }
    }

    a.clear();
    for (int i = 0; i < (int)up.size(); i++)
        a.push_back(up[i]);
    for (int i = down.size() - 2; i > 0; i--)
        a.push_back(down[i]);
}


int main(){
	cin.tie(0) -> sync_with_stdio(0);
	//freopen("in.txt", "r", stdin);
	int T, k;
	cin >> T >> k;
	//T = 1000;
	int t = T;
	ll tot = 0, tot1 = 0, cbrt = 0;
	while(T--){
		int n;
		n = k;
		//cin >> n;
		ll a, b, c, d;
		a = uid(1, 1e9), b = uid(1, 1e9);
		c = uid(1, 1e9), d = uid(1, 1e9);
		vector<pt> ve;
		for(int i = 0; i<n; i++){
			ll x = a*c %(ll)1e9;
			ll y = b*d %(ll)1e9;
			ve.pb({x, y});
			a = x, b = y;
		}
		convex_hull(ve);
		tot += (int)(ve.size());
		tot1 += cbrt;
		//cout << ve.size() << " " << cbrt << "\n";
	}
	lb ra = (lb)tot/(lb)tot1, ra1 = (lb)tot/(lb)t;
	cout << tot << " " << tot1 << fixed << setprecision(6) << " " << ra << " " << ra1 << "\n";
	return 0;
}
