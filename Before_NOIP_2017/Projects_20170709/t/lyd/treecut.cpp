#include<stdio.h>
#include<string.h>
#define max(a,b) a>b?a:b
#define node p[i][0]
int maxi[10010],sum[10010],head[10010],p[20010][2],tot=1;
bool vis[10010],ans=0;
void add(int a,int b)
{
	p[tot][0]=b;
	p[tot][1]=head[a];
	head[a]=tot++;
	return;
}
int dfs(int on)
{
	int i,j,num;
	vis[on]=1;
	for(i=head[on];i;i=p[i][1])
	{
		if(vis[node]) continue;
		num=dfs(node);
		maxi[on]=max(maxi[on],num);
		sum[on]+=num;
	}
	return ++sum[on];
}
int main()
{
	int i,j,n,m,x,y,temp;
	freopen("treecut.in","r",stdin);
	freopen("treecut.out","w",stdout);
	memset(maxi,0,sizeof(maxi));
	scanf("%d",&n);
	for(i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add(x,y);
		add(y,x);
	}
	dfs(1);
	for(i=1;i<=n;i++)
	{
		temp=max(maxi[i],n-sum[i]);
		if(temp<=n/2)
		{
			ans=1;
			printf("%d\n",i);
		}
	}
	if(!ans) printf("NONE\n");
	fclose(stdin);
	fclose(stdout);
	return 0;
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
