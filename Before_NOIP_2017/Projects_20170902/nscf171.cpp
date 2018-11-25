#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=110,maxp=930;

bool vis[maxn][maxp][maxp][10];
bool can[maxn][maxp][maxp][10];

int now[maxn];
int ans[maxn],solved;
int n,tar,p,d;

inline void update_diff(int len)
{
	bool flag=1;
	for(int i=len;i;i--)
		if(now[i]!=ans[i])
		{
			flag=(now[i]<ans[i]);
			break;
		}
	if(flag) for(int i=1;i<=len;i++) ans[i]=now[i];
}

inline bool dfs(int len,int sum,int sump,int abo)
{
	/*if(sum>tar||sump>p) return 0;
	if(vis[len][sum][sump][abo])
		return can[len][sum][sump][abo];
	vis[len][sum][sump][abo]=1;*/
	if(len==n)
	{
		sump+=abo;
		if(sum!=tar||sump!=p) return 0;
		solved=1;
		update_diff(len);
		return 1;
	}
	bool ret=0;
	for(int i=(len==n-1?1:0),lam;i<10;i++)
	{
		now[len+1]=i;
		lam=abo+i*d;
		ret|=dfs(len+1,sum+i,sump+lam%10,lam/10);
	}
	//return can[len][sum][sump][abo]=ret;
}


int main()
{
	memset(ans,0x3f,sizeof(ans));
	scanf("%d%d%d%d",&n,&tar,&p,&d);
	
	dfs(0,0,0,0);
	
	//debug<<"solved = "<<solved<<endl;
	if(!solved) puts("-1");
	else for(int i=n;i;i--) printf("%d",ans[i]);
	return 0;
	
	return 0;
}
