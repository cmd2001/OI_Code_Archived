#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
int n;
int cnt,head[10005],point[100005],next[100005];
bool visit[10005];
int maxx[10005],shu[10005];
void add(int a,int b)
{
	cnt++;
	point[cnt]=b;
	next[cnt]=head[a];
	head[a]=cnt;
}

void dfs(int x)
{
	visit[x]=true;
	for(int i=head[x];i;i=next[i])
	{
		int temp=point[i];
		if(visit[temp]) continue;
		dfs(temp);
		shu[x]+=shu[temp];
		maxx[x]=max(maxx[x],shu[temp]);
	}
	shu[x]+=1;
	maxx[x]=max(maxx[x],n-shu[x]);
}
int main()
{
	freopen("treecut.in","r",stdin);
	freopen("treecut.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		add(a,b);
		add(b,a);
	}
	dfs(1);
	for(int i=1;i<=n;i++)
	{
		if(maxx[i]<=n/2) printf("%d\n",i);
	}
	fclose(stdin);
	fclose(stdout);
}
/*
10
1 2
2 3
3 4
4 5
6 7
7 8
8 9
9 10
3 8
*/
