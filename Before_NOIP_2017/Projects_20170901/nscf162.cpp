#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1e3+1e2,maxl=27;

struct node
{
	char str[maxn];
	int len;
	
	void in()
	{
		scanf("%s",str);
		len=strlen(str);
	}
	char& operator [] (const int &p)
	{
		return str[p-1];
	}
}in[maxn];

int n;

inline bool judge(int pos,int len)
{
	static bool flag;
	for(int i=1;i<=n;i++) if(i!=pos)
	{
		flag=1;
		for(int j=1;j<=len&&flag;j++)
			if(in[i][j]!=in[pos][j]) flag=0;
		if(flag) return 0;
	}
	return 1;
}
int main()
{
	freopen("zwe19.in","r",stdin);
	scanf("%d",&n);
	
	for(int i=1;i<=n;i++)
		in[i].in();
	
	for(int i=1;i<=n;i++)
	{
		int ll=0,rr=in[i].len,mid;
		while(rr>ll+1)
		{
			mid=((ll+rr)>>1);
			if(judge(i,mid)) rr=mid;
			else ll=mid;
			
		}
		for(int j=1;j<=rr;j++) putchar(in[i][j]);
		putchar('\n');
	}
	
	return 0;
}
	
