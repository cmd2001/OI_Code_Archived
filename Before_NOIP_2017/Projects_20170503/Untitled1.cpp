#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=2e4+1e2,maxm=1e5+1e2;
struct node
{
    int a,b,v;
    friend bool operator < (const node &a,const node &b) {return a.v<b.v;}
}edge[maxm];
int fa[maxn],rel[maxn],n,m,ans;
int findfa(int x)
{
    if(fa[x]==x) return x;
    //return fa[x]=findfa(fa[x]);
    else
    {
        int &now=rel[fa[x]];
        fa[x]=findfa(fa[x]);
        rel[x]=(rel[x]+now)%2;
        return fa[x];
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1;i<=m;i++) scanf("%d%d%d",&edge[i].a,&edge[i].b,&edge[i].v);
    sort(edge+1,edge+1+m);
    for(int i=m;i>0;i--)
    {
        const int &a=edge[i].a,&b=edge[i].b,&v=edge[i].v;
        /*debug<<"v="<<v<<endl;
        debug<<"a="<<a<<"b="<<b<<endl;*/
        if(findfa(a)==findfa(b)&&rel[a]==rel[b]) {ans=v;break;}
        else
        {
            /*debug<<"ffa="<<findfa(a)<<endl;
            debug<<"fb="<<findfa(b)<<endl;*/
            int sum=rel[a]+rel[b]+1,ffa=findfa(a);
            fa[ffa]=findfa(b);
            //debug<<"fa[ffa]="<<fa[ffa]<<endl;
            rel[ffa]=sum%2;
        }
        //for(int i=1;i<=n;i++) printf("%d\n",findfa(i));
    }

    printf("%d\n",ans);
}



