#include<iostream>
#include<cstdio>
#include<cstring>
#define ll long long
using namespace std;

ll n,m,a[5][5],mid[5][5],ans[5][5],fir[5],aaa[5];

void ksm(int x)
{
	for(int i=1;i<=4;++i)ans[i][i]=1;
	while(x)
	{
		if(x&1){
			for(int i=1;i<=4;++i)
				for(int j=1;j<=4;++j)
					for(int k=1;k<=4;++k)
						(mid[i][j]+=a[i][k]*ans[k][j]+m)%=m;
			for(int i=1;i<=4;++i)
				for(int j=1;j<=4;++j)
					ans[i][j]=mid[i][j],mid[i][j]=0;
		}
		for(int i=1;i<=4;++i)
			for(int j=1;j<=4;++j)
				for(int k=1;k<=4;++k)
					(mid[i][j]+=a[i][k]*a[k][j]+m)%=m;
		for(int i=1;i<=4;++i)
			for(int j=1;j<=4;++j)
				a[i][j]=mid[i][j],mid[i][j]=0;
		x/=2;
	}
	for(int i=1;i<=4;++i)
		for(int j=1;j<=4;++j)
			(aaa[i]+=ans[i][j]*fir[j]+m)%=m;
}

int main()
{
	freopen("count.in","r",stdin);
	freopen("count.out","w",stdout);
	while(scanf("%lld%lld",&n,&m)!=EOF&&(n||m))
	{
		memset(a,0,sizeof(a));
		memset(aaa,0,sizeof(aaa));
		memset(ans,0,sizeof(ans));
		a[1][1]=1;a[1][2]=5;a[1][3]=1;a[1][4]=-1;
		a[2][1]=1;a[3][2]=1;a[4][3]=1;
		fir[1]=36;fir[2]=11;fir[3]=5;fir[4]=1;
		if(n>=1){
			ksm(n-1);
			printf("%lld\n",aaa[4]);
		}else printf("%lld\n",fir[4-n+1]);
	}
	return 0;
}
