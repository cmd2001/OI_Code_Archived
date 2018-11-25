#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<math.h>
using namespace std;
int n,m,root=1,cnt=1,num[40050][3],head[40050],nxt[40050],node[40050],fa[40050],size[40050];
void add(int x,int y)
{
	nxt[cnt]=head[x];
	node[cnt]=y;
	head[x]=cnt;
	cnt++;
}
void build(int pos)
{
	for(int i=1;i<n;i++)
	{
		if(num[i][1]==pos)
		{
			if(num[i][2]!=fa[pos])
			{
				add(pos,num[i][2]);
				fa[num[i][2]]=pos;
				build(num[i][2]);
			}
		}
		if(num[i][2]==pos)
		{
			if(num[i][1]!=fa[pos])
			{
				add(pos,num[i][1]);
				fa[num[i][1]]=pos;
				build(num[i][1]);
			}
		}
	}
}
void dfs(int pos)
{
	for(int i=head[pos];i;i=nxt[i])
	{
		dfs(node[i]);
		size[pos]+=size[node[i]];
	}
	size[pos]++;
}
int main()
{
	freopen("treecut.in","r",stdin);
	freopen("treecut.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<n;i++)scanf("%d%d",&num[i][1],&num[i][2]);
	fa[1]=1;build(1);dfs(1);
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		int flag=0;
		for(int j=head[i];j;j=nxt[j])if(size[node[j]]>(n/2))flag=1;
		if(flag==0&&(n-size[i])<=(n/2))ans++,printf("%d\n",i);
	}
	if(ans==0)printf("NONE/n");
	fclose(stdin);
	fclose(stdout);
}


