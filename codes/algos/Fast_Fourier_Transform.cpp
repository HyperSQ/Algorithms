#include <cstdio>
#include <complex>
#include <cmath>
using namespace std;

const int maxn=4e6+5;
const double pi=acos(-1);
typedef complex<double> Complex;
int n,m;
Complex f[maxn],g[maxn];
Complex ans[maxn];
int t[maxn];

void init(Complex *y,int len){
	t[0]=0;
	for(int i=1;i<len;i++){
		t[i]=(t[i>>1]>>1)+(i&1?len>>1:0);
	}
	for(int i=0;i<len;i++){
		if(i<t[i]) swap(y[i],y[t[i]]);
	}
}

void FFT(Complex *f,int n,int inv){
	init(f,n);
	for(int len=2;len<=n;len<<=1){
		Complex omg(cos(2.0*pi/len),sin(inv*2.0*pi/len));
		for(int i=0;i<n;i+=len){
			Complex cur(1,0);
			for(int k=i;k<i+len/2;k++){
				Complex e=f[k];
				Complex o=cur*f[k+len/2];
				f[k]=e+o;
				f[k+len/2]=e-o;
				cur*=omg;
			}
		}
	}
	if(inv==-1){
		for(int i=0;i<=n;i++) f[i]/=n;
	}
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=0;i<=n;i++) scanf("%lf",&f[i]);
	for(int i=0;i<=m;i++) scanf("%lf",&g[i]);
	int len=1;
	while(len<n+m+1) len<<=1;
	FFT(f,len,1);
	FFT(g,len,1);
	for(int i=0;i<len;i++) ans[i]=f[i]*g[i];
	FFT(ans,len,-1);
	for(int i=0;i<=n+m;i++){
		printf("%d ",(int)(ans[i].real()+0.5));
	}
}
