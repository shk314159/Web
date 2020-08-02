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
#define eps 1e-4
using namespace std;
struct point {
    double x, y;
    point(double x = 0, double y = 0) : x(x), y(y){}
    point operator + (const point &t) const {
        return point(x + t.x , y + t.y);
    }
    point operator - (const point &t) const {
        return point(x - t.x , y - t.y);
    }
    double operator ^ (const point &t) const {
        return x * t.y - y * t.x;
    }
    double operator * (const point &t) const {
        return x * t.x + y * t.y;
    }
    double dis(const point &t) const {
        return sqrt((x - t.x) * (x - t.x) + (y - t.y) * (y - t.y));
    }
 
};
double Compare(point a, point b, point c) { //ab X ac
    return (b - a) ^ (c - a);
}
point p[50];
int main(){
    int t;
    scanf("%d", &t);
    while(t--) {
        for(int i = 1; i <= 20; i++) {
            scanf("%lf%lf", &p[i].x, &p[i].y);
        }
        int st = 0, ed = 0, flag = 0;
        for(int i = 1; i <= 20; i++) {
            for(int j = i + 1; j <= 20; j++) {
                if(fabs(p[i].dis(p[j]) - 9) < eps) {
                    int f = -1;
                    for(int k = 1; k <= 20; k++) {
                        if(k == i || k == j) continue;
                        if(Compare(p[i], p[j], p[k]) < 0) {
                            if(f == -1) f = 0;
                            else if(f == 0) continue;
                            else if(f == 1) {
                                f = -1;
                                break;
                            }
                        }
                        else if(Compare(p[i], p[j], p[k]) > 0) {
                            if(f == -1) f = 1;
                            else if(f == 1) continue;
                            else if(f == 0) {
                                f = -1;
                                break;
                            }
                        }
                        else {
                            continue;
                        }
                    }
                    if(f == -1) continue;
                    else {
                        flag = f;
                        st = i, ed = j;
                        break;
                    }
                }
            }
            if(st != 0) break;
        }
        //cout <<st << " " <<ed << '\n';
        double a1 = (p[st].x - p[ed].x), b1 = (p[st].y - p[ed].y);
        double c1 = p[st].y * p[ed].y + p[st].x * p[ed].x - p[st].x * p[st].x - p[st].y * p[st].y;
        double a2 = (p[st].x - p[ed].x), b2 = (p[st].y - p[ed].y);
        double c2 =  p[ed].x * p[ed].x + p[ed].y * p[ed].y - p[st].y * p[ed].y - p[st].x * p[ed].x;
        double len1, len2;
        //cout << a1 << " " << b1 << " " <<c1 << '\n';
        //cout << a2 << " " << b2 << " " <<c2 << '\n';
        for(int i = 1; i <= 20; i++) {
            if(i == st || i == ed) continue;
            if(fabs(a1 * p[i].x + b1 * p[i].y + c1) < eps) {
                len1 = p[st].dis(p[i]);
                //cout << p[i].x << " " << p[i].y << '\n';
            }
            else if(fabs(a2 * p[i].x + b2 * p[i].y + c2) < eps) {
                len2 = p[ed].dis(p[i]);
                //cout << p[i].x << " " << p[i].y << '\n';
            }
        }
        //cout << len1 << " " << len2 << '\n';
        if(flag == 1) {
            if(c1 > c2) {
                if(len1 > len2) {
                    printf("right\n");
                }
                else {
                    printf("left\n");
                }
            }
            else {
                if(len1 > len2) {
                    printf("left\n");
                }
                else {
                    printf("right\n");
                }
            }
        }
        else {
            if(c1 > c2) {
                if(len1 > len2) {
                    printf("left\n");
                }
                else {
                    printf("right\n");
                }
            }
            else {
                if(len1 > len2) {
                    printf("right\n");
                }
                else {
                    printf("left\n");
                }
            }
        }
    }
}
