#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+1e2;
int fa[maxn];
struct edge
{
	int from,to,len;
	friend bool operator < (const edge &a,const edge &b) {return a.len<b.len;}
}g[maxn];
int findfa(int x){return x==fa[x]?x:fa[x]=findfa(fa[x]);}
int m,n;
long long int ans;
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1,x,y,l;i<=m;i++) scanf("%d%d%d",&x,&y,&l),g[i].from=x,g[i].to=y,g[i].len=l;
	sort(g+1,g+1+m);
	for(int i=1;i<=m;i++) if(findfa(g[i].from)!=findfa(g[i].to)) ans+=g[i].len,fa[findfa(g[i].from)]=findfa(g[i].to);
	printf("%lld\n",ans);
	return 0;
}

