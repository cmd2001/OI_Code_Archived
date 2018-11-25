#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e4+1e2;

lli l,r,ans;
lli nums[maxn],cnt=-1;
bool vis[maxn];

inline lli gcd(lli a,lli b)
{
	while(a%b)
	{
		a%=b;
		a^=b^=a^=b;
	}
	return b;
}
inline void init(lli base)
{
	if(base>r) return;
	nums[++cnt]=base;
	init(base*10+2);
	init(base*10+9);
}
inline void uni()
{
	sort(nums+1,nums+1+cnt);
	
	for(int i=1;i<=cnt;i++)
	{
		if(!vis[i])
		{
			for(int j=i+1;j<=cnt;j++)
			{
				if(!(nums[j]%nums[i])) vis[j]=1;
			}
		}
	}
	
	lli tmp=0;
	for(int i=1;i<=cnt;i++) if(!vis[i]) nums[++tmp]=nums[i];
	cnt=tmp;
	reverse(nums+1,nums+1+cnt);
}

inline void dfs(int pos,int siz,lli val) // pos is the position of the number you will select or not.
{
	if(pos>cnt)
	{
		if(!siz) return;
		lli tmp=r/val-(l-1)/val;
		//debug<<"val="<<val<<endl;
		if(siz&1) ans+=tmp;
		else ans-=tmp;
		return;
	}
	if(val>r) return;
	
	dfs(pos+1,siz,val);
	
	lli g=gcd(val,nums[pos]);
	lli tmp=nums[pos]/g;
	if((double)val*tmp<=r) dfs(pos+1,siz+1,val*tmp);
}

int main()
{
	scanf("%lld%lld",&l,&r);
	
	init(0);
	uni();
	dfs(1,0,1);
	
	printf("%lld\n",ans);
	
	return 0;
}
	
