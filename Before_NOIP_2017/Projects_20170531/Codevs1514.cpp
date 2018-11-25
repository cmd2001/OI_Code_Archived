#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=16e4+1e2;
struct node
{
    int dat,siz; // dat is the number of the book
    node *lson,*rson,*fa;
}splay[maxn],*pnt[maxn],*root,*st,*ed;
int m,n,cnt;
inline void update(node *x)
{
    x->siz=1;
    if(x->lson) x->siz+=x->lson->siz;
    if(x->rson) x->siz+=x->rson->siz;
}
inline void zig(node *x)
{
    node *fa=x->fa;
    if(!fa->fa) root=x;
    else if(fa==fa->fa->lson) fa->fa->lson=x;
    else if(fa==fa->fa->rson) fa->fa->rson=x;
    x->fa=fa->fa;
    fa->lson=x->rson;
    if(x->rson) x->rson->fa=fa;
    fa->fa=x;
    x->rson=fa;
    update(fa);
    update(x);
    if(x->fa) update(x->fa);
}
inline void zag(node *x)
{
    node *fa=x->fa;
    if(!fa->fa) root=x;
    else if(fa==fa->fa->lson) fa->fa->lson=x;
    else if(fa==fa->fa->rson) fa->fa->rson=x;
    x->fa=fa->fa;
    fa->rson=x->lson;
    if(x->lson) x->lson->fa=fa;
    fa->fa=x;
    x->lson=fa;
    update(fa);
    update(x);
    if(x->fa) update(x->fa);
}
inline void splay_to_root(node *x)
{
	node *fa,*ffa;
	while(x!=root)
	{
		fa=x->fa,ffa=x->fa->fa;
		if(!ffa)
		{
			if(x==fa->lson) zig(x);
			else zag(x);
		}
		else if(fa==ffa->lson)
		{
			zig(fa);
			fa=x->fa;
			if(x==fa->lson) zig(x);
			else zag(x);
		}
		else  if(fa==ffa->rson)
		{
			zag(fa);
			fa=x->fa;
			if(x==fa->lson) zig(x);
			else zag(x);
		}
	}
}
inline void splay_to_rson(node *x)
{
	node *fa,*ffa;
	while(x!=root->rson)
	{
		fa=x->fa,ffa=x->fa->fa;
		if(fa==root->rson)
		{
			if(x==fa->lson) zig(x);
			else zag(x);
		}
		else if(fa==ffa->lson)
		{
			zig(fa);
			fa=x->fa;
			if(x==fa->lson) zig(x);
			else zag(x);
		}
		else if(fa==ffa->rson)
		{
			zag(fa);
			fa=x->fa;
			if(x==fa->lson) zig(x);
			else zag(x);
		}
	}
}
inline node* son_prev(node *x)
{
	x=x->lson;
	while(x->rson) x=x->rson;
	return x;
}
inline node* son_next(node *x)
{
	x=x->rson;
	while(x->lson) x=x->lson;
	return x;
}
inline void del(node *x)
{
	splay_to_root(x);
	node *prev=son_prev(x),*next=son_next(x);
	splay_to_root(prev);
	splay_to_rson(next);
	x->fa=NULL;
	root->rson->lson=NULL;
	root->rson->siz--;
	root->siz--;
}
inline void insert_to_begin(node *x)
{
	node *pos=root;
	while(1)
	{
		pos->siz++;
		if(pos->lson) pos=pos->lson;
		else
		{	
			pos->lson=x;
			x->fa=pos;
			x->siz=1;
			return;
		}
	}
}
inline void insert_to_end(node *x)
{
	node *pos=root;
	while(1)
	{
		pos->siz++;
		if(pos->rson) pos=pos->rson;
		else
		{
			pos->rson=x;
			x->fa=pos;
			x->siz=1;
			return;
		}
	}
}
inline node* get_kth(int x)
{
	node *pos=root;
	while(1)
	{
		if(!pos->lson)
		{
			if(x==1) return pos;
			else pos=pos->rson,x--;
		}
		else
		{
			if(x==pos->lson->siz+1) return pos;
			else if(x<=pos->lson->siz) pos=pos->lson;
			else x-=pos->lson->siz+1,pos=pos->rson;
		}
	}
}
int main()
{
	scanf("%d%d",&n,&m);
	st=root=&splay[0];
	root->siz=1;
	for(int i=1,x;i<=n;i++)
	{
		scanf("%d",&x);
		pnt[x]=&splay[++cnt];
		pnt[x]->dat=x;
		insert_to_end(&splay[cnt]);
	}
	insert_to_end(ed=&splay[++cnt]);
	char c[10];
	for(int i=1,x,d;i<=m;i++)
	{
		scanf("%s%d",c,&x);
		if(*c=='A')
		{
			splay_to_root(pnt[x]);
			update(root);
			printf("%d\n",root->lson->siz-1);
		}
		if(*c=='Q')
		{
			x++;
			node *tmp=get_kth(x);
			printf("%d\n",tmp->dat);
		}
		else if(*c=='I')
		{
			scanf("%d",&d);
			if(!d) continue;
			splay_to_root(pnt[x]);
			if(d==-1)
			{
				node *now=pnt[x],*tmp=son_prev(pnt[x]);
				swap(pnt[x],pnt[tmp->dat]);
				swap(now->dat,tmp->dat);
			}
			else if(d==1)
			{
				node *now=pnt[x],*tmp=son_next(pnt[x]);
				swap(pnt[x],pnt[tmp->dat]);
				swap(now->dat,tmp->dat);
			}
		}
		else if(*c=='T')
		{
			node *tmp=pnt[x];
			del(pnt[x]);
			splay_to_root(st);
			splay_to_root(son_next(root));
			root->lson=NULL;
			root->siz--;
			st->fa=NULL;
			insert_to_begin(tmp);
			insert_to_begin(st);
		}
		else if(*c=='B')
		{
			node *tmp=pnt[x];
			del(pnt[x]);
			splay_to_root(ed);
			splay_to_root(son_prev(root));
			root->rson=NULL;
			root->siz--;
			ed->fa=NULL;
			insert_to_end(tmp);
			insert_to_end(ed);
		}
	}
	return 0;
}
			

