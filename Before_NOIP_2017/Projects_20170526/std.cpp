#include<iostream>
#include<cstdio>
using namespace std;
const int maxn=201000;
int n,m,x,y,op,sz[maxn],next[maxn],fa[maxn],tree[maxn][2],s[maxn];
bool rev[maxn];
inline bool isroot(int x)
{
    return tree[fa[x]][0]!=x&&tree[fa[x]][1]!=x;
}
inline void pushup(int x)
{
    sz[x]=sz[tree[x][0]]+sz[tree[x][1]]+1;
}
inline void pushdown(int x)
{
    if(rev[x])
    {
        rev[x]^=1;rev[tree[x][0]]^=1;rev[tree[x][1]]^=1;
        swap(tree[x][0],tree[x][1]);
    }
}
void rotate(int x)
{
    int y=fa[x],z=fa[y],l=tree[y][1]==x,r=l^1;
    if(!isroot(y)) tree[z][tree[z][1]==y] = x;
    fa[x]=z;fa[y]=x;fa[tree[x][r]]=y;
    tree[y][l]=tree[x][r];tree[x][r]=y;
    pushup(y);pushup(x);
}
void splay(int x)
{
    int top=0;s[++top]=x;
    for(int i=x;!isroot(i);i=fa[i])
    {
        s[++top]=fa[i];
    }
    for(int i=top;i;i--) pushdown(s[i]);
    while(!isroot(x))
    {
        int y=fa[x],z=fa[y];
        if(!isroot(y))
        {
            if(tree[y][0]==x^tree[z][0]==y) rotate(y);else rotate(x);
        }
        rotate(x);
    }
}
void access(int x)
{
    int t=0;
    while(x)
    {
        splay(x);
        tree[x][1]=t;
        t=x;x=fa[x];
    }
}
void rever(int x)
{
    access(x);splay(x),rev[x]^=1;
}
void link(int x,int y)
{
    rever(x);fa[x]=y;splay(x);
}
void cut(int x,int y)
{
    rever(x);access(y);splay(y);tree[y][0]=fa[x]=0;
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&x);
        fa[i]=x+i; sz[i]=1;
        if (fa[i]>n+1) fa[i]=n+1;
        next[i]=fa[i];
    }
    sz[n+1]=1;
    scanf("%d",&m);
    for (int i=1;i<=m;i++)
    {
        scanf("%d",&op);
        if (op==1)
        {
            rever(n+1);
            scanf("%d",&x); x++;
            access(x); splay(x); printf("%d\n",sz[tree[x][0]]);
        }
        else
        {
            scanf("%d%d",&x,&y); x++;
            int t=min(n+1,x+y);
            cut(x,next[x]); link(x,t); next[x]=t;
        }
    }
    return  0;
}
