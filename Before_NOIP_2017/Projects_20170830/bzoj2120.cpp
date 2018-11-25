#include<cstdio>
using namespace std;
const int maxn=1e6+1e2;

int in[maxn],srt[maxn],lst[maxn],n,M,top;
char c[100];

inline int getint()
{
	int ret=0,fix=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-')fix=-1; ch=getchar();}
	while(ch>='0'&&ch<='9')
		ret=ret*10+(ch-'0'),
		ch=getchar();
	return ret*fix;
}

int main()
{
	n=getint(),M=getint();
	for(int i=1,x;i<=n;i++)
	{
		x=getint();
		in[i]=srt[x]?srt[x]:srt[x]=++top;
	}
	register int x,y,ans;
	for(register int m=1;m<=M;m++)
	{
		scanf("%s",c);
		x=getint(),y=getint();
		
		if(*c=='Q')
		{
			ans=0;
			for(int i=x;i<=y;i++) if(lst[in[i]]!=m) lst[in[i]]=m,ans++;
			printf("%d\n",ans);
		}
		else
		{
			in[x]=srt[y]?srt[y]:srt[y]=++top;
		}
	}
	
	return 0;
}
		
