# 快速傅里叶变换（FFT）

### 一、引入

我们先来计算这两个多项式的乘积：
$$
F(x)=x^2+x+1\\G(x)=x+2
$$
根据乘法分配律，我们可以轻松计算这两个多项式的乘积：
$$
\begin{aligned}
F(x)G(x) &= (x^2+x+1)(x+2)\\
&=x(x^2+x+1)+2(x^2+x+1)\\
&=x^3+x^2+x+2x^2+2x+2\\
&=x^3+3x^2+3x+2
\end{aligned}
$$
我们发现，一个多项式最关键的信息是每个项的系数，于是以上两个多项式可以用一个数表来表示。
$$
F(x)=\{1 &1 &1\}\ \ \ \ \ \\
G(x)=\{2 &1\}
$$
这叫作多项式的**系数表示法**。

第一个多项式里的某一项会与第二个多项式的每一项相乘，

比如，$ax^p$ 与 $bx^q$ 相乘得到 $abx^{p+q}$ ，于是会对 $p+q$ 次项有 $ab$ 的贡献。

有此思路，我们可以书写朴素的多项式乘法代码：

```cpp
for(int i=0;i<=p;i++){
	for(int j=0;j<=q;j++){
    	ans[i+j]+=f[i]*g[j];
    }
}
```

发现这个算法的复杂度为 $O(n^2)$ 。

为了优化该多项式算法，快速傅里叶变换（FFT）就此出现。

</br>

### 二、点值表示法

介绍FFT之前，我们要引入一种新的多项式表示法。

我们考虑一种**表示法**的时候，应该明确，这种表示法**能且仅能**表示一种多项式。

</br>

我们可以用函数的思想考虑多项式问题。

想一想，我们在学习 $k$ 次函数的时候，有什么方法能唯一表示一个函数？

比如说，一次函数，$y=kx+b$ ，我们可以通过确定斜率 $k$ 与截距 $b$ 来确定一个函数。又或者，点斜式，$y=k(x-x_0)+y_0$ ，通过直线经过的某一点 $(x_0,y_0)$ 与斜率来确定这条直线。

更一般地，我们发现可以用两个点来表示它。比如 $(1,2)$ 与 $(0,1)$ 两点可以唯一确定一条直线 $y=x+1$ 。

我们再回想起二次函数的一般形式 $y=ax^2+bx+c\ (a\not=0)$ ，我们发现可以用三个横坐标不同的点求解出唯一的抛物线方程。

于是我们大胆猜想：$k$ 次函数可以用 $k+1$ 个横坐标不同的点唯一表示。这就是**点值表示法**。

问题来了，怎么证明这样就能唯一表示呢？

多项式可以看作是以下线性变换：
$$
F(x)=\begin{bmatrix}
1 &x &x^2 &\cdots &x^n
\end{bmatrix}
\begin{bmatrix}
p_0\\
p_1\\
p_2\\
\vdots\\
p_n
\end{bmatrix}
$$
如果你没有深入学过**线性代数**，那么可以感性理解一下，求解一个函数的系数，本质是解以下方程组：
$$
\begin{cases}
y_0=p_0+p_1x_0+p_2x_0^2+\cdots+p_nx_0^n\\
y_1=p_0+p_1x_1+p_2x_1^2+\cdots+p_nx_1^n\\
\vdots\\
y_n=p_0+p_1x_n+p_2x_n^2+\cdots+p_nx_n^n
\end{cases}
$$
把 $1,x ,x^2,\cdots,x^n$ 看作是方程组的系数，$p$ 看作是方程组的元，那么有 $n+1$ 个方程，应该就能唯一求解出 $n+1$ 个元了。这是感性理解。以下是严格证明（可跳过）：

把以上方程组写成线性变换的形式：
$$
\begin{bmatrix}
y_0\\
y_1\\
\vdots\\
y_n
\end{bmatrix}=
\begin{bmatrix}
1 &x_0 &x_0^2 &\cdots &x_0^n\\
1 &x_1 &x_1^2 &\cdots &x_1^n\\
\vdots &\vdots &\vdots &\ddots &\vdots
\\
1 &x_n &x_n^2 &\cdots &x_n^n\\
\end{bmatrix}
\begin{bmatrix}
p_0\\
p_1\\
\vdots\\
p_n
\end{bmatrix}
$$
 要证明方程组有唯一解，根据克拉默法则，即证明系数矩阵的行列式不为 $0$。

