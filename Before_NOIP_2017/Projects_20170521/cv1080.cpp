#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=1e5+1e2;
struct node
{
    int dat,num;
    long long int sum;
    node *lson,*rson,*fa;
}splay[maxn],*root,*pot[maxn];
int n,m,cnt;

inline void update(node *x)
{
    x->sum=x->num;
    if(x->lson) x->sum+=x->lson->sum;
    if(x->rson) x->sum+=x->rson->sum;
}
inline void zig(node *x)
{
    node *fa=x->fa;
    if(fa==root) root=x;
    else if(fa==fa->fa->lson) fa->fa->lson=x;
    else fa->fa->rson=x;
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
    if(fa==root) root=x;
    else if(fa==fa->fa->lson) fa->fa->lson=x;
    else fa->fa->rson=x;
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
    while(x!=root)
    {
        node *fa=x->fa,*ffa=x->fa->fa;
        if(fa==root)
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
inline void splay_to_rson(node *x)
{
    while(x!=root->rson)
    {
        node *fa=x->fa,*ffa=x->fa->fa;
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
inline node* splay_insert(int x,int num)
{
    node *pos=root;
    while(1)
    {
        //debug<<"pos="<<pos-splay<<endl;
        if(x<=pos->dat)
        {
            if(pos->lson) pos=pos->lson;
            else
            {
                pos->lson=&splay[++cnt];
                pos->lson->dat=x;
                pos->lson->num=num;
                pos->lson->sum=num;
                pos->lson->fa=pos;
                splay_to_root(pos->lson);
                return &splay[cnt];
            }
        }
        else
        {
            if(pos->rson) pos=pos->rson;
            else
            {
                pos->rson=&splay[++cnt];
                pos->rson->dat=x;
                pos->rson->num=num;
                pos->rson->sum=num;
                pos->rson->fa=pos;
                splay_to_root(pos->rson);
                return &splay[cnt];
            }
        }
    }
}

int main()
{
    scanf("%d",&n,&m);
    root=pot[0]=&splay[++cnt];
    root->dat=root->num=root->sum=0;
    for(int i=1,tmp;i<=n;i++)
    {
        //debug<<"i="<<i<<endl;
        scanf("%d",&tmp);
        pot[i]=splay_insert(i,tmp);
        //debug<<"ret="<<pot[i]-splay<<endl;
    }
    pot[n+1]=splay_insert(n+1,0);
    scanf("%d",&m);
    for(int i=1,c,a,b;i<=m;i++)
    {
        scanf("%d%d%d",&c,&a,&b);
        if(c==1)
        {
            splay_to_root(pot[a]);
            pot[a]->num+=b;
            update(pot[a]);
        }
        if(c==2)
        {
            splay_to_root(pot[a-1]);
            //debug<<"root="<<root-splay<<endl;
            splay_to_rson(pot[b+1]);
            //debug<<"rson="<<root->rson-splay<<endl;
            printf("%lld\n",root->rson->lson->sum);
        }

    }
    return 0;
}
