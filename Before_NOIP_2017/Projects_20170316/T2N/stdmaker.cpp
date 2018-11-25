#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mid ((ll+rr)>>1)
using namespace std;
const int maxn=1e5+1e2;
int lson[maxn*20],rson[maxn*20],data[maxn*20],root[maxn],cnt;
int in[maxn],srt[maxn],n,m,newnum;
void prebuild(int ll,int rr,int pos)
{
	if(ll==rr) return;
	prebuild(ll,mid,lson[pos]=++cnt);
	prebuild(mid+1,rr,rson[pos]=++cnt);
}
void build(int ll,int rr,int pos,int prepos)
{
	if(ll==rr&&ll==newnum) {data[pos]=data[prepos]+1; return;}
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
int query(int pos,int x,int ll,int rr)
{
    if(rr<x) return data[pos];
    if(ll>=x) return 0;
    return query(lson[pos],x,ll,mid)+query(rson[pos],x,mid+1,rr);
}
int main(int argc,char *argv[])
{
	freopen(argv[1],"r",stdin);
	freopen(argv[2],"w",stdout);
    int len;
    cnt=0;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",in+i),srt[i]=in[i];
    sort(srt+1,srt+1+n);
    len=unique(srt+1,srt+1+n)-srt;
    len--;
    prebuild(1,len,root[0]=++cnt);
    for(int i=1;i<=n;i++)
    {
        newnum=lower_bound(srt+1,srt+1+len,in[i])-srt;
        build(1,len,root[i]=++cnt,root[i-1]);
    }
    for(int i=1,s,e,x,p;i<=m;i++)
    {
        scanf("%d%d%d",&s,&e,&x);
    	p=lower_bound(srt+1,srt+1+len,x)-srt;
        if(srt[p]==x) ++p;
        printf("%d\n",query(root[e],p,1,len)-query(root[s-1],p,1,len));
    }
	return 0;
}
