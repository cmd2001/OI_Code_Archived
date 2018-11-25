#include<bits/stdc++.h>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=5e4+1e2;

lli bl[maxn],col[maxn],d;
int in[maxn],m,n;

struct node
{
	int l,r,id;
	lli above,below;
	friend bool operator < (const node &a,const node &b)
	{
		return bl[a.l]==bl[b.l]?a.r<b.r:bl[a.l]<bl[b.l];
	}
}que[maxn];

bool cmp(const node &a,const node &b)
{
	return a.id<b.id;
}

lli gcd(lli x,lli y)
{
	while(x%y) x%=y,x^=y^=x^=y;
	return y;
}

inline void getblo()
{
	static int sq=sqrt(n);
	for(int i=1;i<=n;i++) bl[i]=(i-1)/sq+1;
}

inline int getint()
{
	int ret=0,fix=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') fix=-1; ch=getchar();}
	while('0'<=ch&&ch<='9')
	{
		ret=ret*10+ch-'0';
		ch=getchar();
	}
	return ret*fix;
}
inline void getin()
{
	for(int i=1;i<=n;i++) in[i]=getint();
	for(int i=1;i<=m;i++)
	{
		que[i].l=getint(),que[i].r=getint();
		que[i].id=i;
	}
}

inline void getans()
{
	lli lastl=0,lastr=0,ans=1;
	col[0]=1;
	for(int i=1;i<=m;i++)
	{
		const int &l=que[i].l,&r=que[i].r;
		//debug<<"l="<<l<<"r="<<r<<endl;
		que[i].below=(lli)(r-l)*(r-l+1);
		if(lastl<l) for(int j=lastl;j<l;j++)
		{
			ans-=((col[in[j]]<<1)-1);
			col[in[j]]--;
		}
		//debug<<"updated lastl<l ans="<<ans<<endl;
		if(lastl>l) for(int j=lastl-1;j>=l;j--)
		{
			ans+=((col[in[j]]<<1)+1);
			col[in[j]]++;
		}
		//debug<<"updated lastl>l ans="<<ans<<endl;
		if(lastr>r) for(int j=lastr;j>r;j--)
		{
			ans-=((col[in[j]]<<1)-1);
			col[in[j]]--;
		}
		//debug<<"updated lastr>r ans="<<ans<<endl;
		if(lastr<r) for(int j=lastr+1;j<=r;j++)
		{
			ans+=((col[in[j]]<<1)+1);
			col[in[j]]++;
		}
		//debug<<"updated lastr<r ans="<<ans<<endl;
		//debug<<"ans="<<ans<<endl;
		que[i].above=ans-(r-l+1);
		lastl=l,lastr=r;
	}
	
}
		
int main()
{
	n=getint(),m=getint();
	//debug<<"n="<<n<<"m="<<m<<endl;
	getin();
	getblo();
	sort(que+1,que+1+m);
	getans();
	sort(que+1,que+1+m,cmp);
	for(int i=1;i<=m;i++)
	{
		if(!que[i].above)
		{
			puts("0/1");
			continue;
		}
		d=gcd(que[i].above,que[i].below);
		printf("%lld/%lld\n",que[i].above/d,que[i].below/d);
	}
	return 0;
}
	




