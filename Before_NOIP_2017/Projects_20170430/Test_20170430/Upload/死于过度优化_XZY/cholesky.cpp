#include<bits/stdc++.h>
#define debug cout
using namespace std;
const int maxn=3e3+1e1;
int in[maxn][maxn],ans[maxn][maxn],n;
int sum;
inline int getint()
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
	freopen("cholesky.in","r",stdin);
	freopen("cholesky.out","w",stdout);
	n=getint();
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) in[i][j]=getint();
	ans[1][1]=sqrt(in[1][1]);
	for(int i=2;i<=n;i++) ans[i][1]=in[1][i]/ans[1][1];
	for(int i=1;i<=n;i++)
	{
		for(int j=2;j<=n;j++)
		{
			if(j>i) {ans[i][j]=0;continue;}
			sum=0;
			if(i==j)//i is the x
			{
				for(int k=1;k<j;k++) sum+=ans[i][k]*ans[i][k];
				ans[i][j]=sqrt(in[i][j]-sum);
				continue;
			}
			for(int k=1;k<j;k++) sum+=ans[j][k]*ans[i][k];
			ans[i][j]=(in[i][j]-sum)/ans[j][j];
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++) printf("%d ",ans[i][j]);
		putchar('\n');
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}

