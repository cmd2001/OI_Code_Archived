#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mid ((ll+rr)>>1)
#define debug cout
using namespace std;
const int maxn=1e5+1e2,maxm=5*1e3+1e2;
int l[maxn*20],r[maxn*20],lson[maxn*20],rson[maxn*20],data[maxn*20],root[maxn],cnt;
int in[maxn],srt[maxn],n,m,newnum;
void prebuild(int ll,int rr,int pos)
{
	l[pos]=ll,r[pos]=rr;
	if(ll==rr) return;
	prebuild(ll,mid,lson[pos]=++cnt);
	prebuild(mid+1,rr,rson[pos]=++cnt);
}
void build(int ll,int rr,int pos,int prepos)
{
	l[pos]=ll,r[pos]=rr;
	if(ll==rr&&ll==newnum) {data[pos]=1; return;}
	if(mid<newnum) lson[pos]=lson[prepos];
	else
	{
		lson[pos]=++cnt;
		build(ll,mid,cnt,lson[prepos]);
	}
	if(mid>=newnum) rson[pos]=rson[prepos];
	else
	{
		rson[pos]=++cnt;
		build(mid+1,rr,cnt,rson[prepos]);
	}
	data[pos]=data[lson[pos]]+data[rson[pos]];
}
int query(int pos,int x,int prepos)
{
    if(l[pos]==r[pos]) return l[pos];
    const int delta=data[lson[pos]]-data[lson[prepos]];
    if(x<=delta) return query(lson[pos],x,lson[prepos]);
    else return query(rson[pos],x-delta,rson[prepos]);
}
int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",in+i),srt[i]=in[i];
	sort(srt+1,srt+1+n);
	for(int i=1;i<=n;i++) in[i]=lower_bound(srt+1,srt+1+n,in[i])-srt;
	prebuild(1,n,root[0]=++cnt);
	for(int i=1;i<=n;i++)
	{
		newnum=in[i];
		build(1,n,root[i]=++cnt,root[i-1]);
	}
	for(int i=1,s,e,x;i<=m;i++)
	{
		scanf("%d%d%d",&s,&e,&x);
		int at=query(root[e],x,root[s-1]);
		printf("%d\n",srt[at]);
	}
	//debug<<cnt<<endl;
	return 0;
}
