#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=500100;
struct node
{
    int dat;
    node *lson,*rson,*fa;
}splay[maxn],*root;
int n,m,cnt;

inline void zig(node *x)
{
    //debug<<"zig"<<endl;
    node *fa=x->fa;
    if(fa==root) root=x;
    else if(fa==fa->fa->lson) fa->fa->lson=x;
    else fa->fa->rson=x;
    x->fa=fa->fa;
    fa->lson=x->rson;
    if(x->rson) x->rson->fa=fa;
    fa->fa=x;
    x->rson=fa;
}
inline void zag(node *x)
{
    //debug<<"zag"<<endl;
    node *fa=x->fa;
    if(fa==root) root=x;
    else if(fa==fa->fa->lson) fa->fa->lson=x;
    else fa->fa->rson=x;
    x->fa=fa->fa;
    fa->rson=x->lson;
    if(x->lson) x->lson->fa=fa;
    fa->fa=x;
    x->lson=fa;
}
inline void splay_to_root(node *x)
{
    while(x!=root)
    {
        //debug<<"x="<<x-splay<<endl;
        node *fa=x->fa;
        //debug<<"fa="<<fa-splay<<endl;
        //debug<<"root="<<root-splay<<endl;
        if(x==fa->lson) zig(x);
        else zag(x);
    }
}
inline void splay_insert(int x)
{
    node *pos=root;
    while(1)
    {
        if(x<=pos->dat)
        {
            if(pos->lson) pos=pos->lson;
            else
            {
                pos->lson=&splay[++cnt];
                pos->lson->dat=x;
                pos->lson->fa=pos;
                splay_to_root(pos->lson);
                return;
            }
        }
        else
        {
            if(pos->rson) pos=pos->rson;
            else
            {
                pos->rson=&splay[++cnt];
                pos->rson->dat=x;
                pos->rson->fa=pos;
                splay_to_root(pos->rson);
                return;
            }
        }
    }
}
inline node* splay_find(int x)
{
    node *pos=root;
    while(1)
    {
        if(x==pos->dat) return pos;
        if(x<pos->dat)
        {
            if(pos->lson) pos=pos->lson;
            else return pos;
        }
        if(x>pos->dat)
        {
            if(pos->rson) pos=pos->rson;
            else return pos;
        }
    }
}


int main()
{
    scanf("%d%d",&n,&m);
    root=&splay[++cnt];
    scanf("%d",&splay[cnt].dat);
    for(int i=1,tmp;i<n;i++)
    {
        scanf("%d",&tmp);
        splay_insert(tmp);
    }
    //debug<<"inserted"<<endl;
    for(int i=1,x;i<=m;i++)
    {
        scanf("%d",&x);
        if(splay_find(x)->dat==x) printf("1 ");
        else printf("0 ");
    }
    return 0;
}
