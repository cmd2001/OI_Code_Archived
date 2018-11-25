#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e4+1e2;
bool bug;
int t,n,mod;
long long int a[5],b[5];
long long int ans;
int gcd(int a,int b)
{
	return (!(a%b))?b:gcd(b,a%b);
}
int exgcd(int a,int b,int &x,int &y)
{
    int d=a;
    if(b)
    {
        d=exgcd(b,a%b,y,x);
        y-=(a/b)*x;
    }
    else
    {
        x=1,y=0;
    }
    return d;
}
int calc(int a1,int a2,int b1,int b2)
{
	if(b1==0&&b2==0) {mod=a1*a2/gcd(a1,a2);return 0;}
	if(a1<a2){swap(a1,a2);swap(b1,b2);}
	int g=gcd(a1,a2),delta=(b2-b1);
	if(abs(delta)%g){bug=1;return 0;}
	mod=a1*a2/g;
	int y1,y2;
	exgcd(a1,a2,y1,y2);
	//debug<<"a1="<<a1<<"a2="<<a2<<"b1="<<b1<<"b2="<<b2<<endl;
	//debug<<"y1="<<y1<<"y2="<<y2<<endl;
	int ret=a1*y1*(delta/g)+b1;
	//debug<<"ret="<<ret<<endl;
	//debug<<"mod="<<mod<<endl;
	ret%=mod;
	if(ret<0) ret+=mod;
	//debug<<"ret="<<ret<<endl;
	return ret;
}
inline void init()
{
	bug=ans=n=mod=0;
	memset(a,0,sizeof(0));
	memset(b,0,sizeof(0));
}
int main()
{
	freopen("equation.in","r",stdin);
	freopen("equation.out","w",stdout);
	scanf("%d",&t);
	while(t--)
	{
		//debug<<"t="<<t<<endl;
		init();
		scanf("%d",&n);
		if(n==1)
		{
			long long int aa,bb;
			scanf("%lld%lld",&aa,&bb);
			if(!bb) printf("0\n");
			else printf("%lld\n",aa-bb);
			continue;
		}
		for(int i=1;i<=n;i++)
		{
			scanf("%lld%lld",a+i,b+i);
			if(b[i]) b[i]=a[i]-b[i];
		}
		for(int i=1;i<n&&!bug;i++)
		{
			long long int num=calc(a[i],a[i+1],b[i],b[i+1]);
			//debug<<"mod="<<mod<<"num="<<num<<endl;
			a[i+1]=mod;
			b[i+1]=num;
			ans=num;
		}
		if(bug) {printf("-1\n");continue;}
		printf("%lld\n",ans);
	}
	fclose(stdin);
	fclose(stdout);
	return 0;
}
	
