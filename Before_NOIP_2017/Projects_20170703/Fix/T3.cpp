#include<bits/stdc++.h>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=5e5+1e2;

int in[maxn],tp[maxn],dst[maxn];
int t,m,n,ans=1;
lli k;

inline bool cmp(int a,int b)
{
	return in[a]<in[b];
}
inline int getint()
{
	int ret=0,fix=1;
	char ch=getchar();
	while(ch<'0'||ch>'9') {if(ch=='-') fix=-1; ch=getchar();}
	while(ch>='0'&&ch<='9')
	{
		ret=(ret<<3)+(ret<<1)+ch-'0';
		ch=getchar();
	}
	return ret*fix;
}
inline void merge(int *a,int *b,int *dst,int alen,int blen)
{
	/*debug<<"a="<<a-tp<<"b="<<b-tp<<endl;
	debug<<alen<<"	"<<blen<<endl;*/
	int la=0,lb=0,ld=0;
	while(la<alen&&lb<blen)
	{
		//debug<<"la="<<la<<"in array a="<<a[la]<<"lb="<<lb<<"in array b="<<b[lb]<<endl;
		if(cmp(a[la],b[lb])) dst[ld++]=a[la++];
		else dst[ld++]=b[lb++];
	}
	while(la<alen) dst[ld++]=a[la++];
	while(lb<blen) dst[ld++]=b[lb++];
	/*debug<<"dst="<<endl;
	for(int i=0;i<ld;i++) debug<<dst[i]<<" ";
	debug<<endl;*/
}	
inline lli calc(int last,int t) // calcing using c [1..t],last means the orginal array's position
{
	/*debug<<"now in calc"<<endl;
	debug<<"last="<<last<<endl;*/
	lli ret=0;
	for(int st=1,ed=t,tme=1;st<ed&&tme<=m;st++,ed--)
	{
		//debug<<"in for ~~~~~~~~~~~~~~~~~~~~~~~"<<endl;
		while(st<=t&&tp[st]>=last) st++;
		while(ed&&tp[ed]>=last) ed--;
		//debug<<"st="<<st<<"ed="<<ed<<endl;
		if(st<ed) ret+=((lli)in[tp[st]]-in[tp[ed]])*((lli)in[tp[st]]-in[tp[ed]]),tme++;
		if(ret>k) break;
	}
	//debug<<"ret="<<ret<<endl;
	//debug<<"exiting calc"<<endl;
	return ret;
}
int update(int last)
{
	//memset(tp,0,sizeof(tp));
	//don't memset tp!!! Fuck you!!! 
	tp[1]=last;
	int p=1,q=1,l=1,r=2;
	for(;last+l<=n;l=r,r<<=1)
	{
		//debug<<"l="<<l<<"r="<<r<<endl;
		for(int i=last+l;i<min(last+r,n+1);i++) tp[++q]=i;
		/*debug<<"inserted tp"<<endl;
		for(int i=1;i<=q;i++) debug<<tp[i]<<" ";
		debug<<endl;*/
		sort(tp+p+1,tp+q+1,cmp);
		/*for(int i=1;i<=q;i++) debug<<tp[i]<<" ";
		debug<<endl;
		debug<<"in update b="<<(tp+p+1-tp)<<endl;*/
		merge(tp+1,tp+p+1,dst,p,q-p);
		//for(int i=0;i<q;i++) debug<<dst[i]<<" ";
		memcpy(tp+1,dst,(q<<2));
		/*debug<<"q="<<q<<endl;
		debug<<"tp="<<endl;
		for(int i=1;i<=q;i++) debug<<tp[i]<<" ";
		debug<<endl;*/
		p=q;
		if(calc(last+q,q)>k) break;
	}
	if(last+l>n) return n+1;
	//debug<<"first for broken"<<endl;
	r=min(r,p);
	while(l<r)
	{
		//debug<<"l="<<l<<"	r="<<r<<endl;
		int mid=(l+r+1)>>1;
		if(calc(last+mid,p)>k) r=mid-1;
		else l=mid;
	}
	//debug<<"exiting updateing l="<<l<<endl;
	return last+l;
}
	
int main()
{
	t=getint();
	while(t--)
	{
		n=getint(),m=getint();
		scanf("%lld",&k);
		for(int i=1;i<=n;i++) *(in+i)=getint();
		int st=1,ans=0;
		while(st<=n)
		{
			//debug<<"st="<<st<<endl;
			st=update(st);
			ans++;
		}
		printf("%d\n",ans);
	}
	return 0;
}
		
		
		
		
