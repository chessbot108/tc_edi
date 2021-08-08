#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define pb emplace_back
#define fi first
#define se second
#define mp make_pair
#define all(x) x.begin(), x.end()
#define in(x); { for (auto &qwertyuiop : x) cin >> qwertyuiop; }
#define out(x); { for (auto qwertyuiop : x) cout << qwertyuiop << ' '; cout << endl; }
#define unq(x); { sort(x.begin(), x.end()); x.resize(unique(x.begin(), x.end()) - x.begin()); }
//#define int long long

using namespace std;
using namespace __gnu_cxx;
using namespace __gnu_pbds;

typedef long long ll;
typedef unsigned long long ull;
typedef vector <int> vi;
typedef vector <long long> vll;
typedef pair <int, int> pii;
typedef pair <short, short> pss;
typedef vector <pair <int, int>> vii;
typedef tree <int, null_type, less <int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

const int INF = 1e9;
const long long INFll = 2e18;
const long long base1 = 239;
const long long base2 = 653;
const long long mod = 1e9 + 7;
const int N = 1e5;
const long double pi = 3.1415926;


void solve() {
    ll n, k; cin >> n >> k;

    for (ll len = 1; len * len <= 10 * n; len++) {
        ll n2 = n - (len * (len - 1) / 2);
        if (n2 % len) continue;
        if (n2 + len > n) continue;

        cout << max((ll)1, n2 / len) << " " << n2 / len + len << "\n";
        return;
    }
    cout << "-1 -1\n";
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);

/*#ifndef FOREST
    freopen("substr3.in", "r", stdin);
    freopen("substr3.out", "w", stdout);
#endif // FOREST*/

    int t = 1;
    cin >> t;
    while (t--) solve();
}