#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
const int M = 200005, base = M / 2, N = 2005;

struct point {
    int w, v, d;
}a[N << 1];
ll dp[2][M];
const ll inf = 1e18;

int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        int n, m;
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; i++) {
            scanf("%d%d", &a[i].w, &a[i].v);
            a[i].d = 1;
        }
        for(int i = 1; i <= m; i++) {
            scanf("%d%d", &a[n + i].w, &a[n + i].v);
            a[n + i].d = -1;
        }
		random_shuffle(a + 1, a + n + m + 1);
        ll *dp1 = dp[0] + base;
        ll *dp2 = dp[1] + base;
		dp2[0] = 0;
        int lim = sqrt(n + m) * 1000 * 2;
        int L = 0, R = 0;
        for(int i = 1; i <= n + m; i++) {
            if(a[i].d == 1) {
                int nr = min(R + a[i].w, lim);
                for(int j = L; j <= R; j++) {
                    dp1[j] = dp2[j];
                }
                for(int j = R + 1; j <= nr; j++) {
                    dp1[j] = -inf;
                }
                for(int j = L; j <= nr - a[i].w; j++) {
                    dp1[j + a[i].w] = max(dp1[j + a[i].w], dp2[j] + a[i].v);
                }
                R = nr;
            }
            else {
                int nl = max(L - a[i].w, -lim);
                for(int j = L; j <= R; j++) {
                    dp1[j] = dp2[j];
                }
                for(int j = nl; j <= L - 1; j++) {
                    dp1[j] = -inf;
                }
                for(int j = nl + a[i].w; j <= R; j++) {
                    dp1[j - a[i].w] = max(dp1[j - a[i].w], dp2[j] + a[i].v);
                }
                L = nl;
            }
            swap(dp2, dp1);
        }
//		cout << "test : " << dp[n + m][200000 + 1000] << " " << dp[n + m][200000 - 200] << " " << dp[n + m][200000 - 800] << " " << dp[n + m][200000 - 1000] << '\n';
        printf("%lld\n", dp2[0]);
    }
}
