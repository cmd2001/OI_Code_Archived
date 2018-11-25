//Cv3110_By_Cmd2001
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=5e5+1e2;

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
		root->val=2147483647;
		root->siz=1;
	}
	inline void update(node* pos)
	{
		pos->siz=1;
		if(pos->lson) pos->siz+=pos->lson->siz;
		if(pos->rson) pos->siz+=pos->rson->siz;
	}
	
	inline void zig(node* pos)
	{
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
	
	inline void dfs(node* pos)
	{
		if(pos->lson) dfs(pos->lson);
		if(pos->val!=2147483647) printf("%d ",pos->val);
		if(pos->rson) dfs(pos->rson);
	}
		
}splay;

inline int getint()
{
	int ret=0,fix=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') fix=-1; ch=getchar();}
	while(ch>='0'&&ch<='9')
		ret=ret*10+(ch-'0'),
		ch=getchar();
	return ret*fix;
}
int main()
{
	static int n=getint();
	
	while(n--)
		splay.insert(getint());
	
	splay.dfs(splay.root);
	
	return 0;
}
	
	
		
	

	
