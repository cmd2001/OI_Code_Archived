#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=5e2+1e2;

double f[maxn][maxn],ans;
int cur=0;
char str[maxn];

int r,b;

double getb(int i,int j)
{
	return r+b+1-i-j;
}

int main()
{
	scanf("%d%d",&r,&b);
	
	f[0][0]=1;
	
	for(int i=0;i<=r;i++)
		for(int j=0;j<=b;j++)
		{
			if(i==0&&j==0) continue;
			if(i-1>=0) f[i][j]+=f[i-1][j]*((double)r-i+1)/getb(i,j);
			if(j-1>=0&&i!=r) f[i][j]+=f[i][j-1]*((double)b-j+1)/getb(i,j);
			if(i==r&&i-j>=0) ans+=f[i][j]*(i-j);
		}
		
	sprintf(str,"%0.7lf",ans);
	str[strlen(str)-1]=0;
	puts(str);
	
	return 0;
}
