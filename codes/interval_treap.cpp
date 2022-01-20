#include <cstdio>
#include <cstdlib>
//文艺平衡树 (无旋Treap) 
struct node{
	node *l,*r;
	int val,p,sz,lz;
	node(int key,node *son){l=r=son,val=key,p=rand(),sz=1,lz=0;}
	node(){l=r=this,val=p=lz=sz=0;}
	bool empty(){return sz==0;}
}*emp=new node(),*root=emp,*a,*b,*c;

void update(node *u){
	u->sz=u->l->sz+u->r->sz+1;
}

void swap(node *&u,node *&v){
	node *temp=u;
	u=v,v=temp;
}

void pushdown(node *u){
	if(u->lz){
		swap(u->l,u->r);
		u->lz=false;
		u->l->lz^=1,u->r->lz^=1;
	}
}

void split(node *u,int sz,node *&x,node *&y){
	if(u->empty()){
		x=y=emp;return;
	}
	pushdown(u);
	if(u->l->sz<sz) x=u,split(u->r,sz-u->l->sz-1,u->r,y);
	else y=u,split(u->l,sz,x,y->l);
	update(u);
}

node *merge(node *u,node *v){
	if(u->empty()||v->empty()){
		return u->empty()?v:u;
	}
	if(u->p>v->p){
		pushdown(u);
		u->r=merge(u->r,v),update(u);return u;
	}else{
		pushdown(v);
		v->l=merge(u,v->l),update(v);return v;
	}
}

void reverse(int l,int r){
	split(root,l-1,a,c);
	split(c,r-l+1,b,c);
	b->lz^=1;
	root=merge(merge(a,b),c);
}

void get_ans(node *u){
	if(u->empty()) return;
	pushdown(u);
	get_ans(u->l);
	printf("%d ",u->val);
	get_ans(u->r);
}

int n,m;

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		root=merge(root,new node(i,emp));
	}
	while(m--){
		int l,r;
		scanf("%d%d",&l,&r);
		reverse(l,r);
	}
	get_ans(root);
}
