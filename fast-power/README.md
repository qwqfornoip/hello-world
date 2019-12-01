# 倍增

## 数倍增

### 例题一

求(a * b) mod c,(a,b极大)。

#### 分析

$$
a\ *\ b = \begin{cases}
a * (b/2) * 2,\ b=2*k(k=1,2,....)\\
a * floor(b/2) * 2 + a,\ b=2*k-1(k=1,2,...)
\end{cases}
$$

#### 实现

```c++
typedef long long ll;
//循环版
ll qtimes1(ll a, ll b, ll c){ // (a * b) % c
	ll ans = 0;
	while(b){ //b为零时退出 
		if (b&1) ans = (ans+a) % c; // 若b为奇数 
		a = (a<<1) % c; //a乘2 
		b >>= 1; //b除2向下取整，进入下一层 
	}
	return ans;
}

//递归版
ll qtimes2(ll a, ll b, ll c){// (a * b) % c
	if (!b) return 0;
	if (b==1) return a%c;
	ll ans = qtimes2(a, b>>1, c); //算出(a * floor(b/2)) % c
	ans = (ans<<1) % c; //*2
	if (b&1) ans = (ans + a) % c; //+a
	return ans;
}
```

### 例题二

(快速幂) 求(a ^ b) mod c,(a,b极大)。

```c++
typedef long long ll;
ll qpower(ll a, ll b, ll c){ //(a^b)%c
	if (!a) return 0; //a=0可直接返回 
	ll ans = 1;
	while(b){
		if (b&1) ans = (ans * a) % c;
		a = (a * a) % c;
		b >>= 1;
	}
	return ans;
}
```

## 矩阵倍增（二阶矩阵）

$$
已知：\begin{bmatrix}
a*e+b*g&b*f+b*h\\
c*e+d*g&d*f+f*h\\
\end{bmatrix}
=
\begin{bmatrix}a&b\\c&d\\\end{bmatrix}
*
\begin{bmatrix}e&f\\g&h\\\end{bmatrix}
$$

$$
求：{\begin{bmatrix}
a&b\\c&d\\
\end{bmatrix}}^n * \begin{bmatrix}m\\n\end{bmatrix}
$$

(n很大)。

### 实现

#### 定义矩阵

```c++
struct matrix{
	ll map[2][2];//初始为全零矩阵
	matrix(ll a, ll b, ll c, ll d){//创建矩阵[[a b][c d]]
		map[0][0] = a;
		map[0][1] = b;
		map[1][0] = c;
		map[1][1] = d;
	}
	matrix(){//空构造方法
		map[0][0] = 0;	map[0][1] = 0;
		map[1][0] = 0;	map[1][1] = 0;
	}
	void print(){//打印方法 
		printf("%d,%d\n%d,%d\n",map[0][0], map[0][1], map[1][0], map[1][1]);
	}
};
```

#### 定义矩阵乘法

我写的

```c++
matrix times(matrix m1, matrix m2){
	matrix *a = new matrix(m1.map[0][0] * m2.map[0][0] + m1.map[0][1] * m2.map[1][0],
					m1.map[0][0] * m2.map[0][1] + m1.map[0][1] * m2.map[1][1],
					m1.map[1][0] * m2.map[0][0] + m1.map[1][1] * m2.map[1][0],
					m1.map[1][0] * m2.map[0][1] + m1.map[1][1] * m2.map[1][1]);
	return *a;
}
```

一个大佬的方法orz

```c++
matrix times(matrix m1, matrix m2, ll m){
	matrix ans;
	for (int i = 0; i < 2; ++i)
		for (int j = 0; j < 2; ++j)
			for (int k = 0; k < 2; ++k){
				ans.map[i][j] += qtimes1(m1.map[i][k], m2.map[k][j], m);
				ans.map[i][j] %= m;
			}
	return ans;
}
```

#### 矩阵快速幂

```c++
//矩阵快速幂
matrix mpow(matrix m1, ll n, ll m){
	if (n == 1) return m1;
	matrix ans = *(new matrix(1, 0, 0, 1)); //单位矩阵
	while(n){
		if (n&1) ans = times(ans, m1, m);
		m1 = times(m1, m1, m);
		n >>= 1;
	}
	return ans;
} 
```

dalao的递归版orz

