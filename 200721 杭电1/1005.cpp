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
#define mod 1000000009
using namespace std;
const int N = 1e5 + 5;
const int v5 = 383008016;
const int v51 = 276601605;
const int a = 691504013;
const int ad = 691504012;//a^-1
const int b = 308495997;
inline int powmod(int a, ll b) {
    int res = 1;
    a = a % mod;
    while(b) {
        if(b & 1) res = (ll)res * a % mod;
        a = (ll) a * a % mod;
        b >>= 1;
    }
    return res;
}
ll fac[N], inv[N];
void init() {
    fac[0] = 1;
    for(int i = 1; i < N; i++) {
        fac[i] = fac[i - 1] * i % mod;
    }
    inv[N - 1] = powmod(fac[N - 1], mod - 2);
    for(int i = N - 2; i >= 0; i--) {
        inv[i] = inv[i + 1] * (i + 1) % mod;
    }
}
inline int C(int n, int m) {
    if(m > n) {
        return 0;
    }
    if(m == 0) {
        return 1;
    }
    return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
int main(){
   init();
   
   int t;
   scanf("%d", &t);
   while(t--) {
        ll n, c;
		int k;
        scanf("%lld%lld%d", &n, &c, &k);
        int sum = 0;
		int add = powmod((ll)ad * b % mod, c);//Ôö¼Ó 
		int n1 = (n + 1) % (mod - 1);//½µÃÝ 
		int n0 = (n + 1) % mod;
		int q1 = powmod(a, c);
		int  q = powmod(q1, k);
		int st = powmod(q, n1);
		int d1 = powmod(add, n1);
		for(int i = 0; i <= k; i++) {
			int cnt = C(k, i);
			if(i & 1) cnt = mod - cnt;
			if(q == 1) {
				sum= ((ll)sum + (ll)n0 * cnt % mod) % mod;
			}
			else 
				sum = ((ll)sum + (ll)(st - 1 + mod) % mod * powmod(q - 1, mod - 2) % mod * cnt % mod) % mod;
			q = (ll)q * add % mod;
			st = (ll)st * d1 % mod;
		}
        printf("%d\n", (ll)sum * powmod(v51, k) % mod);
   }
}
