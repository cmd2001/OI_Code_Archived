#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e4+1e2;

int s[maxn],t[maxn<<1],nxt[maxn<<1],l[maxn<<1],cnt;
int siz[maxn],dep[maxn],arr[maxn],id[maxn],sum,al,root,bkroot,miv,tar,ans,n,lst;
bool used[maxn];

inline void addedge(int from,int to,int len)
{
	t[++cnt]=to;
	l[cnt]=len;
	nxt[cnt]=s[from];
	s[from]=cnt;
}

inline void dfs(int pos,int fa)
{
	//debug<<"pos="<<pos<<"fa="<<fa<<endl;
	siz[pos]=1;
	int at=s[pos];
	while(at)
	{
		if(t[at]!=fa&&!used[t[at]])
		{
			arr[++al]=dep[t[at]]=dep[pos]+l[at];
			id[al]=0;
			dfs(t[at],pos);
			siz[pos]+=siz[t[at]];
		}
		at=nxt[at];
	}
	if(fa==root)
	{
		for(int k=al;k>lst;k--) id[k]=pos;
		lst=al;
	}
}

inline void findrt(int pos,int fa)
{
	//debug<<"pos="<<pos<<"fa="<<fa<<endl;
	int val=sum-siz[pos];
	int at=s[pos];
	while(at)
	{
		if(t[at]!=fa&&!used[t[at]])
		{
			findrt(t[at],pos);
			val=max(val,siz[t[at]]);
		}
		at=nxt[at];
	}
	//debug<<"pos="<<pos<<"val="<<val<<endl;
	if(val<miv) miv=val,root=pos;
}
inline int core_calc(int st,int ed)
{
	int ret=0,ll=st,lim=ed,k;
	sort(arr+st,arr+ed+1);
	for(st;st<=lim;st++)
	{
		while(arr[st]+arr[ed]>tar) ed--;
		for(k=ed;arr[st]+arr[k]==tar&&k>=ll;k--) ++ret;
	}
	return ret;
}
	

inline bool calc()
{
	int ret=0,minus=0;
	for(int i=1,pos;i<=al;i++)
	{
		for(pos=i;id[pos]==id[i];pos++);
		pos--;
		minus+=core_calc(i,pos);
		i=pos+1;
	}
	
	for(int i=1;i<=al;i++) if(arr[i]==tar) return ans=1;
	
	ret=core_calc(1,al);
	
	if(ret-minus>0) return ans=1;
	
	return 0;
}
	
	
inline void work(int pos)
{
	//debug<<"pos="<<pos<<endl;
	if(ans) return;
	
	lst=al=0;
	dep[pos]=0;
	dfs(pos,0);
	//debug<<"al="<<al<<endl;
	used[pos]=1;
	if(calc()) return;
	
	int at=s[pos];
	while(at)
	{
		if(!used[t[at]])
		{
			sum=siz[t[at]];
			root=0,miv=0x3f3f3f3f;
			findrt(t[at],0);
			work(root);
		}
		at=nxt[at];
	}
}

inline void init()
{
	for(int i=0;i<=n;i++) s[i]=0;
	//memset(t,0,sizeof(t));
	//memset(l,0,sizeof(l));
	//memset(nxt,0,sizeof(nxt));
	//memset(dep,0,sizeof(dep));
	//memset(siz,0,sizeof(siz));
	//memset(arr,0,sizeof(arr));
	for(int i=0;i<=n;i++) used[i]=0;
	cnt=0;
	bkroot=root=0,miv=0x3f3f3f3f;
}

int main()
{
	//freopen("2114big.txt","r",stdin);
	//freopen("my.txt","w",stdout);
	
	while(scanf("%d",&n)==1&&n)
	{
		init();
		for(int i=1,d,c;i<=n;i++)
		{
			while(scanf("%d",&d)==1&&d)
			{
				scanf("%d",&c);
				addedge(i,d,c);
				addedge(d,i,c);
			}
		}
		
		dfs(1,0);
		sum=siz[1];
		findrt(1,0);
		bkroot=root;
		
		static int q;
		while(scanf("%d",&q)==1&&q)
		{
			tar=q,ans=0;
			for(int i=0;i<=n;i++) used[i]=0;
			work(root=bkroot);
			if(ans) puts("AYE");
			else puts("NAY");
		}
		
		puts(".");
	}
	
	fclose(stdout);
	return 0;
}
