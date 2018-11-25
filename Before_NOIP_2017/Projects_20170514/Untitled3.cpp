#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define debug cout
using namespace std;
const int maxn=1e5+1e2,maxl=20;

int val[maxn],s[maxn],t[2*maxn],nxt[2*maxn],fa[maxn],siz[maxn],dep[maxn],sondep[maxn],dp[maxn],tab[maxn][maxl],fatab[maxn][maxl],root,cnt,m,n,ans;
bool vis[maxn];

inline void addedge(int from,int to)
{
	t[++cnt]=to,
	nxt[cnt]=s[from],
	s[from]=cnt;
}

void dfs(int pos)
{
	sondep[pos]=dep[pos]=dep[fa[pos]]+1;
	siz[pos]=1;
	tab[pos][0]=val[fa[pos]];
	int at=s[pos];
	while(at)
	{
		if(vis[t[at]])
		{
			at=nxt[at];
			continue;
		}
		vis[t[at]]=1;
		fatab[t[at]][0]=fa[t[at]]=pos;
		dfs(t[at]);
		siz[pos]+=siz[t[at]];
		sondep[pos]=max(sondep[pos],sondep[t[at]]);
		at=nxt[at];
	}
}

int dfs1(int pos)
{
	int sona=0,mxd=dep[pos],med=0,at=s[pos];
	while(at)
	{
		if(vis[t[at]])
		{
			at=nxt[at];
			continue;
		}
		vis[t[at]]=1;
		sona=max(sona,dfs1(t[at]));
		if(sondep[t[at]]>mxd) med=mxd,mxd=sondep[t[at]];
		else if(sondep[t[at]]>med) med=sondep[t[at]];
		at=nxt[at];
	}
	if(med) return max(sona,max(med+mxd-2*dep[pos],med-dep[pos]));
	else return max(sona,mxd-dep[pos]);
}
int dfs2(int pos)
{
	int sona=0x3fffffff,ret=abs(siz[root]-siz[pos]),at=s[pos];
	while(at)
	{
		if(vis[t[at]])
		{
			at=nxt[at];
			continue;
		}
		vis[t[at]]=1;
		sona=min(sona,dfs2(t[at]));
		ret=max(ret,siz[t[at]]);
		at=nxt[at];
	}
	return min(sona,ret);
}

inline void pre()
{
	for(int j=1;(1<<j)<=n;j++)
	{
		for(int i=1;i<=n;i++)
		{
			fatab[i][j]=fatab[fatab[i][j-1]][j-1];
			tab[i][j]=max(tab[i][j-1],tab[fatab[i][j-1]][j-1]);
		}
	}
}
inline int query(int a,int b)
{
	int i,j,ret=max(val[a],val[b]);
	if(dep[a]<dep[b]) swap(a,b);
	for(i=0;(1<<i)<=dep[a];i++);
	i--;
	for(int j=i;j>=0;j--)
	{
		if(dep[a]-(1<<j)>=dep[b])
		{
			ret=max(ret,tab[a][j]);
			a=fatab[a][j];
		}
	}
	if(a==b) return ret;
	for(j=i;j>=0;j--)
	{
		if(fatab[a][j]&&fatab[a][j]!=fatab[b][j])
		{
			ret=max(ret,tab[a][j]);
			a=fatab[a][j];
			ret=max(ret,tab[b][j]);
			b=fatab[b][j];
		}
	}
	return max(ret,tab[a][0]);
}
	
	
int main()
{
	//freopen("t3.in","r",stdin);
	//freopen("my.out","w",stdout);
	scanf("%d%d",&n,&m);
	root=1,dep[1]=1;
	for(int i=1;i<=n;i++) scanf("%d",&val[i]);
	for(int i=1,a,b;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		//if(a==292||b==292) debug<<"now at 292"<<endl;
		addedge(a,b);
		addedge(b,a);
	}
	memset(vis,0,sizeof(vis));vis[1]=1;
	dfs(1);
	memset(vis,0,sizeof(vis));vis[1]=1;
	printf("%d\n",dfs1(root));
	memset(vis,0,sizeof(vis));vis[1]=1;
	printf("%d\n",dfs2(root));
	pre();
	for(int i=1,a,b;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		debug<<query(a,b)<<endl;
	}
	fclose(stdout);
	return 0;
}

