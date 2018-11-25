#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=100100;
int lson[maxn],rson[maxn],fa[maxn],dat[maxn],siz[maxn],num[maxn];
int root,cnt;
void zig(int x)//x is the fa;
{
    //debug<<"zig\n";
    const int gfa=fa[x],son=lson[x];
    fa[son]=gfa;
    if(gfa)
    {
        if(lson[gfa]==x) lson[gfa]=son;
        else rson[gfa]=son;
    }
    else root=son;
    lson[x]=rson[son];
    if(rson[son]) fa[rson[son]]=x;
    fa[x]=son;
    rson[son]=x;
    siz[son]=siz[x];
    siz[x]=siz[lson[x]]+siz[rson[x]]+num[x];
}
void zag(int x)
{
    //debug<<"zag\n";
    const int gfa=fa[x],son=rson[x];
    fa[son]=gfa;
    if(gfa)
    {
        if(lson[gfa]==x) lson[gfa]=son;
        else rson[gfa]=son;
    }
    else root=son;
    rson[x]=lson[son];
    if(lson[son]) fa[lson[son]]=x;
    fa[x]=son;
    lson[son]=x;
    siz[son]=siz[x];
    siz[x]=siz[lson[x]]+siz[rson[x]]+num[x];
}
void insert(int x)// lson:<=, rson:>.
{
    register int pos=root;
    while(1)
    {
        siz[pos]++;
        if(x==dat[pos])
        {
            num[pos]++;
            break;
        }
        if(x<dat[pos])
        {
            if(lson[pos]) pos=lson[pos];
            else
            {
                lson[pos]=++cnt;
                dat[cnt]=x;
                fa[cnt]=pos;
                siz[pos]=num[pos]=1;
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
                siz[pos]=num[pos]=1;
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
        //debug<<"ffa="<<ffa<<"gfa="<<gfa<<endl;
        if(gfa)
        {
                 if(x==lson[ffa]&&ffa==lson[gfa]) {zig(fa[x]);zig(fa[x]);}
            else if(x==lson[ffa]&&ffa==rson[gfa]) {zig(fa[x]);zag(fa[x]);}
            else if(x==rson[ffa]&&ffa==lson[gfa]) {zag(fa[x]);zig(fa[x]);}
            else if(x==rson[ffa]&&ffa==rson[gfa]) {zag(fa[x]);zag(fa[x]);}
        }
        else
        {
            //debug<<"ffa="<<ffa<<endl;
            if(ffa!=root){debug<<"x="<<x<<"ffa="<<ffa<<"root="<<root<<"\n"<<"!gfa&&ffa!=root"<<"\n";exit(0);}
                 if(x==lson[ffa]) zig(fa[x]);
            else if(x==rson[ffa]) zag(fa[x]);
        }
    }
}
void swapnode(int a,int b)//b take a's place
{
    swap(lson[a],lson[b]);
    swap(rson[a],rson[b]);
    if(lson[fa[a]]==a) lson[fa[a]]=b;
    else rson[fa[a]]=b;
    fa[b]=fa[a];
    siz[b]=siz[lson[b]]+siz[rson[b]]+num[b];
    const int &ffa=fa[b];
    siz[ffa]=siz[lson[ffa]]+siz[rson[ffa]]+num[ffa];
}
int sonpro(int x)
{
    x=rson[x];
    while(lson[x]) x=lson[x];
    return x;
}
int sonpre(int x)
{
    x=lson[x];
    while(rson[x]) x=rson[x];
    return x;
}
void del(int x)
{
    int pos=root;
    while(pos&&x!=dat[pos]) {siz[pos]--;pos=(x<dat[pos]?lson[pos]:rson[pos]);}
    if(num[pos]>1) {siz[pos]--,num[pos]--;return;}
    x=pos;
    int *to;
    if(fa[x]) to=(lson[fa[x]]==x?&lson[fa[x]]:&rson[fa[x]]);
    else to=&root;
    siz[pos]--;
    if((!lson[x])&&(!rson[x])) {*to=0;return;}
    if((!lson[x])||(!rson[x])) {*to=lson[x]|rson[x],fa[lson[x]|rson[x]]=fa[x];return;}
    else
    {
        int pro=sonpre(x);
        swapnode(x,pro);
        if(lson[fa[pro]]=pro) lson[fa[pro]]=0;
        else rson[fa[pro]]=0;
        splay(pro);
    }
}
int kth(int x)
{
    int pos=root;
    while(x!=siz[lson[pos]]+1)
    {
        if(x<=siz[lson[pos]]) pos=lson[pos];
        else x-=siz[lson[pos]],pos=rson[pos];
    }
    return dat[pos];
}
int getpos(int x)
{
    int ret=1,pos=query(x);
    while(pos)
    {
        if(pos==rson[fa[pos]]) ret+=siz[lson[fa[pos]]];
        pos=fa[pos];
    }
    return ret;
}
int getpro(int x)
{
    x=query(x);
    if(rson[x]) return dat[sonpro(x)];
    if(x==lson[fa[x]]) return dat[fa[x]];
}
int getpre(int x)
{
    x=query(x);
    if(lson[x]) return dat[sonpre(x)];
    if(x==rson[dat[x]]) return dat[fa[x]];
}
int main()
{
    int n;
    scanf("%d",&n);
    int x,q;
    while(q!=1) n--,scanf("%d%d",&q,&x);
    root=++cnt;
    dat[cnt]=x;
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",&q,&x);
        if(q==1) insert(x);
        else if(q==2) del(x);
        else if(q==3)
        {
            printf("%d\n",getpos(x));
            splay(query(x));
        }
        else if(q==4) printf("%d\n",kth(x));
        else if(q==5) printf("%d\n",getpre(x));
        else if(q==6) printf("%d\n",getpro(x));
    }
    return 0;
}


