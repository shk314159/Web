#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
#define N 200005
#define pii pair<int, int>
bool notp[N];
int prime[N],pnum;
void sieve() {
    memset(notp,0,sizeof(notp));
    notp[0]=notp[1]=1;
    pnum=0;
    for(int i=2;i<N;i++)
    {
        if(!(notp[i])) prime[++pnum]=i;
        for(int j=1;j<=pnum&&prime[j]*i<N;j++)
        {
            notp[prime[j]*i]=1;
            if(i%prime[j]==0) break;
        }
    }
}
vector<pii> v;
vector<int> odd;
set<int> s;
int main() {
	int t;
	scanf("%d", &t);
	sieve();
	while(t--) {
		v.clear();
		odd.clear();
		s.clear();
		int n;
		int t;
		scanf("%d", &n);
		for(int i = pnum; i >= 1; i--) {
			vector<int> tp;
			for(int j = 1; j * prime[i] <= n; j++) {
				if(!s.count(j * prime[i])) {
					tp.push_back(j * prime[i]);
					s.insert(j * prime[i]);
				}
			}
			if(tp.size() == 1) {
				continue;
			}	
			else if(tp.size() & 1){
				v.push_back(make_pair(tp[0], tp[2]));
				odd.push_back(tp[1]);
				for(int i = 4; i < tp.size(); i += 2) {
					v.push_back(make_pair(tp[i - 1], tp[i]));
				}
			}
			else {
				for(int i = 1; i < tp.size(); i += 2) {
					v.push_back(make_pair(tp[i - 1], tp[i]));
				}
			}
		}
		for(int i = 1; i < odd.size(); i += 2) {
			v.push_back(make_pair(odd[i], odd[i - 1]));
		}
		printf("%d\n", v.size());
		for(int i = 0; i < v.size(); i++) {
			printf("%d %d\n", v[i].first, v[i].second);
		}
	}
}

