#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
#define mod 1000000007
int c[1010][1010];
ll dp[1010][1010];
void init() {
	pre[1] = 1;
	for(int i = 0; i <= 1000; i++) {
		c[i][0] = 1;
	} 
	for(int i = 1; i <= 1000; i++) {
		for(int j = 1; j <= min(i, 999); j++) {
			c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
		}
	}
}
int main() {
	int t;
	init();
	scanf("%d", &t);
	while(t--) {
		int n, m;
		cin >> n >> m;
		if(n == 1 && m == 0) {
			printf("1\n");
			continue;
		}
		else if(n == 1 && m != 0) {
			printf("-1\n");
			continue;
		}
		else if(m >= n - 1) {
			printf("-1\n");
			continue;
		}
		memset(dp, 0x3f3f3f3f3f3f, sizeof(dp));
		dp[1][0] = dp[2][0] = 1;
		for(int i = 2; i <= n; i++) {
			for(int j = 0; j <= i - 1; j++) {
				dp[i][j] = max()
	
		}
		printf("%d\n", res);
	}
}

