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
using namespace std;
#define N 20
map<array<int, 10>, ll> dp[20][2];
array<int, 10> v = {0};
int len, d;
int dp2[N];
int dig[N];
ll c[N][N];
void Cinit() {
    for (int i = 0; i < N; i++) {
        c[i][0] = c[i][i] = 1;
		for(int j = 1; j < i; j++) {
			c[i][j] = c[i - 1][j - 1] + c[i - 1][j];
		}
    }
}

ll dfs(int pos, int limit, int lead) {
	if(!limit && dp[pos][lead].find(v) != dp[pos][lead].end()) return dp[pos][lead][v];
    if(!pos) {
       for(int i = 0; i <= 9; i++) {
	        if(i == d) continue;
	        if(v[i] >= v[d]) return dp[pos][lead][v] = 0;
	    }
	    return dp[pos][lead][v] = 1;
    }
    
    ll res = 0;
    int top = limit ? dig[pos] : 9;
    if(lead && !limit) {//
    	for(int i = 0; i <= pos; i++) {
    		for(int j = 0; j <= pos - i; j++) 
				dp2[j] = 0;
    		dp2[pos - i] = c[pos][i];
    		for(int j = 0; j < 10; j++) {
    			if(j == d) continue;
    			if(v[d] + i <= v[j]) {
    				dp2[0] = 0;
    				break;
				}
				for(int k = 0; k <= pos - i; k++) {
					for(int l = 1; l <= min(k, v[d] + i - v[j] - 1); l++) {
						dp2[k - l] += c[k][l] * dp2[k];
					}
				}
			}
			res += dp2[0];
		}
		return dp[pos][lead][v] = res;
	}
	for(int i = 0; i <= top; i++) {
		if(lead || i) {
			if(i == d || v[i] + 2 < v[d] + pos) {
				v[i]++;
				res += dfs(pos - 1, limit && i == dig[pos], 1);
				v[i]--;
			}
		}
		else {
			res += dfs(pos - 1, limit && i == dig[pos], 0);
		}
	}
	if(!limit) {
		dp[pos][lead][v] = res;
	}
	return res;
	
}
ll solve(ll x) {
    len = 0;
    while(x) {
        dig[++len] = x % 10;
        x /= 10;
    }
    return dfs(len, 1, 0);
}
void init() {
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < 2; j++) dp[i][j].clear();
	}
}
int main(){
    int t;
    Cinit();
//    for(int i = 0; i < 10; i++) v.push_back(0);
    scanf("%d", &t);
    while(t--) {
        ll l, r;
        scanf("%lld%lld%d", &l, &r, &d);
       	init();
        printf("%lld\n", solve(r) - solve(l - 1));
    }
}
