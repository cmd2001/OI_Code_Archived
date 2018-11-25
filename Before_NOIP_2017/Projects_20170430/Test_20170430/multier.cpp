#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=5e2;
int in[maxn][maxn],n;
int ans[maxn][maxn];
int getint()
{
	int ret=0,fix=1;
	char ch=getchar();
	while(ch>'9'||ch<'0') {if(ch=='-')fix=-1; ch=getchar();}
	while(ch<='9'&&ch>='0')
	{
		ret=ret*10+ch-'0';
		ch=getchar();
	}
	return ret*fix;
}
int main()
{
	n=getint();
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) in[i][j]=getint();
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) for(int k=1;k<=n;k++) ans[i][j]+=(in[i][k]*in[j][k]);
	debug<<"ans="<<endl;
	for(int i=1;i<=n;i++) {for(int j=1;j<=n;j++) printf("%d ",ans[i][j]);puts("");}
	return 0;
	
}
	
