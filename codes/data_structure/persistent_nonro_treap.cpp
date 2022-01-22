#include <bits/stdc++.h>
using namespace std;

const int maxq=5e5+5;

struct node{
	int sz,val,p;
	int l,r;
	node(){val=sz=p=0,l=r=0;}
}t[maxq*25];
int a,b,c,tot;
int rt[maxq];

void update(int u){
	t[u].sz=t[t[u].l].sz+t[t[u].r].sz+1;
}

int newnode(int key){
	++tot;t[tot].p=rand(),t[tot].sz=1,t[tot].val=key;
	t[tot].l=t[tot].r=0;
	return tot;
}

void split(int u,int key,int &x,int &y){
	if(!u){x=y=0;return;}
	if(t[u].val<=key) x=++tot,t[x]=t[u],split(t[x].r,key,t[x].r,y),update(x);
	else y=++tot,t[y]=t[u],split(t[y].l,key,x,t[y].l),update(y);
}

int merge(int u,int v){
	if(!u||!v) return u+v;
	int x=++tot;
	if(t[u].p>t[v].p){
		t[x]=t[u],t[x].r=merge(t[x].r,v);
	}else{
		t[x]=t[v],t[x].l=merge(u,t[x].l);
	}
	update(x);return x;
}

void insert(int &root,int key){
	split(root,key,a,b);
	root=merge(merge(a,newnode(key)),b);
}

void erase(int &root,int key){
	split(root,key,a,c);
	split(a,key-1,a,b);
	root=merge(merge(a,merge(t[b].l,t[b].r)),c);
}

int rnk(int &root,int key){
	split(root,key-1,a,b);
	int ans=t[a].sz+1;
	root=merge(a,b);
	return ans;
}

int num(int root,int x){
	int cur=root;
	while(true){
		if(x==t[t[cur].l].sz+1) break;
		if(x<=t[t[cur].l].sz) cur=t[cur].l;
		else x-=t[t[cur].l].sz+1,cur=t[cur].r;
	}
	return t[cur].val;
}

int pre(int &root,int key){
	split(root,key-1,a,b);
	int cur=a;
	while(t[cur].r) cur=t[cur].r;
	root=merge(a,b);
	return t[cur].val;
}

int nxt(int &root,int key){
	split(root,key,a,b);
	int cur=b;
	while(t[cur].l) cur=t[cur].l;
	root=merge(a,b);
	return t[cur].val;
}

int n,ver;

int main(){
	scanf("%d",&n);
	int v,key,op;
	rt[0]=0;
	while(n--){
		scanf("%d%d%d",&v,&op,&key);
		rt[++ver]=rt[v];
		switch(op){
			case 1:
				insert(rt[ver],key);
				break;
			case 2:
				erase(rt[ver],key);
				break;
			case 3:
				printf("%d\n",rnk(rt[ver],key));
				break;
			case 4:
				printf("%d\n",num(rt[ver],key));
				break;
			case 5:
				printf("%d\n",pre(rt[ver],key));
				break;
			case 6:
				printf("%d\n",nxt(rt[ver],key));
				break;
		}
	}
}