将矩阵转置，记为 $A$ 。
$$
A=\begin{bmatrix}
1 &1 &1 &\cdots &1\\
x_0 &x_1 &x_2 &\cdots &x_n\\
\vdots &\vdots &\vdots &\ddots &\vdots
\\
x_0^n &x_1^n &x_2^n &\cdots &x_n^n\\
\end{bmatrix}
$$
发现 $|A|$ 是 **Vandermonde** 行列式（本文末附加证明）。
$$
|A|=\prod_\limits{0\leq j<i\leq n}(x_i-x_j)
$$
由于 $x_i$ 两两不同，所以 $|A|\not=0$ 。于是方程组有唯一解。

这也就说明了，点值表示法是靠谱的，可以用于表示一个唯一多项式。

</br>

我们考虑怎么将点值表示法运用于多项式乘法。

假如多项式 $F(x)$ 的某个点值为 $(x_0,F(x_0))$ ，多项式 $G(x)$ 的同横坐标点值为 $(x_0,G(x_0))$ ，那么我们可以得到相乘后的多项式 $F(x)G(x)$ 的一个点值 $(x_0,F(x_0)G(x_0))$ 。

假如两个多项式 $F(x)$ 与 $G(x)$ 的最高次项为 $p$ 和 $q$ ，那么 $F(x)G(x)$ 的最高次为 $p+q$ 。

从上面的讨论发现，要得到多项式乘法后的点值，我们只需找出若干个两两横坐标相同的点值，然后纵坐标相乘，就可以得出若干个 $F(x)G(x)$ 的点值。根据上面的证明，发现这样需要 $p+q+1$ 对点。

举个简单的例子：

$F(x)=x+1$ ，$G(x)=2x-1$

乘法后最高次为 $2$，所以取 $3$ 对点：$(0,1)(0,-1)$ 、$(1,2)(1,1)$ 和 $(2,3)(2,3)$。

于是得到新的点值为：$(0,-1)$ 、$(1,2)$ 和 $(2,9)$。

根据这三个点，列方程组解得 $F(x)G(x)=2x^2+x-1$ 。经检验发现与直接相乘结果相同。

</br>

于是，我们新引入了点值表示法，以此换一个思路解决多项式乘法问题。

先不考虑怎么将点值变回多项式，首先，在取点上就遇到了瓶颈：

对一个多项式求值的复杂度是 $O(n)$ ，取最高次对点，那么复杂度就达到了 $O(n^2)$。所以问题是怎么优化这个过程。

</br>

### 三、离散傅里叶变换（DFT）

可以看出，我们在取点的过程中，希望取的次数尽可能少，这样就能保证复杂度。

</br>

怎么让取点次数尽可能小呢？

首先考虑一些简单的情况：

$f(x)=x^2$，假如我们要对函数取 $2$ 个点，根据偶函数的性质，发现只用取一个就可以了。为什么呢？

因为 $f(x)=f(-x)$ ，这意味着我们实际上只用计算一个点，却能同时知道两个点值。

同理考虑奇函数 $f(x)=x^5$ ，要取 $2$ 个点的话，根据 $f(x)=-f(-x)$ ，同样只用计算一个点即可。

现在考虑一般的情况，

$f(x)=a_0+a_1x+a_2x^2+\cdots+a_nx^n$ ，我们想怎么同时得知两个点值。

我们先对多项式分奇偶，

$f(x)=(a_0+a_2x^2+\cdots)+(a_1x+a_3x^3+\cdots)=(a_0+a_2x^2+\cdots)+x(a_1+a_3x^2+\cdots)$

记函数
$$
P(x)=a_0+a_2x+\cdots\\
Q(x)=a_1+a_3x+\cdots
$$
原函数化为 $f(x)=P(x^2)+xQ(x^2)$。

容易发现，$P(x^2)$ 和 $Q(x^2)$ 都是偶函数。于是可以得到：

$f(x)=P(x^2)+xQ(x^2)$ 且 $f(-x)=P(x^2)-xQ(x^2)$。

