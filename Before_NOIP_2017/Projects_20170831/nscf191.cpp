#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=5e4+1e2;

struct node
{
	int st,ed,id;
	friend bool operator < (const node &a,const node &b)
	{
		return a.st!=b.st?a.st<b.st:a.ed<b.ed;
	}
}ns[maxn],x;
int id[maxn],n,ans,used,lst,nxt;
int out[maxn];

inline int getint()
{
	int ret=0,fix=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-')fix=-1; ch=getchar();}
	while(ch>='0'&&ch<='9')
		ret=ret*10+(ch-'0'),
		ch=getchar();
	return ret*fix;
}

int main()
{
	x.ed=0x3f3f3f3f;
	n=getint();
	for(int i=1;i<=n;i++)
		ns[i].st=getint(),ns[i].ed=getint(),ns[i].id=i;
	
	sort(ns+1,ns+1+n);
	
	while(used!=n)
	{
		ans++,lst=0;
		for(int i=1;i<=n;)
		{
			if(!id[i])
			{
				used++;
				id[i]=ans;
				lst=ns[i].ed;
				x.st=lst;
				nxt=upper_bound(ns+1,ns+1+n,x)-ns;
				//debug<<"lst = "<<lst<<"nxt.st = "<<ns[nxt].st<<endl;
				//debug<<"nxt.id="<<ns[nxt].id<<endl;
				i=nxt;
			}
			else i++;
		}
	}
	for(int i=1;i<=n;i++) out[ns[i].id]=id[i];
	printf("%d\n",ans);
	for(int i=1;i<=n;i++)
		printf("%d\n",out[i]);
	
	return 0;
}
	
