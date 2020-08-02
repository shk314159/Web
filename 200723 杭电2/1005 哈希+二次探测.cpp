#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define inf_int 0x3f3f3f3f
#define inf_ll 0x3f3f3f3f3f3f3f3f
const int MAXN = 2e6 + 5;
const ll mod = 1e9 + 7;
const ll mod2 = 1e9 + 9;
ll qmul(ll x, ll y, ll mod) {
    return (x * y - (long long)(x / (long double)mod * y + 1e-3) *mod + mod) % mod;
}
ll fib[MAXN];
ll fib2[MAXN];
int a[MAXN], b[MAXN], c[MAXN];
int main() {
    fib[0] = fib[1] = 1;
    fib2[0] = fib2[1] = 1;
    for (int i = 2; i < MAXN; i++) {
        fib[i] = (fib[i - 1] + fib[i - 2]) % mod;
        fib2[i] = (fib2[i - 1] + fib2[i - 2]) % mod2;
    }

    int T;
    scanf("%d", &T);
    while (T--) {
        int na, nb, nc;
        scanf("%d", &na);
        for (int i = 1; i <= na; i++) scanf("%d", &a[i]);
        scanf("%d", &nb);
        for (int i = 1; i <= nb; i++) scanf("%d", &b[i]);
        scanf("%d", &nc);
        for (int i = 1; i <= nc; i++) scanf("%d", &c[i]);
        ll aa = 0ll, bb = 0ll, cc = 0ll;
        ll a2 = 0, b2 = 0, c2 = 0;
		for (int i = 1; i <= na; i++) {
            if (a[i]) {
                aa = (aa + fib[i]) % mod ;
				a2 = (a2 + fib2[i]) % mod2 ;
            }
        }
        for (int i = 1; i <= nb; i++) {
            if (b[i]) {
                bb = (bb + fib[i]) % mod;
				b2 = (b2 + fib2[i]) % mod2;
            }
        }
        for (int i = 1; i <= nc; i++) {
            if (c[i]) {
                cc = (cc + fib[i]) % mod;
                c2 = (c2 + fib2[i]) % mod2;

            }
        }
//        printf("%lld %lld %lld\n", aa, bb, cc);
        int res = 0;
        ll pos = (qmul(aa,bb,mod) - cc + mod) % mod;
		ll pos2 = (qmul(a2,b2,mod2) - c2 + mod2) % mod2;  
        for (int i = 1; i <= na + nb + 1; i++) {
            if (pos == fib[i] && pos2 == fib2[i]) {
                res = i;
                break;
            }
        }
        printf("%d\n", res);

    }
}
