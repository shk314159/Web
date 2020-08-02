//矩阵
#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
#define N 205
#define mod 998244353
typedef long long ll;
ll powmod(ll a, ll b) {
    ll res = 1;
    a = a % mod;
    while(b) {
        if(b & 1) {
            res = res * a % mod;
        }
        a = a * a % mod;
        b >>= 1;
    }
    return res % mod;
}
ll inv(ll p) {
    return powmod(p, mod - 2);
}
ll is[N], js[N];
class mat {
public:
    int n,m;
    ll v[N][N];
    mat(int n,int m) : n(n), m(m){memset(v, 0, sizeof(v));}
    void init() {   
        memset(v, 0, sizeof(v));
    }
    void init1() {
        for(int i = 0; i < N; i++)
            for(int j = 0; j < N; j++)
                v[i][j] = (i == j); //单位矩阵
    }
    mat operator * (const mat B) const {//矩阵乘法 A(n,k)*B(k,m)=C(n,m);
        mat C(n, B.m);
        C.init();
        for(int i = 1; i <= n; i++)
        for(int j = 1; j <= B.m; j++)
        for(int k = 1; k <= m; k++)
            C.v[i][j] = (C.v[i][j] + v[i][k] * B.v[k][j]) % mod;//Mod
        return C;
    }
    mat operator ^ (int t)//矩阵快速幂 n=m时可用 
    {
        mat ans(n, n), now(n, n);
        ans.init1();
        for(int i = 1; i <= n; i++)
            for(int j = 1; j <= n; j++)
                now.v[i][j] = v[i][j];
        while(t > 0) {
            if(t & 1) ans = ans * now;
            now = now * now;
            t >>= 1;
        }
        return ans;
    }
    void change() { // 转置 
    	swap(n, m);
		for(int i = 1; i <= max(n, m); i++) {
			for(int j = i + 1; j <= max(n, m); j++) {
				swap(v[i][j], v[j][i]);
			}
		} 
	} 
	void Minv() {  // 逆矩阵 
		for(int k = 1; k <= n; k++) {
	        for(int i = k; i <= n; i++) // 1
	            for(int j = k; j <= n; j++)
	                if(v[i][j]) {
	                    is[k] = i;
	                    js[k] = j;
	                    break;
	                }
	        for(int i = 1; i <= n; i++) // 2
	            swap(v[k][i], v[is[k]][i]);
	        for(int i = 1; i <= n; i++)
	            swap(v[i][k], v[i][js[k]]);
	        v[k][k] = inv(v[k][k]); // 3
	        for(int j = 1; j <= n; j++)
	            if(j != k) // 4
	            	v[k][j] = v[k][j] * v[k][k] % mod;
	        for(int i = 1; i <= n; i++)
	            if(i != k) // 5
	            for(int j = 1; j <= n; j++)
	                if(j != k)
	                    v[i][j] = (v[i][j] + mod - v[i][k] * v[k][j] % mod) % mod;
	        for(int i = 1; i <= n; i++)
	            if(i != k)
	            v[i][k] = (mod - v[i][k] * v[k][k] % mod) % mod;
	    }
	    for(int k = n; k; k--) { // 6
	        for(int i = 1; i <= n; i++)
	            swap(v[js[k]][i], v[k][i]);
	        for(int i = 1; i <= n; i++)
	            swap(v[i][is[k]], v[i][k]);
	    }
	}
};
int main() {
	int n;
	while(~scanf("%d", &n)) {
		mat a(n, n);
		mat b(1, n);
		for(int i = 1; i <= n; i++) {
			for(int j = 1; j <= n; j++) {
				scanf("%lld", &a.v[i][j]);
			}
		}
		for(int i = 1; i <= n; i++) {
			scanf("%lld", &b.v[1][i]);
		}
		a.Minv();
		mat c = b * a;
		b.change();
		c = c * b;
		printf("%lld\n", c.v[1][1]);
	}
} 
