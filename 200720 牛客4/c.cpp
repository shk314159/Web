#include<bits/stdc++.h>
#define ll long long
#define INF 0x3f3f3f3f
#define LLINF 0x3f3f3f3f3f3f3f3f
#define pii pair<int,int>
#define vi vector<int>
#define SZ(x) (int)x.size()
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define mod 1000000007
#define N 1000005
using namespace std;
bool notp[N];
int prime[N], pnum;
int dp[N];
void sieve() {
    memset(notp, 0, sizeof(notp));
    memset(dp, 0, sizeof(dp));
    notp[0] = notp[1] = 1;
    pnum = 0;
    dp[1]= dp[0] = 0;
    for(int i = 2; i < N; i++) {
        if(!notp[i]) {
            prime[++pnum] = i;
            dp[i] = 1;
        }
        for(int j = 1; j <= pnum && prime[j] * i < N; j++) {
            notp[i * prime[j]] = 1;
            dp[i * prime[j]] = max(dp[i] + 1, dp[i * prime[j]]);
            if(i % prime[j] == 0) break;
        }
    }
}
ll powmod(ll a, ll b) {
    ll res = 1;
    a = a % mod;
    while(b) {
        if(b & 1) {
            res = res * a % mod;
        }
        a = a * a % mod;
        b >>= 1;
    }
    return res % mod;
}
int main(){
    sieve();
    int t;
    scanf("%d", &t);
 
    while(t--) {
        ll n, c;
        scanf("%lld%lld", &n, &c);
        printf("%lld\n", powmod(c, dp[n]));
    }
}
