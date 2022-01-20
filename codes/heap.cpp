#include <cstdio>
using namespace std;

const int maxn=1e6+5;
int n;

void swap(int &x,int &y){
	x^=y^=x^=y;
}

struct HEAP{
	int heap[maxn],sz;
	HEAP(){sz=0;}
	void push(int x){
		heap[++sz]=x;
		int cur=sz;
		while(cur>1){
			int p=cur>>1;
			if(heap[p]<heap[cur]) break;
			swap(heap[p],heap[cur]);
			cur=p;
		}
	}
	void pop(){
		swap(heap[sz],heap[1]);sz--;
		int cur=1;
		while((cur<<1)<=sz){
			int son=cur<<1;
			if(son<sz&&heap[son+1]<heap[son]) son++;
			if(heap[cur]<heap[son]) break;
			swap(heap[cur],heap[son]);
			cur=son;
		}
	}
	int top(){
		return heap[1];
	}
	bool empty(){
		return sz==0;
	}
}heap;

int main(){
	scanf("%d",&n);
	while(n--){
		int op,x;
		scanf("%d",&op);
		if(op==1){
			scanf("%d",&x);
			heap.push(x);
		}else if(op==2){
			printf("%d\n",heap.top());
		}else{
			heap.pop();
		}
	}
}
