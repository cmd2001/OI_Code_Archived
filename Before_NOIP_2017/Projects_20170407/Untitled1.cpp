#include<bits/stdc++.h>
#define lowbit(x) (x&-x)
#define debug cout
using namespace std;
const int maxn=1e5+1e2;
int dat[2*maxn];
int cmd[maxn],in[maxn],srt[maxn],uni[maxn],toin[maxn],len,cnt;
int n;
void update(int pos,int x)
{
    while(pos<=n) dat[pos]+=x,pos+=lowbit(pos);
}
int query(int x)
{
    int ret=0;
    while(x) ret+=dat[x],x-=lowbit(x);
    return ret;
}
int midfind(int pos)//return the first
{
    int l=1,r=cnt,mid;
    mid=(l+r)>>1;
    while(mid>l)
    {
        if(query(mid)>pos) r=mid;
        else l=mid;
        mid=(l+r)>>1;
    }
    return r;
}
int getrank(int rank)
{
    int base=midfind(rank);
    if(query(base-1)>=rank) return base-1;
    else return base;
}
int main()
{
    freopen("dat.txt","r",stdin);
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d%d",cmd+i,in+i);
       if(cmd[i]==1) srt[++len]=in[i];
    }
    srt[0]=0xffffffff;
    sort(srt+1,srt+1+len);
    for(int i=1;i<=len;i++) if(srt[i]!=srt[i-1]) uni[++cnt]=srt[i];
    for(int i=1,pos;i<=n;i++)
    {
        pos=lower_bound(uni+1,uni+1+cnt,in[i])-uni;
        if(cmd[i]==1) update(pos,1);
        else if(cmd[i]==2) update(pos,-1);
        else if(cmd[i]==3) printf("%d\n",query(pos-1)+1);
        else if(cmd[i]==4) printf("%d\n",uni[getrank(in[i])]);
        else if(cmd[i]==5) printf("%d\n",uni[getrank(query(in[i]-1))]);
        else if(cmd[i]==6) printf("%d\n",uni[midfind(query(in[i]))]);
    }
    return 0;
}
