#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=2e5+1e2;
struct node
{
    int dat,siz;
    bool rev;
    node *lson,*rson,*fa;
}splay[maxn],*nxt[maxn];
int m,n;
inline void update(node *x)
{
    x->siz=1;
    if(x->lson) x->siz+=x->lson->siz;
    if(x->rson) x->siz+=x->rson->siz;
}
inline void push_down(node *x)
{
    if(x->rev)
    {
        if(x->lson) x->lson->rev^=1;
        if(x->rson) x->rson->rev^=1;
        swap(x->lson,x->rson);
        x->rev=0;
    }
}
inline void push_up(node *x)
{
	if(x->fa&&(x==x->fa->lson||x==x->fa->rson)) push_up(x->fa);
	push_down(x);
}
inline void zig(node *x)
{
    node *fa=x->fa;
    if(!fa->fa) ;
    else if(fa==fa->fa->lson) fa->fa->lson=x;
    else if(fa==fa->fa->rson) fa->fa->rson=x;
    x->fa=fa->fa;
    fa->lson=x->rson;
    if(x->rson) x->rson->fa=fa;
    fa->fa=x;
    x->rson=fa;
    update(fa);
    update(x);
    //if(x->fa) update(x->fa);
}
inline void zag(node *x)
{
    node *fa=x->fa;
    if(!fa->fa) ;
    else if(fa==fa->fa->lson) fa->fa->lson=x;
    else if(fa==fa->fa->rson) fa->fa->rson=x;
    x->fa=fa->fa;
    fa->rson=x->lson;
    if(x->lson) x->lson->fa=fa;
    fa->fa=x;
    x->lson=fa;
    update(fa);
    update(x);
    //if(x->fa) update(x->fa);
}
inline void debug_node(node *x)
{
	if(!x) return;
	debug<<"node="<<x-splay<<endl;
	if(x->lson) debug<<"lson="<<x->lson-splay<<endl;
	if(x->rson) debug<<"rson="<<x->rson-splay<<endl;
	debug<<"fa="<<x->fa-splay<<endl;
}
inline void splay_to_root(node *x)
{
	node *fa,*ffa;
	push_up(x);
	while(x->fa)
	{
		fa=x->fa;
		if(x!=fa->lson&&x!=fa->rson) break;
		ffa=fa->fa;
		/*debug<<"x="<<x-splay<<"fa="<<fa-splay<<"ffa="<<ffa-splay<<endl;
		debug_node(x);
		debug_node(fa);
		debug_node(ffa);*/
		if((!ffa)||(fa!=ffa->lson&&fa!=ffa->rson))
		{
			//debug<<"single rotate"<<endl;
			if(x==fa->lson) zig(x);
			else if(x==fa->rson) zag(x);
		}
		else if(fa==ffa->lson)
		{
			//debug<<"fa==lson"<<endl;
			zig(fa);
			fa=x->fa;
			//debug<<"fa="<<fa-splay<<endl;
			if(x==fa->lson) zig(x);
			else if(x==fa->rson) zag(x);
		}
		else if(fa==ffa->rson)
		{
			//debug<<"fa==rson"<<endl;
			zag(fa);
			//debug<<"zaged"<<endl;
			fa=x->fa;
			//debug<<"fa="<<fa-splay<<endl;
			if(x==fa->lson) zig(x);
			else if(x==fa->rson) zag(x);
		}
		//debug<<"one rep finished"<<endl;
	}
}
inline void access(node *x)
{
    node *t=NULL;
    while(x)
    {
        splay_to_root(x);
        x->rson=t;
        t=x;
        x=x->fa;
    }
}
inline void rev(node *x)
{
    access(x);
    splay_to_root(x);
    x->rev^=1;
}
inline void link(node *x,node *y)
{
    rev(x);
    x->fa=y;
    splay_to_root(x);
}
inline void cut(node *x,node *y)
{
    rev(x);
    access(y);
    splay_to_root(y);
    x->fa=NULL;
    y->lson=NULL;
}
int main()
{
    scanf("%d",&n);
    for(int i=1,tmp;i<=n;i++)
    {
        scanf("%d",&tmp);
        splay[i].fa=&splay[min(i+tmp,n+1)];
        nxt[i]=splay[i].fa;
    }
    scanf("%d",&m);
    for(int i=1,c,x,t;i<=m;i++)
    {
        scanf("%d%d",&c,&x);x++;
        if(c==1)
        {
            rev(&splay[n+1]);
            access((&splay[x]));
            //debug<<"accessed"<<endl;
            splay_to_root(&splay[x]);
            printf("%d\n",splay[x].lson->siz);
        }
        else if(c==2)
        {
            scanf("%d",&t);
            int y=min(x+t,n+1);
            cut(&splay[x],nxt[x]);
            link(&splay[x],&splay[y]);
            nxt[x]=&splay[y];
        }
    }
    return 0;
}

