#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=1e4+1e2;

int s[maxn],t[maxn<<1],nxt[maxn<<1],l[maxn<<1],cnt;
int siz[maxn],dep[maxn],arr[maxn],id[maxn],sum,al,root,bkroot,miv,tar,ans,n,k,lst;
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
	//debug<<"st="<<st<<"ed="<<ed<<endl;
	int ret=0;
	
	sort(arr+st,arr+ed+1);
	
	/*debug<<"Array = "<<endl;
	for(int i=st;i<=ed;i++) debug<<arr[i]<<" ";
	debug<<endl;*/
	
	for(int i=st;i<=ed;i++)
	{
		ret+=((arr[i]<=tar)<<1);
		ret-=((arr[i]<<1)<=tar);
	}
	for(int i=st,xx;i<=ed;i++)
	{
		xx=upper_bound(arr+st,arr+ed+1,tar-arr[i])-arr;
		
		ret+=xx-st;
	}
	
	
	//debug<<"in core 2*ret="<<ret<<endl;
	ret>>=1;
	
	return ret;
	
}
		
	


inline int calc()
{
	int ret=0,minus=0;
	
	/*debug<<"before for al="<<al<<endl;
	
	for(int i=1;i<=al;i++) debug<<id[i]<<" ";
	debug<<endl;*/
	
	for(int i=1,pos;i<=al;i++)
	{
		for(pos=i;id[pos]==id[i]&&pos<=al;pos++);
		pos--;
		
		minus+=core_calc(i,pos);
		
		i=pos;
	}
	
	//debug<<"afrer for al="<<al<<endl;
	for(int i=1;i<=al;i++) ret+=(arr[i]<=tar);
	ret+=core_calc(1,al);
	
	//debug<<"ret="<<ret<<"minus="<<minus<<endl;
	
	return ret-minus;
	
}

	
inline void work(int pos)
{
	
	lst=al=0;
	dep[pos]=0;
	dfs(pos,0);
	
	//debug<<endl<<endl<<"Pos="<<pos<<endl;
	ans+=calc();
	//debug<<"Calc of "<<pos<<" Complete"<<endl<<endl<<endl;
	
	used[pos]=1;
	
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
	for(int i=0;i<=n;i++) used[i]=0;
	cnt=0;
	bkroot=root=0,miv=0x3f3f3f3f;
	ans=0;
}

int main()
{
	//freopen("dat.txt","r",stdin);
	while(scanf("%d%d",&n,&k)==2&&(n||k))
	{
		init();
		
		for(int i=1,a,b,l;i<n;i++)
		{
			scanf("%d%d%d",&a,&b,&l);
			addedge(a,b,l);
			addedge(b,a,l);
		}
		
		dfs(1,0);
		sum=siz[1];
		findrt(1,0);
		//debug<<"root="<<root<<endl;
		
		tar=k;
		
		work(root);
		
		printf("%d\n",ans);
		
	}
		
		
	
	
	
	
	
	
	
	return 0;
}
