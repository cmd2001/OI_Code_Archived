#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=20;

int in[maxn],n,ans;
int tmp[maxn],tot;
int now[maxn];

inline bool judge(int* arr)
{
	bool ret=1;
	for(int i=1;i<=n;i++)
		ret&=(arr[i]==i);
		
	return ret;
}
inline void tran(int* arr,int st,int ed,int k) // transport arr[st,ed] after k ;
{
	memset(tmp,0,sizeof(tmp));
	tot=0;
	
	if(k<st)
	{
		for(int i=1;i<=k;i++) tmp[++tot]=arr[i];
		for(int i=st;i<=ed;i++) tmp[++tot]=arr[i];
		for(int i=k+1;i<st;i++) tmp[++tot]=arr[i];
		for(int i=ed+1;i<=n;i++) tmp[++tot]=arr[i];
		for(int i=1;i<=n;i++) arr[i]=tmp[i];
	}
	
	else if(k>ed)
	{
		for(int i=1;i<st;i++) tmp[++tot]=arr[i];
		for(int i=ed+1;i<=k;i++) tmp[++tot]=arr[i];
		for(int i=st;i<=ed;i++) tmp[++tot]=arr[i];
		for(int i=k+1;i<=n;i++) tmp[++tot]=arr[i];
		for(int i=1;i<=n;i++) arr[i]=tmp[i];
	}
}
inline int h(int *arr)
{
	int ret=0;
	if(arr[1]!=1) ret++;
	for(int i=1;i<n;i++)
		if(arr[i+1]!=arr[i]+1) ret++;
	return (ret+2)/3;
}

inline bool dfs(int used,int lim)
{
	if(judge(now)) return 1;
	if(h(now)+used>lim) return 0;
	
	int bak[20];
	
	for(int i=1;i<=n;i++) bak[i]=now[i];
	
	for(int l=1;l<=n;l++)
		for(int r=l;r<=n;r++)
			for(int k=0;k<=n;k++)
			{
				if(l<=k&&k<=r) continue;
				tran(now,l,r,k);
				if(dfs(used+1,lim)) return 1;
				for(int i=1;i<=n;i++) now[i]=bak[i];
			}
	return 0;
}

inline int idastar()
{
	if(judge(in)) return 0;
	for(int i=0;i<=4;i++)
	{
		for(int k=1;k<=n;k++) now[k]=in[k];
		if(dfs(0,i)) return i;
	}
	return 5;
}

int main()
{
	int t;
	
	scanf("%d",&t);
	
	while(t--)
	{
		memset(in,0,sizeof(in));
		memset(now,0,sizeof(now));
		
		scanf("%d",&n);
		
		for(int i=1;i<=n;i++) scanf("%d",in+i);
		
		ans=idastar();
		
		if(ans==5) puts("5 or more");
		else printf("%d\n",ans);
		
	}
	
	return 0;
}
		


