#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=2e5+1e2;

struct node
{
    int dat,mi,mx;
    long long int num,sum,tag;
    node *lson,*rson,*fa;
}splay[maxn],*root,*pot[maxn];
int n,m,cnt;
inline void update_m(node *x)
{
    x->mi=x->mx=x->dat;
    if(x->lson) x->mi=x->lson->mi;
    if(x->rson) x->mx=x->rson->mx;
}
inline void push_down(node *x)
{
    update_m(x);
    //debug<<"pushing"<<x-splay<<endl;
    if(x->tag)
    {
        if(x->lson)
        {
            x->lson->tag+=x->tag;
            x->lson->num+=x->tag;
            x->lson->sum+=(x->dat-x->mi)*x->tag;
        }
        if(x->rson)
        {
            x->rson->tag+=x->tag;
            x->rson->num+=x->tag;
            x->rson->sum+=(x->mx-x->dat)*x->tag;
        }
        x->tag=0;
    }
}
inline void update(node *x)
{
    update_m(x);
    x->sum=x->num;
    if(x->lson) x->sum+=x->lson->sum;
    if(x->rson) x->sum+=x->rson->sum;
}
inline void zig(node *x)
{
    //debug<<"x="<<x-splay<<"fa="<<x->fa-splay<<endl;
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
    //debug<<"x="<<x-splay<<"fa="<<x->fa-splay<<endl;
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
            //push_down(fa);
            //push_down(x);
            if(x==fa->lson) zig(x);
            else zag(x);
        }
        else if(fa==ffa->lson)
        {
            //if(ffa->fa) push_down(ffa->fa);
            //push_down(ffa);
            //push_down(fa);
            zig(fa);
            fa=x->fa;
            //push_down(x);
            if(x==fa->lson) zig(x);
            else zag(x);
        }
        else if(fa==ffa->rson)
        {
            //if(ffa->fa) push_down(ffa->fa);
            //push_down(ffa);
            //push_down(fa);
            zag(fa);
            //push_down(x);
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
            //push_down(root);
            //push_down(fa);
            //push_down(x);
            if(x==fa->lson) zig(x);
            else zag(x);
        }
        else if(fa==ffa->lson)
        {
            //if(ffa->fa) push_down(ffa->fa);
            //push_down(ffa);
            //push_down(fa);
            zig(fa);
            fa=x->fa;
            //push_down(x);
            if(x==fa->lson) zig(x);
            else zag(x);
        }
        else if(fa==ffa->rson)
        {
            //if(ffa->fa) push_down(ffa->fa);
            //push_down(ffa);
            //push_down(fa);
            zag(fa);
            //push_down(x);
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
            pos->mi=x;
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
            pos->mx=x;
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
inline void debugt(node *x)
{
    debug<<x-splay<<"{";
    if(x->lson) debugt(x->lson);
    debug<<",";
    if(x->rson) debugt(x->rson);
    debug<<"}";
}
int main()
{
    freopen("dp.in","r",stdin);
    freopen("my.txt","w",stdout);
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
            //push_down(root->rson->lson);
            /*debug<<"updated node="<<root->rson->lson-splay<<endl;
            debug<<"updated tag="<<root->rson->lson->tag<<endl;
            debugt(root);
            debug<<endl;*/
        }
        if(c==2)
        {
            splay_to_root(pot[a-1]);
            splay_to_rson(pot[b+1]);
            push_down(root);
            push_down(root->rson);
            printf("%lld\n",root->rson->lson->sum);
            /*debug<<"outputed node="<<root->rson->lson-splay<<endl;
            debugt(root);
            debug<<endl;*/
        }

    }
    return 0;
}
