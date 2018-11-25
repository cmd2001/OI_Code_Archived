#include<bits/stdc++.h>
#define mat vector<vector<int> >
#define ll long long
using namespace std;
ll mod,n,m;
mat mul(mat &a,mat &b)
{
	mat c(a.size(),vector<int>(b[0].size()));
	for(int i=0;i<a.size();i++)
	for(int k=0;k<b.size();k++)
	{
		if(a[i][k]!=0)
		{
			for(int j=0;j<b[0].size();j++)
			{
				c[i][j]=(c[i][j]+a[i][k]*b[k][j])%mod;
			}	
		}
	}
	return c;
}
mat pow(mat a,ll tmp)
{
	mat b(a.size(),vector<int>(a.size()));
	for(int i=0;i<a.size();i++)
		b[i][i]=1;
	while(tmp>0)
	{
		if(tmp&1)
			b=mul(b,a);
		a=mul(a,a);
		tmp>>=1;
	}
	return b;
}
int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	scanf("%d%d",&n,&mod);
	mat b(6,vector<int>(6));
	b[0][0]=1;b[0][1]=1;b[0][2]=1;b[0][3]=1;b[0][4]=1;b[0][5]=0;
	b[1][0]=1;b[1][1]=0;b[1][2]=1;b[1][3]=0;b[1][4]=0;b[1][5]=0;
	b[2][0]=1;b[2][1]=1;b[2][2]=0;b[2][3]=0;b[2][4]=0;b[2][5]=0;
	b[3][0]=1;b[3][1]=0;b[3][2]=0;b[3][3]=0;b[3][4]=0;b[3][5]=1;
	b[4][0]=1;b[4][1]=0;b[4][2]=0;b[4][3]=0;b[4][4]=0;b[4][5]=0;
	b[5][0]=0;b[5][1]=0;b[5][2]=0;b[5][3]=1;b[5][4]=0;b[5][5]=0;
	printf("%d\n",pow(b,n)[0][0]);
	return 0;
}
