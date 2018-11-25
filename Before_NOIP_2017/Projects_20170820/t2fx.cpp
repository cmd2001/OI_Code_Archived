#include<bits/stdc++.h>
using namespace std;
const int maxn=5e3+1e2;

double f[2][maxn];
int cur,n,m;
char s[maxn];

int main()
{
	//puts("Welcome To Africa!"); // What  A FUCK ? 
	
	scanf("%d%d",&n,&m);
	
	for(int i=1;i<=m+n;i++)
	{
		cur^=1;
		for(int j=0;j<=min(i,n);j++)
			if(j==0) f[cur][j]=0;
			else f[cur][j]=max(0.0,(double)(f[cur^1][j-1]+1)*j/i+(double)(f[cur^1][j]-1)*(i-j)/i);
	}
	
	sprintf(s,"%0.7lf",f[cur][n]);
	s[strlen(s)-1]=0;
	puts(s);
	
	return 0;
}
	
	
