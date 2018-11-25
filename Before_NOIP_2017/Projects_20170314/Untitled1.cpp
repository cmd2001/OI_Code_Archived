#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define mid ((ll+rr)>>1)
#define debug cout
using namespace std;
const int maxn=66*1e5;
int n,m;
int in[100100];
int l[maxn],r[maxn],data[maxn];
int root[maxn],cnt;
int hash[maxn],tme[maxn],ch;
struct question
{
    int l,r,n;
}que[5100];
int at;
void build(int ll,int rr,int pos,int recopos)
{
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",in+i);
    sort(in+1,in+1+n);
    for(int i=1;i<=n;i++)
    {
        if(in[i]==hash[ch]) ++tme[ch];
        else hash[++ch]=in[i],++tme[ch];
    }
    for(int i=1;i<=m;i++) scanf("%d%d%d",que[i].l,que[i].r,que[i].n);
    int maxr=hash[ch];
    build(1,maxr,0,0)
    for(int i=1;i<=maxr;i++)
    {
        at=lower_bound(hash+1,hash+1+n,i)-hash;
        if(hash[at]!=i) --at;
        build(1,maxr,root[i],0);
    }

    return 0;
}


