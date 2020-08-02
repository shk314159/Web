#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
#define N 1000005
#define mod 998244353
ll powmod(ll a, ll b){
	ll res = 1;
	a %= mod;
	while(b) {
		if(b & 1) {
			res = res * a % mod;
		}
		b >>= 1;
		a = a * a % mod;
	}
	return res % mod;
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
ll c(ll n, ll m) { // 数据范围很大不够 
	if(m > n) {
		return 0;
	}
	if(m == 0) return 1;
	if(n < N) return fac[n] * inv[m] % mod * inv[n - m] % mod;
	//c(m,k) = m!/(k! * (m - k))= m-k+1~m/(k!)
	ll res = inv[m];
	for(int i = n - m + 1; i <= n; i++) {
		res = res * i % mod;
	}
	return res;
}
int main() {
	init();
	int t;
	scanf("%d", &t);
	while(t--) {
		int n, m, k;
		scanf("%d%d%d", &n, &m, &k);
		if(n > m) swap(n, m);
		ll res = 0;
		for(int i = 0; i <= n - k; i++) {
			res = ((ll)res + c(k + i - 1, i) * c(k + n - k - i - 1, n - k - i) % mod * c(k + m - k - i - 1, m - k - i) % mod) % mod;
		}
		printf("%lld\n", res);
	}
}

