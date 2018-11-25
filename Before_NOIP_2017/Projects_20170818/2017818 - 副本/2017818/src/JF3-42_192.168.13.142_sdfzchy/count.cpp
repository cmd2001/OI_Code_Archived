#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long LL;
LL mod,n;
struct Matrix
{
	LL a[6][6];
	Matrix() {memset(a,0,sizeof(a));}
	Matrix operator *(const Matrix& b)const
	{
		Matrix ret;
		for(int i=0;i<=5;i++)
			for(int j=0;j<=5;j++)
				for(int k=0;k<=5;k++)
					ret.a[i][j]=(ret.a[i][j]+a[i][k]*b.a[k][j])%mod;
		return ret;			
	}
};

Matrix ksm(Matrix x,LL b)
{
	b--;
	Matrix ret=x,tmp=x;
	for(;b;b>>=1,tmp=tmp*tmp)
		if(b&1) ret=ret*tmp;
	return ret;
}

int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	while(~scanf("%lld%lld",&n,&mod)&&(n||mod))
	{
		Matrix e;
		for(int i=0;i<=4;i++) e.a[i][0]=1ll;
		Matrix ans,ret;
		ans.a[0][4]=1ll;
		ans.a[1][3]=ans.a[1][4]=1ll;
		ans.a[2][4]=ans.a[2][5]=1ll;
		ans.a[3][1]=ans.a[3][4]=1ll;
		for(int i=0;i<=4;i++) ans.a[4][i]=1ll;
		ans.a[5][2]=1ll;
		ret=ksm(ans,n-1ll);
		e=ans*e;
		printf("%lld\n",e.a[4][0]%mod);
	}
	return 0;
}

