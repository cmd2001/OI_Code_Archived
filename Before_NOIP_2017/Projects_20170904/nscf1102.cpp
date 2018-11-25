#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cstdlib>
#include<map>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=55,maxm=maxn*100;

struct Node
{
	lli v;
	lli c,id;
	Node(lli vv,int cc,int iid)
	{
		v=vv,c=cc,id=iid;
	}
	Node(){}
	friend bool operator < (const Node &a,const Node &b)
	{
		return a.c<b.c;
	}
}ns[maxm];

lli n,m,k;
int cnt,pos;
lli ans;
int nxt[maxm][2];
lli f[maxm][110],from[maxm][110];
int stk[maxn],top;

map<lli,int> mp;


inline void pre()
{
	sort(ns+1,ns+1+cnt);
	for(int i=cnt,p;i>0;i--)
	{
		for(p=i;p>0&&ns[i].c==ns[p].c;p--) ;
		for(int j=i;j>p;j--)
		{
			const lli add=ns[j].v+k;
			nxt[j][0]=mp.find(add)==mp.end()?-1:mp[add];
			const lli multi=ns[j].v*k;
			nxt[j][1]=mp.find(multi)==mp.end()?-1:mp[multi];
		}
		for(int j=i;j>p;j--) mp[ns[j].v]=j;
		i=p;
	}
}

inline void update(int tarx,int tary,lli val,int fm)
{
	if(val<=f[tarx][tary]) return;
	f[tarx][tary]=val,from[tarx][tary]=fm;
}
inline void getans()
{
	memset(f,-1,sizeof(f));
	for(int i=1;i<=cnt;i++) f[i][1]=ns[i].v;
	for(int i=1;i<=cnt;i++)
	{
		if(f[i][n]!=-1&&f[i][n]>ans) ans=f[i][n],pos=i;
		for(int j=1;j<n;j++)
		{
			//debug<<"i = "<<i<<"	j = "<<j<<endl;
			if(f[i][j]==-1) break;
			if(nxt[i][0]!=-1) update(nxt[i][0],j+1,f[i][j]+ns[nxt[i][0]].v,i);
			if(nxt[i][1]!=-1) update(nxt[i][1],j+1,f[i][j]+ns[nxt[i][1]].v,i);
		}
	}
}

inline lli getint()
{
	lli ret=0,fix=1;
	char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')fix=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')
		ret=ret*10+(ch-'0'),
		ch=getchar();
	return ret*fix;
}

inline void getin()
{
	static lli a,b,c;
	n=getint(),m=getint(),k=getint();
	
	for(int i=1;i<=m;i++)
	{
		a=getint(),b=getint(),c=getint();
		for(lli j=a;j<=b;j++) ns[++cnt]=Node(j,c,i);
	}
}

int main()
{
	getin();
	
	ans=-1;
	
	pre();
	getans();
	
	if(ans==-1) return puts("NO");
	
	puts("YES");
	for(int i=n;i;i--)
	{
		stk[++top]=pos;
		pos=from[pos][i];
	}
	for(int i=top;i;i--) printf("%d %lld\n",ns[stk[i]].id,ns[stk[i]].v);
	
	return 0;
}