假如我们分别知道 $P(x)$ 与 $Q(x)$ 两两对应的 $\frac{n}{2}$ 个点值，那么在 $O(n)$ 的时间内，我们就能得到 $n$ 个 $f(x)$ 的点值。

问题很显然了：$P(x)$ 和 $Q(x)$ 的求解，显然是两个子问题。那么有分治的可能性。

但仍然有问题：观察到 $f(x)$ 中，$P(x)$ 和 $Q(x)$ 的定义域都在 $[0,+\infty)$ ，所以并不能取横坐标符号相反的点对。

举个例子：对 $f(x)=x^3+x^2+x+1$ 求点值。按照刚刚的讨论，我们要求正负成对的 $4$ 个点。

 比如 $-2,-1,1,2$ ，但平方后 $1,4$ ，并不满足正负成对。

所以我们将 $x$ 拓展到复数域。

</br>

将 $x$ 拓展到复数域后，为平方后正负成对提供了可能性，但有没有一种取法，让其得到保证？

首先考虑上面那个实际情况。

对 $f(z)$ 求 $4$ 个点值，发现 $z^4=1$ 的解就满足**正负成对、且平方后仍正负成对**的条件。

检验一下：

$z_1=1\ \ z_2=-1\ \ z_3=i\ \ z_4=-i$ ，发现满足条件。

现在讨论一般情况，为了方便，我们将所有多项式全部看作是 $n=2^k$ 项多项式（不足的高位补 $0$）。

根据复平面的知识，$z^n=1$ 的解是复平面上单位圆上的 $n$ 等分点。

我们把复平面上第一个 $n$ 等分角所对的向量称为  $\mathbf{n}$ **次单位复根**，记为 $\omega_n$。
$$
\omega_n=e^{\frac{2\pi i}{n}}=\cos\frac{2\pi}{n}+i\sin\frac{2\pi}{n}
$$
所以我们将第 $k$ 个解记为 $\omega_n^k=\cos{\frac{2k\pi}{n}}+i\sin{\frac{2k\pi}{n}}$。

由欧拉公式，亦可得 $\omega_n^k=e^{i\frac{2k\pi }{n}}$

当 $k=0$ 时，$\omega_n^0=1$。

我们可以得到以下性质：
$$
\tag{i}(\omega_{2n}^k)^2=\omega_n^k
$$

$$
\tag{ii}\omega_{2n}^{k+n}=-\omega_{2n}^k
$$

**证明**：
$$
\tag{i}
(\omega_{2n}^k)^2=\omega_{2n}^{2k}=\cos{\frac{4k\pi}{2n}}+i\sin{\frac{4k\pi}{2n}}=\cos{\frac{2k\pi}{n}}+i\sin{\frac{2k\pi}{n}}=\omega_{n}^k
$$

$$
\tag{ii}\omega_{2n}^{k+n}=\cos\frac{2(k+n)\pi}{2n}+i\sin\frac{2(k+n)\pi}{2n}=-\cos\frac{2k\pi}{2n}-i\sin\frac{2k\pi}{2n}=-\omega_{2n}^k
$$

现在证明 $n$ 为 $2^k$ 形式时，满足正负成对。

由 $\mathrm{(ii)}$ 可知，当 $k>0$ 时，任何复根 $\omega_{n}^k$ 总能找到其相反数 $\omega_n^{k+\frac{n}{2}}$ 且一一对应。

所以平方后 $(\omega_n^k)^2=\omega_{\frac{n}{2}}^k$ 。于是平方后得到的复数集合 $S=\{z\ |\ z=\omega_{\frac{n}{2}}^k\}$ ，由上面的讨论可以发现，$S$ 的元素也是两两成对的。

</br>

现在我们已经确定了横坐标的取值，即 $x_i=\omega_n^i$ 。

那么取点值可以看作是以下线性变换：
$$
\begin{bmatrix}
y_0\\
y_1\\
y_2\\
\vdots\\
y_{n-1}
\end{bmatrix}=
\begin{bmatrix}
1 &1 &1 &\cdots &1\\
1 &\omega_{n} &\omega_{n}^2 &\cdots &\omega_{n}^{n-1}\\
1 &\omega_{n}^2 &\omega_{n}^4 &\cdots &\omega_{n}^{2n-2}\\
\vdots &\vdots &\vdots &\ddots &\vdots
\\
1 &\omega_{n}^{n-1} &\omega_{n}^{2n-2} &\cdots &\omega_{n}^{(n-1)^2}\\
\end{bmatrix}
\begin{bmatrix}
p_0\\
p_1\\
p_2\\
\vdots\\
p_{n-1}
\end{bmatrix}
$$
这个过程便叫作**离散傅里叶变换**（DFT，Discrete Fourier Transform）。

