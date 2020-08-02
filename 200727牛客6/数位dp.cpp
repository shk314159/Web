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
#define mod 1000000007
#define N 105
int dig[N];
ll dp[N][2005][2][2][2][2][2];

ll dfs(int pos, int sum, int eq, int lead1, int limit1, int lead2, int limit2) {
    if (pos < 0) {
        if (eq) return 0;
        else return sum > 0;
    }
    if (dp[pos][sum + 1000][eq][lead1][limit1][lead2][limit2] != -1) {
        return dp[pos][sum + 1000][eq][lead1][limit1][lead2][limit2];
    }
    ll res = 0;
    int top1 = limit1 ? dig[pos] : 9;
    int top2 = limit2 ? dig[pos] : 9;
    for (int i = 0; i <= top1; i++) {
        int nxlead1 = (lead1 && i == 0);
        int nxlimit1 = (limit1 && i == top1);
        int stj = eq ? i : 0;
		for (int j = stj; j <= top2; j++) {
            int nxlead2 = (lead2 && j == 0);
            int nxlimit2 = (limit2 && j == top2);
            int nxeq = (eq && (i == j));
            res = (res + dfs(pos - 1, sum + i - j, nxeq, nxlead1, nxlimit1, nxlead2, nxlimit2)) % mod;
        }

    }
	dp[pos][sum + 1000][eq][lead1][limit1][lead2][limit2] = res;
    return res;
}

ll solve(string s) {
    memset(dp, -1, sizeof(dp));
    int len = 0;
    for (int i = s.length() - 1; i >= 0; i--) {
        dig[len++] = s[i] - '0';
    }
    return dfs(len - 1, 0, 1, 1, 1, 1, 1);
}

int main() {
    string s;
    cin >> s;
    printf("%lld\n", solve(s));
}
