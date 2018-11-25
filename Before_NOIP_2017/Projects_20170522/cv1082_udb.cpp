#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+1e2;

struct node
{
    int dat;
    long long int num,sum,tag;
    node *lson,*rson,*fa;
}splay[maxn],*root,*pot[maxn];
int n,m,cnt;
inline int get_min(node *x)
{
    while(x->lson) x=x->lson;
    return x->dat;
}
inline int get_max(node *x)
{
    while(x->rson) x=x->rson;
    return x->dat;
}
inline void push_down(node *x)
{
    if(x->tag)
    {
        if(x->lson)
        {
            x->lson->tag+=x->tag;
            x->lson->num+=x->tag;
            x->lson->sum+=(x->dat-get_min(x))*x->tag;
        }
        if(x->rson)
        {
            x->rson->tag+=x->tag;
            x->rson->num+=x->tag;
            x->rson->sum+=(get_max(x)-x->dat)*x->tag;
        }
        x->tag=0;
    }
}
inline void update(node *x)
{
    x->sum=x->num;
    if(x->lson) x->sum+=x->lson->sum;
    if(x->rson) x->sum+=x->rson->sum;
}
inline void zig(node *x)
{
    node *fa=x->fa;
    push_down(fa);
    push_down(x);
    if(fa==root) root=x;
    else if(fa==fa->fa->lson) fa->fa->lson=x;
    else fa->fa->rson=x;
    x->fa=fa->fa;
    fa->lson=x->rson;
    if(x->rson) x->rson->fa=fa;
    fa->fa=x;
    x->rson=fa;
    if(x->fa) push_down(x->fa);
    push_down(x);
    push_down(fa);
    update(fa);
    update(x);
    if(x->fa) update(x->fa);
}
inline void zag(node *x)
{
    node *fa=x->fa;
    push_down(fa);
    push_down(x);
    if(fa==root) root=x;
    else if(fa==fa->fa->lson) fa->fa->lson=x;
    else fa->fa->rson=x;
    x->fa=fa->fa;
    fa->rson=x->lson;
    if(x->lson) x->lson->fa=fa;
    fa->fa=x;
    x->lson=fa;
    if(x->fa) push_down(x->fa);
    push_down(x);
    push_down(fa);
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
    scanf("%d",&n);
    root=pot[0]=&splay[++cnt];
    root->dat=root->num=root->sum=0;
    for(int i=1,tmp;i<=n;i++)
    {
        scanf("%d",&tmp);
        pot[i]=splay_insert(i,tmp);
    }
    pot[n+1]=splay_insert(n+1,0);
    scanf("%d",&m);
    for(int i=1,c,a,b,x;i<=m;i++)
    {
        scanf("%d%d%d",&c,&a,&b);
        if(c==1)
        {
            scanf("%d",&x);
            splay_to_root(pot[a-1]);
            splay_to_rson(pot[b+1]);
            root->rson->lson->tag+=x;
            root->rson->lson->num+=x;
            root->rson->lson->sum+=(b-a+1)*x;
        }
        if(c==2)
        {
            splay_to_root(pot[a-1]);
            splay_to_rson(pot[b+1]);
            push_down(root);
            push_down(root->rson);
            printf("%lld\n",root->rson->lson->sum);
        }

    }
    return 0;
}