而用分治的方法在 $O(n\log n)$ 的复杂度下完成DFT，便叫作**快速傅里叶变换**（FFT，Fast Fourier Transform）。

</br>

按照最初的多项式分奇偶、正负求值方法，我们可以分治完成DFT。
$$
f(x)=P(x^2)+xQ(x^2)\\
f(-x)=P(x^2)-xQ(x^2)
$$
我们把 $x$ 替换成复数，
$$
f(\omega_n^k)=P(\omega_{\frac{n}{2}}^k)+\omega_n^kQ(\omega_{\frac{n}{2}}^k)
\\
f(\omega_n^{k+\frac{n}{2}})=P(\omega_{\frac{n}{2}}^k)-\omega_n^kQ(\omega_{\frac{n}{2}}^k)
$$
其中 $P(\omega_{\frac{n}{2}}^k)$ 与 $Q(\omega_{\frac{n}{2}}^k)$ 已经在分治的下一层处理好了，记作 $e_k$ 与 $o_k$ 。
$$
f(\omega_n^k)=e_k+\omega_n^ko_k
\\
f(\omega_n^{k+\frac{n}{2}})=e_k-\omega_n^ko_k
$$
边界条件是 $n=1$ ，此时多项式只有一个常数项，直接返回一个常数。

以下是伪代码：

```apl
def FFT(Array f,n):
	if n==1: return
	for i in [0,n) i++:
		tmp[i]=f[i]
	for i in [0,n) i++:
		if i&1:
			f[i/2+n/2]=tmp[i]
		else:
			f[i/2]=tmp[i]
	FFT(e=f,n/2),FFT(o=f+n/2,n/2)
	omg=cos(2*pi/n)+I*sin(2*pi/n)
	cur=1+I*0
	for k in [0,n/2) k++:
		tmp[k]=e[k]+cur*o[k]
		tmp[k+n/2]=e[k]-cur*o[k]
		cur=cur*omg
	for i in [0,n) i++:
		f[i]=tmp[i]
	return
```

时间复杂度 $O(n\log n)$。

以上实现方法要开辟新的空间，而且递归常数大。

我们可以考虑预处理出分治最底层每个系数所在的位置。

我们发现一个优美的性质：一个系数的最终位置为其次数的二进制翻转。

比如，一个 $7$ 次多项式的第 $4$ 次项系数最后所在的下标为 $1$。

$(4)_{10}=(100)_2$ 所以其翻转为 $(001)_2=(1)_{10}$。

我们这样考虑这个性质：对每个系数的最终下标以二进制的形式从高位到低位考虑，

假如这个系数的次数为奇数，那么肯定在最底层的右半部分。

反之则在左半部分，这样递归考虑，于是最终的下标就是次数翻转。

现在我们设计一个递推算法 $O(n)$ 求出下标翻转。

$t_i$ 表示次数为 $i$ 的最终下标，多项式项数 $n$。首先 $t_0=0$。

我们已知 $t_{\lfloor\frac{i}{2}\rfloor}$，也就是说，我们知道 $i$ 右移 $1$ 位的翻转。于是我们将这个翻转再右移一位，还原回 $t_i$。还有个问题，右移 $i$ 会损失最低位，所以我们将原来 $i$ 的最低位补在 $t_i$ 的最高位。

得到递推式：
$$
t_i=\lfloor\frac{t_{\lfloor\frac{i}{2}\rfloor}}{2} \rfloor+\frac{n}{2}(i\bmod 2)
$$
给出伪代码：

```apl
def init(Array f,n):
	t[0]=0
	for i in [1,n) i++:
		t[i]=t[i>>1]>>1
		if i&1:
			t[i]|=n>>1
	for i in [0,n) i++:
		if i<t[i]:
			swap(f[i],f[t[i]])
	return
```

