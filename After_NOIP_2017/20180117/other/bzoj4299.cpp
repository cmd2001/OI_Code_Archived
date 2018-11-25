#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e5+1e2,maxm=5e6+1e2;
const int lim=1e9;

int srt[maxn],in[maxn],len;
int l[maxm],r[maxm],lson[maxm],rson[maxm],sum[maxm],cnt;
int root[maxn];

inline void build(int pos,int ll,int rr) {
    l[pos] = ll , r[pos] = rr;
    if( ll == rr ) return;
    const int mid = ( ll + rr ) >> 1;
    build( lson[pos] = ++cnt , ll , mid );
    build( rson[pos] = ++cnt , mid+1 , rr );
}
inline void insert(int pos,int pre,int tar,int x) {
    l[pos] = l[pre] , r[pos] = r[pre] ,
    lson[pos] = lson[pre] , rson[pos] = rson[pre];
    if( l[pos] == r[pos] && l[pos] == tar ) {
        sum[pos] = sum[pre] + x;
        return;
    }
    const int mid = ( l[pos] + r[pos] ) >> 1;
    if( tar <= mid ) insert(lson[pos]=++cnt,lson[pre],tar,x);
    else insert(rson[pos]=++cnt,rson[pre],tar,x);
    sum[pos] = sum[lson[pos]] + sum[rson[pos]];
}
inline int query(int pos,int pre,int ll,int rr) {
    if( rr < l[pos] || r[pos] < ll ) return 0;
    if( ll <= l[pos] && r[pos] <= rr ) return sum[pos] - sum[pre];
    return query(lson[pos],lson[pre],ll,rr) + query(rson[pos],rson[pre],ll,rr);
}

inline int getans(int l,int r) {
    for(int ret=1,sum;;ret=sum+1) {
        int rr = upper_bound(srt+1,srt+1+len,ret) - srt - 1;
        sum = query(root[r],root[l-1],1,rr);
        if( sum < ret ) return ret;
    }
}


int main() {
    static int n,m;
    
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",in+i) , srt[i] = in[i];
    
    sort(srt+1,srt+1+n);
    len = unique(srt+1,srt+1+n) - srt - 1;
    for(int i=1;i<=n;i++)
        in[i] = lower_bound(srt+1,srt+1+len,in[i]) -srt;
    
    build(root[0]=++cnt,1,len);
    for(int i=1;i<=n;i++)
        insert(root[i]=++cnt,root[i-1],in[i],srt[in[i]]);
    
    scanf("%d",&m);
    for(int i=1,l,r;i<=m;i++) {
        scanf("%d%d",&l,&r);
        printf("%d\n",getans(l,r));
    }
    
    return 0;
}