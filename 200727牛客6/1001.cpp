#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
#define N 100005
#define mod 998244353
int f[N];
int a[N];
int vis[N];
int powmod(int a, int b) {
	int res = 1;
	while(b) {
		if(b & 1) {
			res = (ll)res * a % mod;
		}
		a = (ll)a * a % mod;
		b >>= 1;
	}
	return res;
}
void init() {
	f[2] = 4;
	for(int i = 3; i < N; i++) {
		f[i] = (ll)(f[i - 1] + 1) * i % mod * powmod(i - 1, mod - 2) % mod;
	}
}
int main() {
	init();
	int n, m;
	scanf("%d%d", &n, &m);
	while(m--) {
		for(int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			vis[i] = 0;
		}
		ll res = 0;
		for(int i = 1; i <= n; i++) {
			if(vis[i]) continue;
			vis[i] = 1;
			int st = a[i];
			int sum = 1;
			while(st != i) {
				vis[st] = 1;
				st = a[st];
				sum++;
			}
			res = (res + f[sum]) % mod;
		}
		printf("%d\n", res);
	}
}