根据这个预处理，我们就能写出非递归版的FFT：

```apl
def FFT(Array f,n):
	init(f,n)
	for i in [2,n] i*=2:
		omg=cos(2*pi/i)+I*sin(2*pi/i)
		for j in [0,n) j+=i:
			cur=1+0*I
			for k in [j,j+i/2) k++:
				e=f[k]
				o=f[k+i/2]
				f[k]=e+cur*o
				f[k+i/2]=e-cur*o
				cur*=omg
	return	
```

</br>


### 四、离散傅里叶逆变换（IDFT）

完成了刚刚的工作，我们终于把目标多项式的点值表达求出来了。

但我们一开始要的是系数表示法。也就是说，我们已经得到了线性变换
$$
\begin{bmatrix}
y_0\\
y_1\\
y_2\\
\vdots\\
y_{n-1}
\end{bmatrix}=
\begin{bmatrix}
1 &1 &1 &\cdots &1\\
1 &\omega_{n} &\omega_{n}^2 &\cdots &\omega_{n}^{n-1}\\
1 &\omega_{n}^2 &\omega_{n}^4 &\cdots &\omega_{n}^{2n-2}\\
\vdots &\vdots &\vdots &\ddots &\vdots
\\
1 &\omega_{n}^{n-1} &\omega_{n}^{2n-2} &\cdots &\omega_{n}^{(n-1)^2}\\
\end{bmatrix}
\begin{bmatrix}
p_0\\
p_1\\
p_2\\
\vdots\\
p_{n-1}
\end{bmatrix}
$$
中的列向量 $\begin{bmatrix}y_0\\y_1\\y_2\\\vdots\\y_{n-1}\end{bmatrix}$  ，要反过来求解初始向量。这个过程本质是解一个 $n$ 元方程组，可以用高斯消元法。

但是高斯消元复杂度为 $O(n^3)$，如果用高斯消元，意味着我们前面的努力都白费了。

从线性代数的角度查看，实际上就是在求
$$
\begin{bmatrix}
p_0\\
p_1\\
p_2\\
\vdots\\
p_{n-1}
\end{bmatrix}=
\begin{bmatrix}
1 &1 &1 &\cdots &1\\
1 &\omega_{n} &\omega_{n}^2 &\cdots &\omega_{n}^{n-1}\\
1 &\omega_{n}^2 &\omega_{n}^4 &\cdots &\omega_{n}^{2n-2}\\
\vdots &\vdots &\vdots &\ddots &\vdots
\\
1 &\omega_{n}^{n-1} &\omega_{n}^{2n-2} &\cdots &\omega_{n}^{(n-1)^2}\\
\end{bmatrix}^{-1}
\begin{bmatrix}
y_0\\
y_1\\
y_2\\
\vdots\\
y_{n-1}
\end{bmatrix}
$$
这个过程被称为**离散傅里叶逆变换**。

注意到中间这个矩阵十分特殊，所以这个矩阵的逆也是特殊的。

这个矩阵特殊之处就在于，它的逆矩阵就是它的共轭矩阵乘$\frac{1}{n}$。

也就是说，
$$
\begin{bmatrix}
1 &1 &1 &\cdots &1\\
1 &\omega_{n} &\omega_{n}^2 &\cdots &\omega_{n}^{n-1}\\
1 &\omega_{n}^2 &\omega_{n}^4 &\cdots &\omega_{n}^{2n-2}\\
\vdots &\vdots &\vdots &\ddots &\vdots
\\
1 &\omega_{n}^{n-1} &\omega_{n}^{2n-2} &\cdots &\omega_{n}^{(n-1)^2}\\
\end{bmatrix}^{-1}=
\frac{1}{n}
\begin{bmatrix}
1 &1 &1 &\cdots &1\\
1 &\omega_{n}^{-1} &\omega_{n}^{-2} &\cdots &\omega_{n}^{1-n}\\
1 &\omega_{n}^{-2} &\omega_{n}^{-4} &\cdots &\omega_{n}^{2-n}\\
\vdots &\vdots &\vdots &\ddots &\vdots
\\
1 &\omega_{n}^{-n+1} &\omega_{n}^{2-2n} &\cdots &\omega_{n}^{-(n-1)^2}\\
\end{bmatrix}
$$
只是将单位复根变为了 $\omega_n^{-1}$ 。

