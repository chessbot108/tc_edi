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

const int maxn = 1e5 + 10;

int n;
ll x;
int t[maxn], r[maxn];

bool check(ll v) {
    ll sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += max((ll)0, v - t[i]) / r[i];
        if (sum >= x) return true;
    }
    return false;
}

int main() {
    scanf("%d%lld", &n ,&x);
		for (int i = 0; i < n; ++i) {
				scanf("%d%d", &t[i], &r[i]);
		}
    ll l = 0, r = 2e15;
    while (l + 1 < r) {
        ll mid = (l + r) >> 1;
			  if (check(mid)) r = mid;
        else l = mid;
    }
    printf("%lld", r);
		return 0;
}
