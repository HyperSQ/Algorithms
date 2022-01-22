#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn=1e6+5;
const int maxm=1e6+5;
int n,m;

inline int num(int x){
	return x<<1;
}

inline int N(int x){
	return x^1;
}

struct node{
	int v,nxt;
}edge[maxm*5];int head[maxn],cntE;

void add(int u,int v){
	edge[++cntE]=(node){v,head[u]};
	head[u]=cntE;
}

int stk[maxn],dfn[maxn],low[maxn],clk,top,id[maxn],scc;

void tarjan(int u){
	stk[++top]=u;
	dfn[u]=low[u]=++clk;
	for(int i=head[u];i;i=edge[i].nxt){
		int v=edge[i].v;
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}else if(!id[v]){
			low[u]=min(low[u],dfn[v]);
		}
	}
	if(low[u]==dfn[u]){
		scc++;
		while(true){
			int v=stk[top--];
			id[v]=scc;
			if(u==v) break;
		}
	}
}

bool ans=1;

int main(){
	scanf("%d%d",&n,&m);
	for(int p=1;p<=m;p++){
		int i,a,j,b;
		scanf("%d%d%d%d",&i,&a,&j,&b);
		i=num(i);j=num(j);
		int u=a?i:N(i);
		int v=b?j:N(j);
		add(N(u),v);
		add(N(v),u);
	}
	for(int i=2;i<=2*n+1;i++){
		if(!id[i]) tarjan(i);
	}
	for(int i=1;i<=n;i++){
		int u=num(i);
		if(id[u]==id[N(u)]) ans=0;
	}
	if(!ans){
		puts("IMPOSSIBLE");
	}else{
		puts("POSSIBLE");
		for(int i=1;i<=n;i++){
			int u=num(i);
			printf("%d ",id[u]<id[N(u)]?1:0);
		}
	}
}
