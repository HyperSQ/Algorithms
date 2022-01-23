#include <cstdio>
#include <cstdlib>
#define ll long long
using namespace std;

const int maxq=2e5+5;

inline void swap(int &x,int &y){
	x^=y^=x^=y;
}

struct node{
	int sz,val,p;
	int l,r;
	bool lz;ll sum;
}t[maxq<<7];

int a,b,c,tot;

inline int newnode(int key){
	++tot;
	t[tot].sz=1,t[tot].val=key,t[tot].p=rand(),t[tot].sum=key;
	return tot;
}

inline void update(int u){
	t[u].sz=t[t[u].l].sz+t[t[u].r].sz+1;
	t[u].sum=t[t[u].l].sum+t[t[u].r].sum+t[u].val;
}

inline int copynode(int u){
	tot++,t[tot]=t[u];
	return tot;
}

inline void pushdown(int u){
	if(t[u].lz){
		if(t[u].l) t[u].l=copynode(t[u].l);
		if(t[u].r) t[u].r=copynode(t[u].r);
		swap(t[u].l,t[u].r);
		if(t[u].l) t[t[u].l].lz^=1;
		if(t[u].r) t[t[u].r].lz^=1;
		t[u].lz=0;
	}
}

void split(int u,int key,int &x,int &y){
	if(!u){x=y=0;return;}
	pushdown(u);
	if(t[t[u].l].sz<key) x=copynode(u),split(t[x].r,key-t[t[u].l].sz-1,t[x].r,y),update(x);
	else y=copynode(u),split(t[y].l,key,x,t[y].l),update(y);
}

int merge(int u,int v){
	if(!u||!v) return u+v;
	int x;
	if(t[u].p>t[v].p){
		pushdown(u);
		x=copynode(u);t[x].r=merge(t[x].r,v);
	}else{
		pushdown(v);
		x=copynode(v);t[x].l=merge(u,t[x].l);
	}
	update(x);
	return x;
}

void insert(int &root,int key,int p){
	split(root,p,a,b);
	root=merge(merge(a,newnode(key)),b);
}

void erase(int &root,int p){
	split(root,p,a,c);
	split(a,p-1,a,b);
	root=merge(merge(a,merge(t[b].l,t[b].r)),c);
}

void reverse(int &root,int l,int r){
	split(root,l-1,a,c);
	split(c,r-l+1,b,c);
	t[b].lz^=1;
	root=merge(merge(a,b),c);
}

ll get_sum(int &root,int l,int r){
	split(root,l-1,a,c);
	split(c,r-l+1,b,c);
	ll ret=t[b].sum;
	root=merge(merge(a,b),c);
	return ret;
}

int n,rt[maxq<<1];
int ver;

int main(){
	scanf("%d",&n);
	ll v,op,x,p;
	while(n--){
		scanf("%lld%lld%lld",&v,&op,&p);
		rt[++ver]=rt[v];
		switch(op){
			case 1:
				scanf("%lld",&x);
				insert(rt[ver],x,p);
				break;
			case 2:
				erase(rt[ver],p);
				break;
			case 3:
				scanf("%lld",&x);
				reverse(rt[ver],p,x);
				break;
			case 4:
				scanf("%lld",&x);
				printf("%lld\n",get_sum(rt[ver],p,x));
				break;
		}
	}
}
