#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=1e6+1e2;
int lson[maxn],rson[maxn],fa[maxn],dat[maxn];
int cnt;
int findroot(int x)
{
	while(fa[x]) x=fa[x];
	return x;
}
void zig(int x)//x is the fa;
{
    const int gfa=fa[x],son=lson[x];
    fa[son]=gfa;
    if(gfa)
    {
        if(lson[gfa]==x) lson[gfa]=son;
        else rson[gfa]=son;
    }
    lson[x]=rson[son];
    if(rson[son]) fa[rson[son]]=x;
    fa[x]=son;
    rson[son]=x;
}
void zag(int x)
{
    const int gfa=fa[x],son=rson[x];
    fa[son]=gfa;
    if(gfa)
    {
        if(lson[gfa]==x) lson[gfa]=son;
        else rson[gfa]=son;
    }
    rson[x]=lson[son];
    if(lson[son]) fa[lson[son]]=x;
    fa[x]=son;
    lson[son]=x;
}
void insert(int x)// lson:<=, rson:>.
{
    register int pos=root;
    while(1)
    {
        if(x<=dat[pos])
        {
            if(lson[pos]) pos=lson[pos];
            else
            {
                lson[pos]=++cnt;
                dat[cnt]=x;
                fa[cnt]=pos;
                break;
            }
        }
        else
        {
            if(rson[pos]) pos=rson[pos];
            else
            {
                rson[pos]=++cnt;
                dat[cnt]=x;
                fa[cnt]=pos;
                break;
            }
        }
    }
}
int query(int x)//find a node whose dat == x, return a number of the pos, 0 means not found.
{
    register int pos=root;
    while(pos&&x!=dat[pos]) pos=(x<dat[pos]?lson[pos]:rson[pos]);
    return pos;
}
void splay(int x)
{
    if(x==root) return;
    int ffa,gfa;
    while(x!=root)
    {
        ffa=fa[x],gfa=fa[fa[x]];
        if(gfa)
        {
                 if(x==lson[ffa]&&ffa==lson[gfa]) {zig(fa[x]);zig(fa[x]);}
            else if(x==lson[ffa]&&ffa==rson[gfa]) {zig(fa[x]);zag(fa[x]);}
            else if(x==rson[ffa]&&ffa==lson[gfa]) {zag(fa[x]);zig(fa[x]);}
            else if(x==rson[ffa]&&ffa==rson[gfa]) {zag(fa[x]);zag(fa[x]);}
        }
        else
        {
            if(ffa!=root){debug<<"x="<<x<<"ffa="<<ffa<<"root="<<root<<"\n"<<"!gfa&&ffa!=root"<<"\n";exit(0);}
                 if(x==lson[ffa]) zig(fa[x]);
            else if(x==rson[ffa]) zag(fa[x]);
        }
    }
}
int getmax(int pos)//return the number of the pos
{
	while(rson[pos]) pos=rson[pos];
	return pos;
}
int getmin(int pos)
{
	while(lson[pos]) pos=lson[pos];
	return pos;
}
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    {
        cnt=1;
        scanf("%d",&dat[cnt]);
        root=1;
    }
    for(int i=1,x;i<n;i++)
    {
        scanf("%d",&x);
        insert(x);
    }
    for(int i=1,x,q;i<=m;i++)
    {
        scanf("%d",&x);
        q=query(x);
        printf("%d ",(bool)q);
        if(q) splay(q);
    }
    return 0;
}

