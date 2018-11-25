#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;

const int maxn=1e5+1e2;
const double eps=1e-8;

double in[maxn],s[maxn],a,ans;
int n,k;

int main()
{
	scanf("%d%lf",&n,&a);
	
	for(int i=1;i<=n;i++) scanf("%lf",in+i),s[i]=in[i]+s[i-1];
	
	
	for(int i=1;i<=n;i++)
	{
		ans=0,k=((double)a*i+eps);
		if(i<=500) for(int j=1;j<=k;j++) ans+=in[i]*in[j]/(double)(i-j);	
		else ans=(s[k]*in[i])/(double)(i-k/2);
		printf("%f\n",ans);
	}
	
	return 0;
}
		
	
