#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
#define N 305
int f[N][N];
char arr[N * N];
int a[N];
int main() {
	int t;
	scanf("%d", &t);
	while(t--) {
		int n, s;
		scanf("%d%d", &n, &s);
		scanf("%s", arr);
		int ct = 0;
		for(int i = 0; i < n; i++) {
			for(int j = i + 1; j < n; j++) {
				f[i][j] = f[j][i] = arr[ct++] - '0';
			}
			f[i][i] = 1;
		}
		fill(a, a + n + 1, -1);
		int id = 0;
		for(int i = 0; i < n; i++) {
			vector<int> v;
			if(a[i] == -1) {
				for(int j = 0; j < n; j++) {
					if(f[i][j] && a[j] == -1) {
						v.push_back(j);
					}
				}
				int m = v.size();
				for(int j = 0; j < n; j++) {
					int num = 0;
					for(auto k : v) {
						if(f[k][j]) {
							num++;
						}	
					}
					if(num >= m / 2) {
						a[j] = id;	
					}
				}
				id++;
			}
		}
		for(int i = 0; i < n - 1; i++) {
			printf("%d ", a[i]);
		}
		printf("%d\n", a[n - 1]);
	}
}

