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

int n, x;
int t[maxn], r[maxn];

bool check(int v) {
    ll sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += max(0, v - t[i]) / r[i];
        if (sum >= x) return true;
    }
    return false;
}

int main() {
    freopen("9.in", "r", stdin);
    freopen("9.out", "w", stdout);
    scanf("%d%d", &n ,&x);
    for (int i = 0; i < n; ++i) {
        scanf("%d%d", &t[i], &r[i]);
    }
    int l = 0, r = 2e9;
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        if (check(mid)) r = mid;
        else l = mid;
    }
    printf("%d", r);
}