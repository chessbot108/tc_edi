///made by : Mr_Ph :D
#include<iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#include<unordered_map>
typedef long long ll;
typedef long long int lli;
//typedef int long long;
//typedef unsigned long long ull;
using namespace std;
const double PI=acos(-1.0);
const ll mod=(ll)1e18;
///the defines :)
#define endl '\n'
#define vi vector<int>
#define vll vector<ll>
#define lower(s) transform(s.begin(),s.end(),s.begin(),::tolower)
#define upper(s) transform(s.begin(),s.end(),s.begin(),::toupper)
#define ent_arr for(int i=0;i<n;i++)cin>>arr[i];
#define all(arr) arr.begin(),arr.end()
#define allr(arr) arr.rbegin(),arr.rend()
#define sz size()
///the end of the defines
ll power(ll n,ll m){
if (m==0)return 1;
if (m==1)return n%mod;
ll r=(power(n%mod,m/2));
if (m%2) return (((r*r)%mod)*(n%mod))%mod;
else return (r*r)%mod;
}
void solve()
{
    int d;
    cin>>d;
    ll t=d;
    int x=1;
    while(d--)
    {
        ll l=1,r=1;
        ll sum=0;
        ll n,m;
        cin>>n>>m;
        bool valid=false;
        for (ll i=1; i<=min(n,200000000/t); i++)
        {
            if (sum<n)
            {
                sum+=(power(r,m));
                r++;
            }
            else if (sum>n)
            {
                sum-=(power(l,m));
                l++;
            }
            else
            {
                cout<<l<<" "<<r<<endl;
                valid=true;
                break;
            }
        }
        if(!valid)
        cout<<-1<<" "<<-1<<endl;
    }
}
int main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(0);
    // freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int t=1;
    //cin>>t;
    while(t--)
        solve();
}
