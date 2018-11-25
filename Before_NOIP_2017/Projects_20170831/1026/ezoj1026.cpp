//#include<iostream>
#include<cstdio>
//#include<cstring>
//#define debug cout
#define lli long long int
using namespace std;
const int maxn=3e5+1e2;

int in[maxn],n,m,ope_st,ope_ed,t;
int f[maxn];
lli ans[5];

inline int max(int a,int b)
{
	return a>b?a:b;
}

inline void re_update(int st,int ed)
{
	for(int i=ed;i>=st;i--)
	{
		if(in[i]+i>n) f[i]=1;
		else f[i]=1+f[i+in[i]];
	}
}

inline int getint()
{
	int ret=0;
	char ch=getchar();
	while(ch<'0'||ch>'9') ch=getchar();
	while(ch>='0'&&ch<='9')
		ret=ret*10+(ch-'0'),
		ch=getchar();
	return ret;
}

int main()
{
	freopen("sheep3.in","r",stdin);
	freopen("my.txt","w",stdout);
	n=getint(),m=getint(),t=getint();
	//cerr<<"m="<<m<<"t="<<t<<endl;
	for(int i=0;i<=n;i++)
		in[i]=getint();
	re_update(0,n);
	ope_ed=-1;
	
	for(int i=1,op,a,b,c;i<=m;i++)
	{
		//cerr<<"i="<<i<<endl;
		op=getint();
		if(op==1)
		{
			a=getint(),b=getint();
			in[a]=b;
			ope_ed=max(ope_ed,a);
		}
		else if(op==2)
		{
			c=getint();
			if(c<=n)
			{
				if(c>ope_ed)
				{
					if(t==2) printf("%d\n",f[c]);
					else ans[(i&1)]^=f[c],ans[2]+=f[c];
				}
				else // c <= ope_ed
				{
					//debug<<"c = "<<c<<" ope_ed = "<<ope_ed<<endl;
					re_update(c,ope_ed);
					ope_ed=c-1;
					//debug<<"f[0] = "<<f[0]<<endl;
					if(t==2) printf("%d\n",f[c]);
					else ans[(i&1)]^=f[c],ans[2]+=f[c];
				}
			}
			else if(t==2) puts("0");
		}
	}
	
	if(t==1) printf("%lld %lld %lld\n",ans[1],ans[0],ans[2]);
	
	return 0;
}
				
