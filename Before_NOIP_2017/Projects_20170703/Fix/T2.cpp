#include<bits/stdc++.h>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e5+1e2;

int in[maxn],n;
lli ans;

inline int getint()
{
	int ret=0,fix=1;
	char ch=getchar();
	if(ch==EOF) exit(0);
	while(ch<'0'||ch>'9') { if(ch=='-') fix=-1; if((ch=getchar())==EOF) exit(0);}
	while(ch>='0'&&ch<='9')
	{
		ret=(ret<<3)+(ret<<1)+ch-'0';
		ch=getchar();
	}
	return ret*fix;
}
		
int main()
{
	static int t;
	while(n=getint())
	{
		t++,ans=0;
		multiset<int> h;
		for(int i=1;i<=n;i++) *(in+i)=getint();
		for(int i=1;i<=n;i++)
		{
			if(h.empty()||*h.begin()>in[i]) h.insert(in[i]);
			else
			{
				ans+=in[i]-*h.begin();
				h.erase(h.begin());
				h.insert(in[i]);
				h.insert(in[i]);
			}
		}
		printf("Case #%d: %lld\n",t,ans);
	}
	return 0;
}
				


