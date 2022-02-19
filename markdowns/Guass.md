# 高斯消元

### 一、线性方程组

求解形如
$$
\begin{cases}
p_{11}x_1+p_{12}x_2+\cdots+p_{1n}x_n=y_1\\
p_{21}x_1+p_{22}x_2+\cdots+p_{2n}x_n=y_2\\
\vdots \\
p_{n1}x_1+p_{n2}x_2+\cdots+p_{nn}x_n=y_n\\
\end{cases}
$$
的 $n$ 元一次方程组（也就是线性方程组），我们会用到**高斯消元**法。
$$
\left(
\begin{matrix}
p_{11} &p_{12} &\cdots &p_{1n}\\
p_{21} &p_{22} &\cdots &p_{2n}\\
\vdots &\vdots &\ddots &\vdots\\
p_{n1} &p_{n2} &\cdots &p_{nn}\\
\end{matrix}
\middle|\ 
\begin{matrix}
y_{1} \\
y_{2} \\
\vdots \\
y_{n} \\
\end{matrix}

\right)
$$
我们把一个线性方程组简便记成上面这样的形式。

**高斯消元主要依据线性方程组的以下三个性质：**

**1、方程组中的两条等式交换位置，解不变。**

**2、方程组中某个等式乘上某个非零实数，解不变。**

**3、方程组中某个等式减去另一个等式，解不变。**



接下来我们通过一个实例来讲解高斯消元法。下文用 $r$ 表示行。
$$
\left(
\begin{matrix}
1 &3 &2\\
2 &-1 &1\\
1 &1  &1\\
\end{matrix}
\middle|\ 
\begin{matrix}
2 \\
5 \\
7 \\
\end{matrix}

\right)
$$
由于一个纵列对应的是一个元，我们每次从左到右处理每个元。
$$
\xlongequal{r_1\Leftrightarrow r_2}
\left(
\begin{matrix}
2 &-1 &1\\
1 &3 &2\\
1 &1  &1\\
\end{matrix}
\middle|\ 
\begin{matrix}
5 \\
2 \\
7 \\
\end{matrix}

\right)
$$
对于第一个元，我们找到系数绝对值最大的那一项，并将其交换至第一列。（下文会解释这个步骤）
$$
\xlongequal{r_1 \div2}
\left(
\begin{matrix}
1 &-\frac{1}{2} &\frac{1}{2}\\
1 &3 &2\\
1 &1  &1\\
\end{matrix}
\middle|\ 
\begin{matrix}
\frac{5}{2} \\
2 \\
7 \\
\end{matrix}

\right)
$$
将第一列的第一个元系数化为 $1$ 。同时，将其他行用**性质3**减去第一行的 $k$ 倍，将其它式子中的第一个系数全部化为 $0$ 。
$$
\xlongequal{r_i-k\cross r_1}
\left(
\begin{matrix}
1 &-\frac{1}{2} &\frac{1}{2}\\
0 &\frac{7}{2} &\frac{3}{2}\\
0 &\frac{3}{2}  &\frac{1}{2}\\
\end{matrix}
\middle|\ 
\begin{matrix}
\frac{5}{2} \\
-\frac{1}{2} \\
\frac{9}{2} \\
\end{matrix}

\right)
$$
发现右下角有一个子方阵，于是我们仿照上面的方法继续处理第二元，
$$
\xlongequal{r_2\div\frac{7}{2}}
\left(
\begin{matrix}
1 &-\frac{1}{2} &\frac{1}{2}\\
0 &1 &\frac{3}{7}\\
0 &\frac{3}{2}  &\frac{1}{2}\\
\end{matrix}
\middle|\ 
\begin{matrix}
\frac{5}{2} \\
-\frac{1}{7} \\
\frac{9}{2} \\
\end{matrix}

\right)
$$

$$
\xlongequal{r_i-k\cross r_2}
\left(
\begin{matrix}
1 &-\frac{1}{2} &\frac{1}{2}\\
0 &1 &\frac{3}{7}\\
0 &0  &-\frac{1}{7}\\
\end{matrix}
\middle|\ 
\begin{matrix}
\frac{5}{2} \\
-\frac{1}{7} \\
\frac{33}{7} \\
\end{matrix}

\right)
$$

最后将第三个元系数化为 $1$ ，
$$
\xlongequal{r_3\div (-\frac{1}{7})}
\left(
\begin{matrix}
1 &-\frac{1}{2} &\frac{1}{2}\\
0 &1 &\frac{3}{7}\\
0 &0  &1\\
\end{matrix}
\middle|\ 
\begin{matrix}
\frac{5}{2} \\
-\frac{1}{7} \\
-33 \\
\end{matrix}

\right)
$$
这样子，我们将原方程组化为了上三角形式。

