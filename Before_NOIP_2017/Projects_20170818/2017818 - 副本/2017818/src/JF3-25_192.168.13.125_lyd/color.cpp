#include<stdio.h>
#include<string.h>
#define uint unsigned int
int n,c[20];
bool map[20][20],vis[20],take[20];
uint fp(int d,int p)
{
	uint ans=1;
	while(p)
	{
		if(p&1) ans*=d;
		p>>=1;
		d*=d;
	}
	return ans;
}
uint color(int s)
{
	int i;
//	printf("%d\n",s);
	memset(c,0,sizeof(c));
	memset(take,0,sizeof(take));
	for(i=0;i<n;i++)
	{
		if(!(s&(1<<i))) continue;
		memset(vis,0,sizeof(vis));
		for(int j=0;j<i;j++)
		{
			if(s&(1<<j)&&map[i][j])
			{
				vis[c[j]]=1;
			}
		}
		for(int j=1;j<=n;j++)
		{
			if(!vis[j]) {c[i]=j;take[j]=1;break;}
		}
	}
	for(int j=n;j;j--)
	{
		if(take[j]) return j;
	}
}
int main()
{
	int i,j,m;
	uint ans=0;
	char s[20];
	freopen("color.in","r",stdin);
	freopen("color.out","w",stdout);
	scanf("%d",&n);
	for(i=0;i<n;i++)
	{
		scanf("%s",s);
		for(j=0;j<n;j++)
		{
			map[i][j]=s[j]=='1'?1:0;
		}
	}
	for(i=1;i<(1<<n);i++)
	{
		ans+=fp(233,i)*color(i);
//		printf("color(%d)=%d\n",i,color(i));
	}
	printf("%u\n",ans);
	fclose(stdin);
	fclose(stdout);
	return 0;
}
/*
4
0110
1010
1101
0010
*/
