#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e5+1e2,maxm=2e5+1e2,maxk=1e5+1e2;

int fa[maxn],siz[maxn];
int a[maxm],b[maxm];
int len[maxk],met[maxk][6];
int cnt[maxm],stk[maxn],top;
char ans[maxk];
int n;

inline int findfa(int x) {
    return fa[x] == x ? x : findfa(fa[x]);
}

inline void merge(int l,int r) {
    for(int i=l;i<=r;i++)
        for(int j=1;j<=len[i];j++) {
            const int k = met[i][j];
            if( --cnt[k] ) continue;
            int aa = findfa(a[k]) , bb = findfa(b[k]);
            if( aa == bb ) continue;
            if( siz[aa] > siz[bb] ) fa[bb] = aa , siz[aa] += siz[bb] , stk[++top] = bb;
            else fa[aa] = bb , siz[bb] += siz[aa] , stk[++top] = aa;
        }
}
inline void resetcnt(int l,int r) {
    for(int i=l;i<=r;i++)
        for(int j=1;j<=len[i];j++)
            ++cnt[met[i][j]];
}
inline void resetfa(int tar) {
    while( top > tar ) {
        const int pos = stk[top--];
        siz[fa[pos]] -= siz[pos] , fa[pos] = pos;
    }
}

inline void solve(int ll,int rr) {
    if( ll == rr ) {
        ans[ll] = ( siz[findfa(1)] == n );
        return;
    }
    const int mid = ( ll + rr ) >> 1 , mem = top;
    
    merge(ll,mid);
    solve(mid+1,rr);
    resetfa(mem);
    resetcnt(ll,mid);
    
    merge(mid+1,rr);
    solve(ll,mid);
    resetfa(mem);
    resetcnt(mid+1,rr);
}

inline void init() {
    for(int i=1;i<=n;i++)
        fa[i] = i , siz[i] = 1;
}

int main() {
    static int m,k;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        scanf("%d%d",a+i,b+i);
    scanf("%d",&k);
    for(int i=1;i<=k;i++) {
        scanf("%d",len+i);
        for(int j=1;j<=len[i];j++)
            scanf("%d",met[i]+j);
    }
    
    init();
    resetcnt(1,k);
    for(int i=1;i<=m;i++)
        if( !cnt[i] ) {
            int aa = findfa(a[i]) , bb = findfa(b[i]);
            if( aa == bb ) continue;
            if( siz[aa] > siz[bb] ) fa[bb] = aa , siz[aa] += siz[bb];
            else fa[aa] = bb , siz[bb] += siz[aa];
        }
    
    solve(1,k);
    
    for(int i=1;i<=k;i++)
        puts( ans[i] ? "Connected" : "Disconnected" );
    
    return 0;
}
