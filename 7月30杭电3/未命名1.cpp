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
struct point {
    double x, y;
    point(double _x = 0,double _y = 0):x(_x), y(_y){}
    point eotate(point const &o, double angle) {//绕p点逆时针转angle角度 
		return point(o.x + (x - o.x) * cos(angle) - (y - o.y) * sin(angle),
					o.y + (x - o.x) * sin(angle) + (y - o.y) * cos(angle));
	}
};
double L, x, y, vx, vy;
int k;
double h;
const double eps = 1e-6;
const double pi = acos(-1);
const double ag = pi * 2 / 3;
point p; 
ll res;
bool check(double t) {
    res = 0;
	point ed(1.0 * vx * t + x, 1.0 * vy * t + y);
	res += abs(floor(ed.y / h));
	res += abs(floor(ed.eotate(p, ag).y / h));
	res += abs(floor(ed.eotate(p, 2 * ag).y / h));
    if(res >= k) return false;
    return true;
}
int main() {
    int t;
    scanf("%d", &t);
    while(t--) {
        scanf("%lf%lf%lf%lf%lf%d", &L, &x, &y, &vx, &vy, &k);
        h = sqrt(3) * L / 2;
        p = point(0, h / 3);
		double l = 0, r = 1e11, mid;
        while(r - l > eps) {
            mid = (l + r) / 2.0;
            if(check(mid)) {
				l = mid;
            }
            else {            	
            	r = mid;
            }
        }
        printf("%.8f\n", (l + r) / 2);
    }
}
