#include<cstdio>
#define lli long long int
#define debug cout
using namespace std;

lli f,n,p;
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
	freopen("leap.in","r",stdin);
	freopen("leap.out","w",stdout);
	
	n=getint(),p=getint();
	
	//if(!p) puts("Runtime Error ?");
	if((n-1>=p&&p>=3)||p==1||(n>=5&&p<3))
	{
		puts("0");
		return 0;
	}
	
	f=1;
	for(int i=3;i<n;i++)
		f=f*i%p;
	
	f%=p;
	
	printf("%lld\n",f);
	
	fclose(stdin);
	fclose(stdout);
	
	return 0;
}
	
