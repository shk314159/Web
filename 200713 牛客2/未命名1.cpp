#include <bits/stdc++.h>
using namespace std;
const int SIZE = 2000+50;
const double eps = 1e-9;
struct Point {
    double x,y;
    bool operator < (const Point& tb) const {
        if (x != tb.x) return x < tb.x;
        return y < tb.y;
    }
    bool operator == (const Point& tb) const {
        return ((fabs(x - tb.x) < eps) && (fabs(y - tb.y) < eps));
    }
}p[SIZE];
inline Point waixin(const Point& a, const Point& b, const Point& c) {
    double a1 = b.x - a.x, b1 = b.y - a.y, c1 = (a1 * a1 + b1 * b1) * 0.5;
    double a2 = c.x - a.x, b2 = c.y - a.y, c2 = (a2 * a2 + b2 * b2) * 0.5;
    double d = a1 * b2 - a2 * b1;
    Point ans;
    ans.x = a.x + (c1 * b2 - c2 * b1) / d; 
	ans.y = a.y + (a1 * c2 - a2 * c1) / d;
    return ans;
}
pair<double, double> pt[3000005];
int main() {
	int n;
    scanf("%d", &n);
    for (int i = 1, x, y; i <= n; i++) {
    	scanf("%d%d", &x, &y);
    	p[i].x = x, p[i].y = y;
    }
    int num = 0;
    Point Zero; Zero.x = 0.0, Zero.y = 0.0;
    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (fabs(p[i].x * p[j].y - p[i].y * p[j].x) <= eps) continue;
            Point p = waixin(p[i], p[j], Zero);
			pt[num++] = make_pair(p.x, p.y);
        }
    }
    if(num == 0) {
    	printf("1\n");
    	return 0;
	}
    sort(pt, pt + num);
    int maxx = 1;
    int cnt = 1;
    for (int i = 1; i <= num - 1; i++) {
    	if(fabs(pt[i].first - pt[i + 1].first) < eps && fabs(pt[i].second - pt[i + 1].second) < eps) {
    		cnt++;
    		maxx = max(maxx, cnt);
		}
		else {
			cnt = 1;
		}
    }
    for(int i = 1; i <= n; i++) {
    	if(i * (i - 1) == maxx * 2) {
    		printf("%d\n", i);
    		break;
		}
	}
//    printf("%d\n", maxx); 
}
 
