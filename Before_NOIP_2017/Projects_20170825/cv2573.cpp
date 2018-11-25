#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=(3e4+1e2)*4;

struct SPLAY
{
	struct node
	{
		int val,siz;
		node *lson,*rson,*fa;
	}Splay[maxn],*root;
	
	inline node* newnode()
	{
		static int cnt=0;
		return &Splay[++cnt];
	}
	SPLAY()
	{
		root=newnode();
		//debug<<"root="<<root-Splay<<endl;
		root->val=2147483647;
		root->siz=1;
	}
	inline void update(node* pos)
	{
		pos->siz=1;
		if(pos->lson) pos->siz+=pos->lson->siz;
		if(pos->rson) pos->siz+=pos->rson->siz;
	}
	
	inline void zig(node* pos) // pos is fa
	{
		//debug<<"zig "<<pos-Splay<<endl;
		node *son=pos->lson;
		son->fa=pos->fa;
		if(pos->fa)
			if(pos==pos->fa->lson) pos->fa->lson=son;
			else pos->fa->rson=son;
		else root=son;
		pos->lson=son->rson;
		if(son->rson) son->rson->fa=pos;
		son->rson=pos;
		pos->fa=son;
		update(pos);
		update(son);
	}
	inline void zag(node* pos)
	{
		//debug<<"zag "<<pos-Splay<<endl;
		node *son=pos->rson;
		son->fa=pos->fa;
		if(pos->fa)
			if(pos==pos->fa->lson) pos->fa->lson=son;
			else pos->fa->rson=son;
		else root=son;
		pos->rson=son->lson;
		if(son->lson) son->lson->fa=pos;
		son->lson=pos;
		pos->fa=son;
		update(pos);
		update(son);
	}
	inline void splay(node* pos)
	{
		while(pos!=root)
		{
			if(!pos->fa->fa)
			{
				if(pos==pos->fa->lson) zig(pos->fa);
				else zag(pos->fa);
			}
			else
			{
				node *fa=pos->fa;
				if(fa==fa->fa->lson) zig(fa->fa);
				else zag(fa->fa);
				if(pos==root) return;
				if(pos==pos->fa->lson) zig(pos->fa);
				else zag(pos->fa);
			}
		}
	}
	inline void insert(int val)
	{
		node* pos=root;
		while(1)
		{
			pos->siz++;
			if(val<pos->val)
			{
				if(pos->lson) pos=pos->lson;
				else
				{
					pos->lson=newnode();
					pos->lson->val=val;
					pos->lson->siz=1;
					pos->lson->fa=pos;
					pos=pos->lson;
					break;
				}
			}
			else
			{
				if(pos->rson) pos=pos->rson;
				else
				{
					pos->rson=newnode();
					pos->rson->val=val;
					pos->rson->siz=1;
					pos->rson->fa=pos;
					pos=pos->rson;
					break;
				}
			}
		}
		splay(pos);
	}
	inline int kth(int k)
	{
		int num;
		node* pos=root;
		while(1)
		{
			num=pos->lson?pos->lson->siz+1:1;
			if(num==k) return pos->val;
			if(k<=num) pos=pos->lson;
			else k-=num,pos=pos->rson;
		}
	}
	inline void dfs(node* pos)
	{
		cout<<"{";
		if(pos->lson) dfs(pos->lson);
		cout<<",";
		cout<<pos->val;
		cout<<",";
		if(pos->rson) dfs(pos->rson);
		cout<<"}";
	}
			
}splay;

struct qnode
{
	int pos,id,val; // id == 0 means insert , id == 1 means query ;
	friend bool operator < (const qnode &a,const qnode &b)
	{
		return a.pos==b.pos?a.id<b.id:a.pos<b.pos;
	}
}qs[maxn];

int n,m,cnt;
	
int main()
{
	scanf("%d%d",&m,&n);
	
	for(int i=1,x;i<=m;i++)
	{
		scanf("%d",&x);
		qs[++cnt].id=0;
		qs[cnt].val=x;
		qs[cnt].pos=i;
	}
	for(int i=1,x;i<=n;i++)
	{
		scanf("%d",&x);
		qs[++cnt].id=1;
		qs[cnt].val=i;
		qs[cnt].pos=x;
	}
	
	sort(qs+1,qs+1+cnt);
	
	/*for(int i=1;i<=cnt;i++)
		debug<<"i="<<i<<"id="<<qs[i].id<<endl;*/
	
	for(int i=1;i<=cnt;i++)
	{
		//splay.dfs(splay.root);
		//debug<<"root="<<splay.root-splay.Splay<<endl;
		if(qs[i].id==0)
			splay.insert(qs[i].val);
		else
		{
			//debug<<"qureying kth"<<qs[i].val<<endl;
			printf("%d\n",splay.kth(qs[i].val));
		}
	}
	
	
	return 0;
	
}

		
	

	
