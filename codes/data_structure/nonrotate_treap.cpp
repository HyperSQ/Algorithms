#include <cstdio>
#include <cstdlib>

struct node{
	int val,sz,p;
	node *l,*r;
	node(int key,node *son){l=r=son;val=key,sz=1,p=rand();}
	node(){l=r=this,val=sz=p=0;}
	bool empty(){return sz==0;}
};

struct nonro_treap{
	node *emp,*root;
	node *a,*b,*c;
	nonro_treap(){
		emp=new node();
		root=emp;
	}
	inline void update(node *u){
		u->sz=u->l->sz+u->r->sz+1;
	}
	void split(node *u,int key,node *&x,node *&y){
		if(u->empty()){
			x=y=emp;return;
		}
		if(u->val<=key) x=u,split(u->r,key,u->r,y);
		else y=u,split(u->l,key,x,u->l);
		update(u);
	}
	node *merge(node *u,node *v){
		if(u->empty()||v->empty()) return u->empty()?v:u;
		if(u->p>v->p){
			u->r=merge(u->r,v),update(u);return u;
		}
		else{
			v->l=merge(u,v->l),update(v);return v;
		}
	}
	inline void insert(int key){
		split(root,key,a,b);
		root=merge(merge(a,new node(key,emp)),b);
	}
	inline void erase(int key){
		split(root,key,a,c);
		split(a,key-1,a,b);
		root=merge(merge(a,merge(b->l,b->r)),c);
		if(!b->empty()) delete b;
	}
	inline int rnk(int key){
		split(root,key-1,a,b);
		int ans=a->sz+1;
		root=merge(a,b);
		return ans;
	}
	inline int num(int x){
		node *cur=root;
		while(true){
			if(x==cur->l->sz+1) break;
			if(x<=cur->l->sz) cur=cur->l;
			else x-=cur->l->sz+1,cur=cur->r;
		}
		return cur->val;
	}
	inline int pre(int key){
		split(root,key-1,a,b);
		register node *cur=a;
		while(!cur->r->empty()) cur=cur->r;
		root=merge(a,b);
		return cur->val;
	}
	inline int nxt(int key){
		split(root,key,a,b);
		register node *cur=b;
		while(!cur->l->empty()) cur=cur->l;
		root=merge(a,b);
		return cur->val;
	}
}bst;

int n;

int main(){
	scanf("%d",&n);
	while(n--){
		int op,x;
		scanf("%d%d",&op,&x);
		switch(op){
			case 1:
				bst.insert(x);
				break;
			case 2:
				bst.erase(x);
				break;
			case 3:
				printf("%d\n",bst.rnk(x));
				break;
			case 4:
				printf("%d\n",bst.num(x));
				break;
			case 5:
				printf("%d\n",bst.pre(x));
				break;
			case 6:
				printf("%d\n",bst.nxt(x));
				break;
		}
	}
}