化为上三角形式方便我们对解进行回代，接下来我们进行回代操作。

首先可以得到 $x_3=-33$ 。我们把这个结果代入 $r_2$ 可以得到 $x_2=14$。

再将 $x_3$ 与 $x_2$ 代入 $r_1$，我们又能解得 $x_1=26$。

于是方程组的解为
$$
\begin{cases}
x_1=26\\
x_2=14\\
x_3=-33
\end{cases}
$$
通过上面这个例子，聪明的你应该能够理解高斯消元算法的步骤了：

**一、从 $1$ 到 $n$ 依次消去第 $i$ 个元**

**二、消第 $i$ 个元时，选择第 $i$ 列中系数绝对值最大的未处理行 $r$，交换到第 $i$ 行。**

**三、将第 $i$ 行的主元系数化为 $1$。**

**四、将未处理行主元系数化为 $0$ 。**

**五、将第 $i$ 行看作是已处理行。继续对第 $i+1$ 列进行消元。**

通过上面的步骤，我们就能将原方程化为上三角的形式。再对元进行回代，就能得出方程组的解。

在步骤二中，如果行 $r$ 主元系数依然为 $0$ ，则说明该方程组**不存在唯一解**，因为该元可取任意值。

如果最后的上三角形式中，存在一行系数**全部是 $0$ **而常数项不为 $0$ ，则方程组 **无解**。

一般来说，我们只需要判断是否存在唯一解即可。

这个算法时间复杂度为 $O(n^3)$，详见代码。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int maxn=2e2+5;
const double eps=1e-10;
int n;
double a[maxn][maxn];
double x[maxn];

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n+1;j++){
			scanf("%lf",&a[i][j]);
		} 
	}//读入
	for(int i=1;i<=n;i++){
		int r=i;
		for(int j=i+1;j<=n;j++){
			if(abs(a[j][i])>abs(a[r][i])){
				r=j;
			}
		}//寻找最大系数
		if(abs(a[r][i])<eps){//判断是否有解
			puts("No Solution");
			return 0;
		}
		if(r!=i)
		for(int j=1;j<=n+1;j++){
			swap(a[r][j],a[i][j]);
		}//交换
		double div=a[i][i];
		for(int j=i;j<=n+1;j++){
			a[i][j]/=div;
		}//系数化为一
		for(int j=i+1;j<=n;j++){
			double mul=a[j][i];
			for(int k=i;k<=n+1;k++){
				a[j][k]-=a[i][k]*mul;
			}
		}//消元
	}//通过这段程序，已经化为上三角形式
	x[n]=a[n][n+1];
	for(int i=n-1;i>=1;i--){
		x[i]=a[i][n+1];
		for(int j=i+1;j<=n;j++){
			x[i]-=a[i][j]*x[j];
		}
	}//回代
	for(int i=1;i<=n;i++){
		printf("%.2f\n",x[i]);
	}
}
```

简单说一说为什么要找绝对值最大的那一行，一是因为可以寻找一个非零行，二是作浮点数除法时，显然除以一个大数会让精度更好，误差更小。



### 二、高斯消元求行列式

由于行列式有特殊性质，所以解方程组的方法对行列式求解也适用。

我们知道，当行列式化为上三角形式时，行列式的值就是对角线的累积。

注意到我们在消元时作了整行除以 $k$ 的操作，根据行列式的性质，相当于行列式的值也除以了 $k$ ，于是我们要把 $k$ 乘到最终答案里弥补损失。

另外，如果交换行时，根据行列式的性质，答案应该进行取反。



### 三、矩阵求逆

与线性方程组类似，矩阵可以进行交换、某行乘 $k$、某行加上另一行的操作。这称为**矩阵的初等行变换**。

实际上，这三个操作本质上分别对应着一种线性变换。

同样以上面那个矩阵为例，
$$
\left[
\begin{matrix}
1 &3 &2\\
2 &-1 &1\\
1 &1  &1\\
\end{matrix}
\right]
$$
交换第一第二行对应的线性变换是
$$
\left[
\begin{matrix}
0 &1 &0\\
1 &0 &0\\
0 &0  &1\\
\end{matrix}
\right]
\left[
\begin{matrix}
1 &3 &2\\
2 &-1 &1\\
1 &1  &1\\
\end{matrix}
\right]=
\left[
\begin{matrix}
2 &-1 &1\\
1 &3 &2\\
1 &1  &1\\
\end{matrix}
\right]
$$
第二行乘上 $\frac{1}{2}$ 对应的线性变换是
$$
\left[
\begin{matrix}
1 &0 &0\\
0 &\frac{1}{2} &0\\
0 &0  &1\\
\end{matrix}
\right]
\left[
\begin{matrix}
1 &3 &2\\
2 &-1 &1\\
1 &1  &1\\
\end{matrix}
\right]=
\left[
\begin{matrix}
1 &3 &2\\
1 &-\frac{1}{2} &\frac{1}{2}\\
1 &1  &1\\
\end{matrix}
\right]
$$
第一行加上第二行的三倍对应的线性变换是
$$
\left[
\begin{matrix}
1 &3 &0\\
0 &1 &0\\
0 &0  &1\\
\end{matrix}
\right]
\left[
\begin{matrix}
1 &3 &2\\
2 &-1 &1\\
1 &1  &1\\
\end{matrix}
\right]=
\left[
\begin{matrix}
7 &0 &5\\
2 &-1 &1\\
1 &1  &1\\
\end{matrix}
\right]
$$
综上所述，我们对矩阵进行的三类操作其实均可看作是一次线性变换。

由逆矩阵的定义可知，
$$
A^{-1}A=E
$$
记 $P=A^{-1}$，说明如果可逆，那么 $P$ 相当于就是对 $A$ 进行了若干次初等行变换，并让 $A$ 转变为 $E$ 。即
$$
P_n\cdots P_3P_2P_1A=E
$$
 对 $A$ 的这些行变换本质上就是高斯消元的过程。

其中 $P_n\cdots P_3P_2P_1$ 就等于 $P$，也就是 $A$ 的逆矩阵。稍微作一下变换，
$$
P_n\cdots P_3P_2P_1EA=E\\
P_n\cdots P_3P_2P_1E=P=A^{-1}
$$
也就是说，在我们将 $A$ 高斯消元的同时，对 $E$ 也作同样的行变换，最后得到的“记录”就是 $A$ 的逆矩阵。

套用高斯消元的模板即可。这里的逆矩阵是取模意义下的，所以所有的除法全部用乘法逆元代替。

具体细节就看代码吧。

```cpp
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const ll mod=1e9+7;
const int maxn=4e2+5;
ll a[maxn][maxn];
ll b[maxn][maxn];
int n;

