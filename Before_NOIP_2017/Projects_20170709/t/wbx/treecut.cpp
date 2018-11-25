#include<cstdio>
#include<algorithm>
#include<cstring>
#include<iostream>
#include<cmath>
using namespace std;
int head[10010],nxt[20010],whr[20010],size[10010],wson[10010],cnt=1,fa[10010];
void add(int a,int b)
{
	nxt[cnt]=head[a];
	whr[cnt]=b;
	head[a]=cnt;
	cnt++;
}
void dfs(int pos,int fat)
{
	int i,t;
	fa[pos]=fat;
	size[pos]=1;
	for(i=head[pos];i!=0;i=nxt[i])
	{
		t=whr[i];
		if(t!=fat)
		{
			dfs(t,pos);
			size[pos]+=size[t];
			wson[pos]=max(wson[pos],size[t]);
		}
	}
}
int main()
{
	freopen("treecut.in","r",stdin);
	freopen("treecut.out","w",stdout);
	int n,m,i,a,b;
	scanf("%d",&n);
	m=n/2;
	for(i=1;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		add(a,b); add(b,a);
	}
	dfs(1,1);
	for(i=1;i<=n;i++)
	{
		wson[i]=max(wson[i],n-size[i]);
		if(wson[i]<=m)	printf("%d\n",i);
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
