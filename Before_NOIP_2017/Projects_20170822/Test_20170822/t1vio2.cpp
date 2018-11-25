#include<bits/stdc++.h>
#define lli long long int
#define debug cout
using namespace std;

lli f[2],n,p,ans;
int cur;

inline lli getint()
{
	lli ret=0,fix=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') fix=-1; ch=getchar();}
	while(ch>='0'&&ch<='9')
		ret=ret*10+(ch-'0'),
		ch=getchar();
	return ret*fix;
}

int main()
{
	n=getint(),p=getint();
	
	f[cur]=1;
	
	for(lli i=1;i<n-1;i++)
	{
		cur^=1,
		f[cur]=f[cur^1]*(n-i)%p;
		//debug<<"sum["<<i+1<<"]="<<f[cur]<<endl;
	}
	
	ans=(f[cur]-f[cur^1])%p;
	ans+=ans<0?p:0;
	
	printf("%lld\n",ans);
	
	return 0;
}
	