ll qpow(ll a,ll b){
	ll ret=1;
	while(b){
		if(b&1) ret=ret*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return ret;
}

inline ll inv(ll x){
	return qpow(x,mod-2);
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%lld",&a[i][j]);
	for(int i=1;i<=n;i++) b[i][i]=1;//初始化一个b矩阵为E，记录A中的操作
    //接下来要注意，B的记录操作一定要是整行变换的。
    //在一般的高斯消元中，A不进行整行操作，是因为行前已经削为0，但本质上还是进行了整行变换
    //但是B中行的数字都不一定是非0的，如果不进行整行变换就会出错。
	for(int i=1;i<=n;i++){
		int r=i;
		for(int j=i;j<=n;j++){//这里找一个非零值就可以了，因为整数运算不存在误差
			if(a[j][i]){
				r=j;break;
			}
		}
		if(!a[r][i]){//对角线中有0，即矩阵行列式为0，故不存在逆矩阵
			puts("No Solution");return 0;
		}
		if(r!=i) swap(a[r],a[i]),swap(b[r],b[i]);
		ll div=inv(a[i][i]);
		for(int j=1;j<=n;j++){
			a[i][j]=a[i][j]*div%mod;b[i][j]=b[i][j]*div%mod;
		}//注意B中整行的操作
		for(int j=i+1;j<=n;j++){
			ll mul=a[j][i];
			for(int k=1;k<=n;k++){//还是要整行
				a[j][k]-=mul*a[i][k]%mod;
				a[j][k]=(a[j][k]+mod)%mod;
				b[j][k]-=mul*b[i][k]%mod;
				b[j][k]=(b[j][k]+mod)%mod;
			}
		}
	}
	for(int i=n-1;i>=1;i--){//最后的回代过程还是要注意整行相减！！整行！！所以是O(n^3)的
		for(int j=i+1;j<=n;j++){
			for(int k=1;k<=n;k++){
				b[i][k]-=b[j][k]*a[i][j]%mod;
				b[i][k]=(b[i][k]+mod)%mod;
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			printf("%lld ",b[i][j]);
		}
		puts("");
	}
}
```



高斯消元还有很多应用，日后掌握了再补充。
