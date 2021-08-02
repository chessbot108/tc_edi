#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <string>
#include <string.h>
#include <utility>
#include <map>
#include <list>
using namespace std;
typedef pair <int, int> pii;
typedef long long ll;
#define pb push_back 
#define mp make_pair
#define f first
#define s second

const int maxn = 1e5 + 10, MOD = 1e9 + 7;

int n, x;
ll sum[maxn << 2], mul[maxn << 2];

ll find_inv(int x) {
    ll pw = MOD - 2, v = x, ans = 1;
    for (int i = 0; i < 31; ++i) {
        if ((1 << i) & pw) {
            ans *= v;
            ans %= MOD;
        }
        v *= v;
        v %= MOD;
    }
    return ans;
}

void push_down(int id) {
    int lc = id << 1, rc = id << 1 | 1;
    mul[lc] *= mul[id], sum[lc] *= mul[id];
    mul[lc] %= MOD, sum[lc] %= MOD;
    mul[rc] *= mul[id], sum[rc] *= mul[id];
    mul[rc] %= MOD, sum[rc] %= MOD;
    mul[id] = 1;
}

void add_helper(int id, int l, int r, int p, int v) {
    if (p < l || p > r) return;
    if (p == l && p == r) {
        sum[id] += v;
        sum[id] %= MOD;
        return;
    }
    push_down(id);
    int lc = id << 1, rc = id << 1 | 1, mid = (l + r) >> 1;
    add_helper(lc, l, mid, p, v);
    add_helper(rc, mid + 1, r, p, v);
    sum[id] = sum[lc] + sum[rc];
    sum[id] %= MOD;
}

void add(int p, int v) {
    add_helper(1, 0, n - 1, p, v);
}

void mult_helper(int id, int l, int r, int ql, int qr, int v) {
    if (r < ql || l > qr) return;
    if (ql <= l && r <= qr) {
        mul[id] *= v;
        sum[id] *= v;
        mul[id] %= MOD;
        sum[id] %= MOD;
        return;
    }
    push_down(id);
    int lc = id << 1, rc = id << 1 | 1, mid = (l + r) >> 1;
    mult_helper(lc, l, mid, ql, qr, v);
    mult_helper(rc, mid + 1, r, ql, qr, v);
    sum[id] = sum[lc] + sum[rc];
    sum[id] %= MOD;
}

void mult(int l, int r, int v) {
    mult_helper(1, 0, n - 1, l, r, v);
}

ll query_helper(int id, int l, int r, int ql, int qr) {
    if (r < ql || l > qr) return 0;
    if (ql <= l && r <= qr) return sum[id];
    push_down(id);
    int lc = id << 1, rc = id << 1 | 1, mid = (l + r) >> 1;
    return (query_helper(lc, l, mid, ql, qr) + query_helper(rc, mid + 1, r, ql, qr)) % MOD;
}

ll query(int l, int r) {
    if (l > r) return 0;
    return query_helper(1, 0, n - 1, l, r);
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &x);
        if (n == 1) {
            printf("1\n");
            continue;
        }
        ll inv = find_inv(x);
        for (int i = 0; i < (n << 2); ++i) {
            sum[i] = 0;
            mul[i] = 1;
        }
        add(0, 1);
        for (int i = 2; i <= n; ++i) {
            int q = x / i, r = x - q * i;
            ll addv = 0;
            if (r) addv += (query(0, r - 1) * (ll)(q + 1)) % MOD * inv;
            addv %= MOD;
            addv += query(r, i - 2) * q % MOD * inv;
            addv %= MOD;
            add(i - 1, addv);
            mult(0, i - 2, (q * inv) % MOD);
        }
        ll ans = query(0, n - 1);
        if (ans < 0) ans += MOD;
        printf("%lld\n", ans);
    }
}