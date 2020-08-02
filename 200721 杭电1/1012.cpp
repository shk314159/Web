#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
#define pi acos(-1)
#define N 205
#define eps 1e-20
struct point{
    double x, y;
    double angle;
    bool operator<(const point &t)
    {
        return angle < t.angle;
    }
    point(){}
    point(double a,double b){x=a,y=b;angle = atan2(y, x);}
    point operator - (const point &t) const {
        return point(x - t.x, y - t.y);
    }
    double operator * (const point &t) const {
        return x * t.x + y * t.y;
    }
    double operator ^ (const point &t) const {
        return x * t.y - y * t.x;
    }
    double dis(const point &t) {
        return sqrt((x - t.x) * (x - t.x) + (y - t.y) * (y - t.y));
    }
}p[N], xp[N];
bool QJcmp(point a, point b) {
    if (a.angle == b.angle)
        return a.x < b.x;
    else {
        return a.angle < b.angle;
    }
}
struct line {
    point s, e;
    double k;
    line() {}
    line(point a, point b) { s = a, e = b, k = atan2(b.y - a.y, b.x - a.x); }
    point operator & (const line &b) const {//求两直线交点 
        point res = s;
        double t = ((s - b.s) ^ (b.s - b.e)) / ((s - e) ^ (b.s - b.e));
        res.x += (e.x - s.x) * t;
        res.y += (e.y - s.y) * t;
        return res;
    }
};
int n;
int ans_s; //相交点数
line L[N], q[N];
point ans[N]; //存点
bool cmp(line a, line b) {
    if (fabs(a.k - b.k) <= eps)
        return ((a.s - b.s) ^ (b.e - b.s)) < 0; //平行取下
    return a.k < b.k;
}
double getarea(int n) {
    if (n < 3)
        return 0;
    int i;
    double res = 0;
    for (i = 2; i < n; i++) {	
        res += fabs(((p[i] - p[0]) ^ (p[i - 1] - p[0])) / 2.0);
    }
    return res;
}
double getRarea(int n) {
    if (n < 3)
        return 0;
    int i;
    double res = 0;
    for (i = 2; i < n; i++) {	
        res += fabs(((ans[i] - ans[0]) ^ (ans[i - 1] - ans[0])) / 2.0);
    }
    return res;
}
void Hpi() {//保证多边形逆时针建边
    int tot = 1;
    sort(L, L + n, cmp);
    for (int i = 1; i < n; i++) {
        if (fabs(L[i].k - L[i - 1].k) > eps) {
            L[tot++] = L[i];
        } //因为平行的时候，左边的线段先判断，所以可以去除无效判定
    }
    int l = 0, r = 1;
    q[0] = L[0];
    q[1] = L[1]; //模拟双端 ，每条线取左删右（顺时针建边取右删左）
    for (int i = 2; i < tot; i++) {
        if (fabs((q[r].e - q[r].s) ^ (q[r - 1].e - q[r - 1].s)) <= eps ||
            fabs((q[l].e - q[l].s) ^ (q[l + 1].e - q[l + 1].s)) <= eps)
            return;                                                               //半平面交不存在
        while (l < r && (((q[r] & q[r - 1]) - L[i].s) ^ (L[i].e - L[i].s)) > eps) //上一个交点在下一条线的右侧，不在半平面交上
            r--;
        while (l < r && (((q[l] & q[l + 1]) - L[i].s) ^ (L[i].e - L[i].s)) > eps) // 同上
            l++;
        q[++r] = L[i]; //加入新边
    }
    while(l < r && (((q[r] & q[r - 1]) - L[l].s) ^ (L[l].e - L[l].s)) > eps)
        r--;
    while(l < r && (((q[l] & q[l - 1]) - L[r].s) ^ (L[r].e - L[r].s)) > eps)
        l++;
    if (r <= l + 1)
        return; //如果只有2个或以下的点，构不成平面
    for(int i = l; i < r; i++) {
        ans[ans_s++] = q[i] & q[i + 1];
    } //ans里存交点
   if(l < r - 1) ans[ans_s++] = q[l] & q[r];
}

void reset(point a, point b, point &t1, point &t2, double d) {
	double db = a.dis(b);
	double dx = (a.y - b.y) * d / db;
	t1.x = a.x + dx,t2.x = b.x + dx;
	double dy = (b.x - a.x) * d / db;
	t1.y = a.y + dy, t2.y = b.y + dy;
}                                                              

int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		int d;
		scanf("%d%d", &n, &d);
		int a, b;
		scanf("%d%d", &a, &b);
		for(int i = 0; i < n; i++) {
			scanf("%lf%lf", &p[i].x, &p[i].y);
			p[i].angle = atan2(p[i].y, p[i].x);
		}
		sort(p, p + n, QJcmp);
		double area = getarea(n);
		for(int i = 0; i < n; i++) {
			point t1, t2;
            reset(p[i], p[(i + 1) % n], t1, t2, d);
			L[i] = line(t1, t2);
		}
		double cost = area * 1.0 * a;
		double l = 0;
		ans_s = 0;
		Hpi();
		if(ans_s) {
			for(int i = 0; i < ans_s; i++) {
				l += ans[i].dis(ans[(i + 1) % ans_s]);
			}
			double da = getRarea(ans_s) + l * (double)d + 1.0 * d * d * pi;
			cost = min(cost, da * (double)b + (area - da) * (double)a);
		} 
		printf("%.20f\n", cost);
	}
}