```c++
matrix Pow( matrix x , ll cnt, ll m) {
    if ( cnt == 1 ) return x ;
    matrix rec = Pow( x , cnt / 2, m) ;
    rec = times( rec , rec, m ) ;
    if ( cnt % 2 ) rec = times( rec , x , m) ;
    return rec ;
}
```

## 全部代码

```c++
#include <cstdio>
typedef long long ll;

//input:
//a b c
//d e f
//a b c d n m
//output:
//(a*b)%c
//(d^e)%f
//{[[a,b],[c,b]] ^ n} % m

ll a1, b1, c1;
ll a2, b2, c2;
ll a3, b3, c3, d3, n3, m3;
 
ll qtimes1(ll a, ll b, ll c){ // (a * b) % c
	if (!a) return 0;
	ll ans = 0;
	while(b){ //b为零时退出 
		if (b&1) ans = (ans+a) % c; // 若b为奇数 
		a = (a<<1) % c; //a乘2 
		b >>= 1; //b除2向下取整，进入下一层 
	}
	return ans;
}

ll qtimes2(ll a, ll b, ll c){
	if (!b) return 0;
	if (b==1) return a%c;
	ll ans = qtimes2(a, b>>1, c);
	ans = (ans<<1) % c;
	if (b&1) ans = (ans + a) % c;
	return ans;
}

ll qpower(ll a, ll b, ll c){ //(a^b)%c
	if (!a) return 0; //a=0可直接返回 
	ll ans = 1;
	while(b){
		if (b&1) ans = (ans * a) % c;
		a = (a * a) % c;
		b >>= 1;
	}
	return ans;
}

struct matrix{
	ll map[2][2];
	matrix(ll a, ll b, ll c, ll d){
		map[0][0] = a;
		map[0][1] = b;
		map[1][0] = c;
		map[1][1] = d;
	}
	matrix(){
		map[0][0] = 0;	map[0][1] = 0;
		map[1][0] = 0;	map[1][1] = 0;
	}
	
	void print(){//打印方法 
		printf("%d,%d\n%d,%d\n",map[0][0], map[0][1], map[1][0], map[1][1]);
	}
};

matrix times(matrix m1, matrix m2, ll m){
//	matrix *a = new matrix(m1.map[0][0] * m2.map[0][0] + m1.map[0][1] * m2.map[1][0],
//					m1.map[0][0] * m2.map[0][1] + m1.map[0][1] * m2.map[1][1],
//					m1.map[1][0] * m2.map[0][0] + m1.map[1][1] * m2.map[1][0],
//					m1.map[1][0] * m2.map[0][1] + m1.map[1][1] * m2.map[1][1]);
//	return *a;
	matrix ans;
	for (int i = 0; i < 2; ++i){
		for (int j = 0; j < 2; ++j){
			for (int k = 0; k < 2; ++k){
				ans.map[i][j] += qtimes1(m1.map[i][k], m2.map[k][j], m);
				ans.map[i][j] %= m;
			}
		}
	}
	return ans;
}

//矩阵快速幂
matrix mpow(matrix m1, ll n, ll m){
	if (n == 1) return m1;
	matrix ans = *(new matrix(1, 0, 0, 1));
	while(n){
		if (n&1) ans = times(ans, m1, m);
		m1 = times(m1, m1, m);
		n >>= 1;
	}
	return ans;
} 

matrix Pow( matrix x , ll cnt, ll m) {
    if ( cnt == 1 ) return x ;
    matrix rec = Pow( x , cnt / 2, m) ;
    rec = times( rec , rec, m ) ;
    if ( cnt % 2 ) rec = times( rec , x , m) ;
    return rec ;
}

int main(){
	freopen("bigtimes.in", "r", stdin);
	freopen("bigtimes.out", "w", stdout);
	
	scanf("%lld%lld%lld", &a1, &b1, &c1);
	scanf("%lld%lld%lld", &a2, &b2, &c2);
	printf("%d\n%d\n", qpower(a1, b1, c1), qtimes1(a2, b2, c2));
	
	scanf("%lld%lld%lld%lld%lld%lld", &a3, &b3, &c3, &d3, &n3, &m3);
	matrix *a = new matrix(a3, b3, c3, d3);
	matrix c = mpow(*a, n3, m3);
	c.print();
	
	fclose(stdin);
	fclose(stdout);
	return 0;
} 
```

## 典型例题

[[NOI2012\]随机数生成器]: https://www.luogu.org/problem/P2044	"[NOI2012]随机数生成器"