于是我们可以直接套用FFT，只不过改一下单位复根，并在最后把答案乘上 $\frac{1}{n}$ 就能复原出原来的多项式。

这个过程叫作**快速傅里叶逆变换**。

```apl
def IFFT(Array f,n):
	init(f,n)
	for i in [2,n] i*=2:
		omg=cos(2*pi/i)-I*sin(2*pi/i)
		for j in [0,n) j+=i:
			cur=1+0*I
			for k in [j,j+i/2) k++:
				e=f[k]
				o=f[k+i/2]
				f[k]=e+cur*o
				f[k+i/2]=e-cur*o
				cur*=omg
	for i in [0,n) i++
		f[i].a/=n
	return	
```

也可以把这个函数同FFT包装在一起。

</br>

至此，快速傅里叶变换算法介绍完毕。

</br>

### 附、Vandermonde 行列式的证明

（这个证明过程一般线性代数的教材里都有）

证明 Vandermonde行列式：
$$
\begin{vmatrix}
1 &1 &1 &\cdots &1\\
x_0 &x_1 &x_2 &\cdots &x_n\\
\vdots &\vdots &\vdots &\ddots &\vdots
\\
x_0^n &x_1^n &x_2^n &\cdots &x_n^n\\
\end{vmatrix}=\prod_\limits{0\leq j<i\leq n}(x_i-x_j)
$$
用归纳法证明。当 $n=1$ 时，
$$
\begin{vmatrix}
1 &1\\
x_0 &x_1
\end{vmatrix}=x_1-x_0
$$
成立。现在假设对于 $n-1$ 的 Vandermonde 行列式成立，证明 $n$ 也成立。$(n>2)$
$$
\begin{equation}

\begin{vmatrix}
1 &1 &1 &\cdots &1\\
x_0 &x_1 &x_2 &\cdots &x_n\\
x_0^2 &x_1^2 &x_2^2 &\cdots &x_n^2\\
\vdots &\vdots &\vdots &\ddots &\vdots
\\
x_0^n &x_1^n &x_2^n &\cdots &x_n^n\\
\end{vmatrix}
\xlongequal{r_i-x_0\times r_{i-1}} 
\begin{vmatrix}
1 &1 &1 &\cdots &1\\
0 &x_1-x_0 &x_2-x_0 &\cdots &x_n-x_0\\
0 &x_1(x_1-x_0) &x_2(x_2-x_0) &\cdots &x_n(x_n-x_0)\\
\vdots &\vdots &\vdots &\ddots &\vdots
\\
0 &x_1^{n-1}(x_1-x_0) &x_2^{n-1}(x_2-x_0) &\cdots &x_n^{n-1}(x_n-x_0)\\
\end{vmatrix}
\end{equation}
$$

$$
\xlongequal{\ \ \ \ \ \ \ \ \ \ \ \ \ \ \ \ }
\begin{vmatrix}

x_1-x_0 &x_2-x_0 &\cdots &x_n-x_0\\
x_1(x_1-x_0) &x_2(x_2-x_0) &\cdots &x_n(x_n-x_0)\\
\vdots &\vdots &\ddots &\vdots
\\
x_1^{n-1}(x_1-x_0) &x_2^{n-1}(x_2-x_0) &\cdots &x_n^{n-1}(x_n-x_0)\\
\end{vmatrix}
$$

$$
\xlongequal{\ \ \ \ \ \ \ }
(x_1-x_0)(x_2-x_0)\cdots(x_n-x_0)
\begin{vmatrix}
1 &1 &\cdots &1\\
x_1 &x_2 &\cdots &x_n\\
\vdots &\vdots &\ddots &\vdots
\\
x_1^{n-1} &x_2^{n-1} &\cdots &x_n^{n-1}\\
\end{vmatrix}
$$

$$
\xlongequal{\ \ \ \ \ \ \ }
\prod \limits_{1\leq i\leq n}(x_i-x_0) \times\prod \limits_{1\leq j<i\leq n}(x_i-x_j)
\xlongequal{\ \ \ \ \ \ \ }
\prod \limits_{0\leq j<i\leq n}(x_i-x_j) 
\tag*{Q.E.D.}
$$

