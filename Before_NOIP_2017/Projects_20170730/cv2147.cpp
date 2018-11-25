#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=5e5+1e2;

int in[maxn],srt[maxn],n,len;
bool vis[maxn];

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",in+i),srt[i]=in[i];
	
	sort(srt+1,srt+1+n);
	
	len=unique(srt+1,srt+1+n)-srt-1;
	
	for(int i=1,pos;i<=n;i++)
	{
		pos=lower_bound(srt+1,srt+1+len,in[i])-srt;
		if(vis[pos]) putchar('1');
		else putchar('0'),vis[pos]=1;
	}
	
	putchar('\n');
		
	
	return 0;
}
