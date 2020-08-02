#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
#define N (int)1e5 + 5
void exgcd(ll a, ll b, ll & g,ll &x, ll &y) {
	if(!b) {
		g = a;
		x = 1;
		y = 0;
		return ;
	}
	exgcd(b,a%b,g,y,x);
	y-=(a/b)*x;
}
ll getInv(ll a, ll mod) {
	ll x, y, g;
	exgcd(a, mod, g, x, y); // ax + mod * y = 1
	x = (x % mod + mod) % mod;
	return x;
}
int a[N];
int vis[N];
int q[N], qnum;
int tp[N];
void find(int x) {
	qnum = 0;
	while(!vis[x]) {
		vis[x] = 1;
		q[++qnum] = x;
		x = a[x];
	}
}
int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	for(int i = 1; i <= n; i++) {
		scanf("%d", &a[i]);
	}
	memset(vis, 0, sizeof(vis));
	for(int i = 1; i <= n; i++) {
		if(!vis[i]) {
			find(i);
			int d = getInv(k, qnum);
			for(int j = 1, dd = 1; j <= qnum; j++) {
				tp[j] = q[dd];
				dd = (dd + d - 1) % qnum + 1;
			}
			tp[qnum + 1] = tp[1];
			for(int j = 1; j <= qnum; j++) {
				a[tp[j]] = tp[j + 1];
			}
		}
	}
	for(int i = 1; i < n; i++) {
		printf("%d ", a[i]);
	}
	printf("%d\n", a[n]);
}

