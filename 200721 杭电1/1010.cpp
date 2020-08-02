#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
#define N 100000000
#define M 11000
#define mod 998244353
#define inv2 499122177
inline int powmod(int a, int b) {
    int res = 1;
    a = a % mod;
    while(b) {
        if(b & 1) res = (ll)res * a % mod;
        a = (ll)a * a % mod;
        b >>= 1;
    }
    return res;
}
int inv[N + 5];
void init() {
    inv[1] = 1;
    for(int i = 2; i <= N; i++) {
        inv[i] = (ll)(mod - mod / i) * inv[mod % i] % mod;
    }
    for(int i = 2; i <= N; i++) {
        inv[i] = (inv[i] + inv[i - 1]) % mod;
    }
}
int v[50], top;
int res, n;
void dfs(int id, int d, int mu) {
    if(id == top + 1) {
        mu = (mu + mod) % mod;
        res = (res +  (ll)mu * (inv[d] - inv[d - 1] + mod) % mod * inv[n / d] % mod) % mod;
        return;    
    }
    dfs(id + 1, d, mu);
    dfs(id + 1, d * v[id], -mu);
}
int main() {
    init();
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        if(n == 2) {
            printf("%d\n", inv2);
            continue;
        }
        int y = n;
        top = 0;
        ll invn = powmod(n, mod - 2);
        for(int i = 2; i * i <= n; i++) {
            if(n % i == 0) {
                v[++top] = i;
                while(n % i == 0) {
                    n /= i;
                }
            }
        }
        if(n != 1) {
            v[++top] = n;
        }
        n = y;
        res = 0;
        dfs(1, 1, 1);
        res = (1ll * res * invn % mod + inv2) % mod;
        printf("%lld\n", res);
    }
}

