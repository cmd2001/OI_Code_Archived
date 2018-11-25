#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<set>
using namespace std;
const int maxn=1e5+1e2;

int n,x,y,h,e,i;
int now,ans;
int in[maxn];
multiset<int> s;

inline int getint()
{
	int ret=0,fix=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
		ch=getchar();
	while(ch>='0'&&ch<='9')
		ret=(ret<<3)+(ret<<1)+(ch-'0'),
		ch=getchar();
	return ret;
}

int main()
{
	n=getint(),x=getint(),y=getint(),h=getint(),e=getint(),ans=-1;
	
	for(i=1;i<=n;i++)
		in[i]=getint();
	
	for(i=1;i<=n;i++)
	{
		now+=x;
		ans=max(ans,now);
		if(ans>=e) break;
		s.insert(max(y,in[i]));
		h-=in[i];
		while(h<=0&&!s.empty())
		{
			now-=x;
			h+=*s.rbegin();
			s.erase(s.find(*s.rbegin()));
		}
		if(h<=0) break;
	}
	
	if(ans>=e) printf("YES\n%d\n",i);
	else printf("NO\n%d\n",ans);
	
	return 0;
}
			

