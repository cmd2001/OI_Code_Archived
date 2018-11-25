#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e6+1e2,maxp=27;

int len,ans;
int delta[maxp][maxp];
bool exi[maxp][maxp],pre[maxp][maxp];
char s[maxn];


int main()
{
	scanf("%d",&len);
	scanf("%s",s+1);
	
	for(int i=1;i<=len;i++)
	{
		const int x=s[i]-'a';
		for(int i=0;i<26;i++) if(i!=x)
		{
			delta[x][i]++;
			if(exi[x][i]) ans=max(ans,delta[x][i]);
			if(pre[x][i]) ans=max(ans,pre[x][i]-1);
			delta[i][x]--;exi[i][x]=1;
			ans=max(ans,delta[i][x]);
			if(delta[i][x]<0)
			{
				exi[i][x]=0;
				delta[i][x]=0;
				pre[i][x]=1;
			}
		}
	}
	
	printf("%d\n",ans);
	
	
	return 0;
}

