# 二分法

### 引例

![二分](hello-world/dichotomy/dichotomy.png)

> 移动石头的个数越多，答案越大（NOIP2015跳石头）。 
>
> 前i天的条件一定比前 i + 1 天条件更容易（NOIP2012借教室）。 
>
> 满足更少分配要求比满足更多的要求更容易（NOIP2010关押罪犯）。
>
>  满足更大最大值比满足更小最大值的要求更容易（NOIP2015运输计划）。 
>
> 时间越长，越容易满足条件（NOIP2012疫情控制）。

## 例题一

农夫有c头牛，n个隔间，c头牛很躁动，很容易相互打架，因此农夫想把它们分得越远越好，要你分配隔间使得相邻两头牛的距离越远越好，问你这c头牛分割的最小距离的最大值。

### 分析

1.暴力：枚举每种长度，直到符合条件且最小的值

2.二分优化：最短距离为0，最长为两端距离。二分查找（最大的最小值）

3.check(x)：贪心的放牛，每次只找距离最小的地方，判断能否装下c头牛

### 代码

check判断函数

```c++
bool check(int dist){
	int last = 1;
	for (int i = 1; i < c; ++i){//放c-1头牛
		int cur = last + 1;
		while (cur < n and p[cur]-p[last] < dist)//挨个查找，直到距离恰好大于等于dist
			cur++;
		if (cur == n)//若当前已达到队尾且没有放满c头牛
			return 0;
		last = cur;
	}
	return 1;
}
```

二分模板

```c++
int midcheck(int l, int r){
	for (int i = 1; i <= 100; ++i){ //若分析不清，就暴力写100次循环，精度为2^100~10^(-30)
		int mid = (l+(r-l))>>1;
		if (check(mid))
			l = mid;
		else
			r = mid;
	}
	return l;
}
```

 输入前排序

```c++
scanf("%d%d", &n, &c);
for (int i = 1; i <= n; ++i){
	scanf("%d", &p[i]);
}
sort(p+1, p+n+1);//默认从小到大
```

#### 全部代码

```c++
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
	freopen("towpiece.out", "w", stdout);
	
	scanf("%d%d", &n, &c);
	for (int i = 1; i <= n; ++i){
		scanf("%d", &p[i]);
	}
	sort(p+1, p+n+1);
	printf("%d", midcheck(0, 0x3fffffff));
	
	fclose(stdin);
	fclose(stdout);
	return 0;
} 
```

