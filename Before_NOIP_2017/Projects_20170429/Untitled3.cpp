#include<bits/stdc++.h>
#define lowbit(x) (x&(-x))
#define debug cout
using namespace std;
const int maxn=1e6+1e2;
int dat[maxn],in[maxn],srt[maxn],n,tmp,len;
long long int ans;
void update(int pos)
{
    while(pos<=n)
    {
        dat[pos]++;
        pos+=lowbit(pos);
    }
}
int query(int pos)
{
    int ret=0;
    while(pos)
    {
        ret+=dat[pos];
        pos-=lowbit(pos);
    }
    return ret;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&tmp);
        in[i]=srt[i]=tmp;
    }
    sort(srt+1,srt+1+n);
    len=unique(srt+1,srt+1+n)-srt-1;
    for(int i=1;i<=n;i++)
    {
        tmp=lower_bound(srt+1,srt+1+len,in[i])-srt;
        update(tmp);
        ans+=i-query(tmp);
    }
    printf("%lld\n",ans);
    return 0;
}
