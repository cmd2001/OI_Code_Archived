#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=1e6+1e2;
int dat[maxn],lson[maxn],rson[maxn],dis[maxn],fa[maxn];
bool vis[maxn];
int n,m;
void merge(int x,int y)
{
    if(!rson[x]) rson[x]=y;
    else if(rson[x]&&dat[rson[x]]<=dat[y]) merge(rson[x],y);
    else if(rson[x]&&dat[rson[x]]>dat[y]) {merge(y,rson[x]);rson[x]=y;}
    if(dis[rson[x]]>dis[lson[x]]) swap(lson[x],rson[x]);
    dis[x]=dis[rson[x]]+1;
    return;
}
int findfa(int x)
{
    return x==fa[x]?x:fa[x]=findfa(fa[x]);
}
int kill(int p)
{
	p=findfa(p);
    int ret=dat[p];
    vis[p]=1;
    int x=lson[p],y=rson[p];
    if(!(x|y)) return ret;
    if((!x)||(!y)) {fa[x|y]=x|y; fa[p]=x|y; return ret;}
    if(dat[x]>dat[y]) swap(x,y);
    fa[x]=x;
    fa[findfa(p)]=x;
    merge(x,y);
    return ret;
}
int main()
{
	dis[0]=-1;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",dat+i),fa[i]=i;
    scanf("%d",&m);
    char cmd[5];
    for(int i=1,x,y;i<=m;i++)
    {
        scanf("%s",cmd);
        if(cmd[0]=='M')
        {
            scanf("%d%d",&x,&y);
            if(vis[x]||vis[y]) continue;
            x=findfa(x),y=findfa(y);
            if(x==y) continue;
            if(dat[x]>dat[y]) swap(x,y);
            fa[y]=fa[x];
            merge(x,y);
        }
        if(cmd[0]=='K')
        {
            scanf("%d",&x);
			if(vis[x]) {printf("0\n"); continue;}
            printf("%d\n",kill(x));
        }
    }
    return 0;
}

