#include <bits/stdc++.h>
#define N 100050
using namespace std;

int n, c;
int p[N];

bool check(int dist){
	int last = 1;
	for (int i = 1; i < c; ++i){
		int cur = last + 1;
		while (cur < n and p[cur]-p[last] < dist)
			cur++;
		if (cur == n)
			return 0;
		last = cur;
	}
	return 1;
}

int midcheck(int l, int r){
	for (int i = 1; i <= 100; ++i){
		int mid = (l+(r-l))>>1;
		if (check(mid)){
			l = mid;
		} else {
			r = mid;
		}
	}
	return l;
}

int main(){
	freopen("towpiece.in", "r", stdin);
	
	scanf("%d%d", &n, &c);
	for (int i = 1; i <= n; ++i){
		scanf("%d", &p[i]);
	}
	sort(p+1, p+n+1);
	printf("%d", midcheck(0, 0x3fffffff));
	
	fclose(stdin);
	return 0;
} 
