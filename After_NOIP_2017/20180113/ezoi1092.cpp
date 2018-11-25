#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e5+1e2,maxm=3e6+1e2;

int in[maxn];
int l[maxm],r[maxm],lson[maxm],rson[maxm],siz[maxm],cnt;
int root[maxn];

inline void prebuild(int pos,int ll,int rr) {
    l[pos] = ll , r[pos] = rr;
    if( ll == rr ) return;
    const int mid = ( ll + rr ) >> 1;
    prebuild(lson[pos]=++cnt,ll,mid);
    prebuild(rson[pos]=++cnt,mid+1,rr);
}

inline void insert(int pos,int pre,int tar) {
    l[pos] = l[pre] , r[pos] = r[pre] ,
    lson[pos] = lson[pre] , rson[pos] = rson[pre];
    if( l[pos] == r[pos] && l[pos] == tar ) {
        siz[pos] = siz[pre] + 1;
        return;
    }
    const int mid = ( l[pos] + r[pos] ) >> 1;
    if( tar <= mid ) insert(lson[pos]=++cnt,lson[pre],tar);
    else insert(rson[pos]=++cnt,rson[pre],tar);
    siz[pos] = siz[lson[pos]] + siz[rson[pos]];
}

inline int query(int pos,int pre,int lim) {
    if( l[pos] > lim ) return 0;
    if( r[pos] <= lim ) return siz[pos] - siz[pre];
    return query(lson[pos],lson[pre],lim) + query(rson[pos],rson[pre],lim);
}

int main() {
    static int n,m;
    scanf("%d%d",&n,&m);
    prebuild(root[0]=++cnt,1,1e5);
    for(int i=1;i<=n;i++) {
        scanf("%d",in+i);
        insert(root[i]=++cnt,root[i-1],in[i]);
    }
    for(int i=1,l,r,k;i<=m;i++) {
        scanf("%d%d%d",&l,&r,&k);
        printf("%d\n",query(root[r],root[l-1],k));
    }
    return 0;
}
