#include<cstdio>
#include<cstring>
typedef long long int lli;
const int maxn=1e5+1e2,maxe=1e7+1e2,lim=1e5,alp=328;

int n,arylen;

int root[maxn];
struct SegmentTree {
    int lson[maxe],rson[maxe],dat[maxe],cnt;
    inline void insert(int &pos,int l,int r,const int &tar) {
        if( !pos ) { pos = ++cnt; } ++dat[pos];
        if( l == r ) return;
        const int mid = ( l + r ) >> 1;
        tar <= mid ? insert(lson[pos],l,mid,tar) : insert(rson[pos],mid+1,r,tar);
    }
    inline int query(int pos,int l,int r,const int &ll,const int &rr) {
        if( !pos || ( ll <= l && r <= rr ) ) return dat[pos];
        const int mid = ( l + r ) >> 1;
        if( rr <= mid ) return query(lson[pos],l,mid,ll,rr);
        else if( ll > mid ) return query(rson[pos],mid+1,r,ll,rr);
        return query(lson[pos],l,mid,ll,rr) + query(rson[pos],mid+1,r,ll,rr);
    }
    inline void reset() {
        ++cnt , memset(dat,0,cnt<<2) , memset(lson,0,cnt<<2) , memset(rson,0,cnt<<2) , cnt = 0;
    }
}sgt;

struct Array {
    int dat[71][maxn];
    int* operator [] (const int &x) { return dat[x]; }
    inline int segment(int id,int l,int r) {
        return dat[id][r] - dat[id][l-1];
    }
    inline void build() {
        for(int i=1;i<=arylen;i++) for(int j=1;j<=n;j++) dat[i][j] += dat[i][j-1];
    }
    inline void reset() {
        memset(dat,0,sizeof(dat));
    }
}ary;

namespace GetDivide {
    int prime[maxn],dv[maxn],cnt;
    inline void sieve() {
        static bool vis[maxn];
        for(int i=2;i<=lim;i++) {
            if( !vis[i] ) prime[++cnt] = i , dv[i] = cnt;
            for(int j=1;j<=cnt&&(lli)i*prime[j]<=lim;j++) {
                const int tar = i * prime[j];
                vis[tar] = 1 , dv[tar] = j;
                if( ! ( i % prime[j] ) ) break;
            }
        }
        while( prime[arylen+1] <= alp ) ++arylen;
    }
    inline void getdvs(int x,int* dvs,int* pows,int &len) {
        len = 0;
        while( x != 1 ) {
            if( !len || dv[x] != dvs[len] ) dvs[++len] = dv[x] , pows[len] = 0;
            ++pows[len] , x /= prime[dv[x]];
        }
    }
}
using GetDivide::getdvs;

inline void insert(int x,int id) {
    static int dvs[maxn],pows[maxn],len;
    getdvs(x,dvs,pows,len);
    for(int i=1;i<=len;i++) {
        if( dvs[i] <= arylen ) ary[dvs[i]][id] = pows[i];
        else sgt.insert(root[dvs[i]],1,n,id);
    }
}
inline bool query(int x,int l,int r) {
    static int dvs[maxn],pows[maxn],len;
    getdvs(x,dvs,pows,len);
    for(int i=1;i<=len;i++) {
        if( dvs[i] <= arylen ) {
            if( ary.segment(dvs[i],l,r) < pows[i] ) return 0;
        } else {
            if( !sgt.query(root[dvs[i]],1,n,l,r) ) return 0;
        }
    }
    return 1;
}

inline void reset() {
    sgt.reset() , ary.reset() , memset(root,0,sizeof(root));
}

int main() {
    static int T,m;
    scanf("%d",&T) , GetDivide::sieve();
    while(T--) {
        scanf("%d%d",&n,&m) , reset();
        for(int i=1,t;i<=n;i++) scanf("%d",&t) , insert(t,i);
        ary.build();
        for(int i=1,l,r,x;i<=m;i++) scanf("%d%d%d",&l,&r,&x) , puts(query(x,l,r)?"Yes":"No");
    }
    return 0;
}
