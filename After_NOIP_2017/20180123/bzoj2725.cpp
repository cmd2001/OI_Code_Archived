#pragma GCC optimize(2)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ext/pb_ds/priority_queue.hpp>
#include<cctype>
#define bool unsigned char
#define lli long long int
#define debug cout
using namespace std;
using namespace __gnu_pbds;
const int maxn=2e5+1e2;
const lli inf=0x3f3f3f3f3f3f3f3fll;

int fr[maxn<<1],to[maxn<<1],le[maxn<<1];
lli disst[maxn],dised[maxn];
int soust[maxn],soued[maxn],pid[maxn],lve[maxn],bck[maxn];
int n,m,q,s,t,ecnt,plen;

namespace Dji {
    int s[maxn],t[maxn<<1],nxt[maxn<<1],l[maxn<<1];
    bool vis[maxn];
    int *sou,*lve;
    lli *dis;
    
    struct Node {
        lli dd;
        int pos;
        friend bool operator < (const Node &a,const Node &b) {
            return a.dd > b.dd;
        }
    };
    __gnu_pbds::priority_queue<Node,less<Node>,pairing_heap_tag> heap;
    
    inline void reset() {
        while( heap.size() ) heap.pop();
        for(int i=1;i<=n;i++)
            dis[i] = inf;
        memset(vis,0,sizeof(vis));
    }
    
    inline void addedge(int from,int to,int len) {
        static int cnt = 0;
        t[++cnt] = to , l[cnt] = len,
        nxt[cnt] = s[from] , s[from] = cnt;
    }
    
    inline void dji1(int st,lli* dd,int* ss) {
        dis = dd , sou = ss;
        reset() , dis[st] = 0 ;
        for(int i=1;i<=n;i++)
            heap.push((Node){dis[i],i});
        for(int i=1;i<n;i++) {
            const int pos = (heap.top()).pos; heap.pop();
            if( vis[pos] ) {
                --i;
                continue;
            }
            vis[pos] = 1;
            for(int at=s[pos];at;at=nxt[at])
                if( dis[t[at]] > dis[pos] + l[at] ) {
                    dis[t[at]] = dis[pos] + l[at] , sou[t[at]] = pos;
                    heap.push((Node){dis[t[at]],t[at]});
                }
        }
    }
    
    inline void dji2(int st,lli* dd,int* ll) {
        dis = dd , lve = ll;
        reset() , dis[st] = 0 , lve[st] = pid[st];
        for(int i=1;i<=n;i++)
            heap.push((Node){dis[i],i});
        for(int i=1;i<n;i++) {
            const int pos = (heap.top()).pos; heap.pop();
            if( vis[pos] ) {
                --i;
                continue;
            }
            vis[pos] = 1;
            for(int at=s[pos];at;at=nxt[at])
                if( dis[t[at]] > dis[pos] + l[at] ) {
                    dis[t[at]] = dis[pos] + l[at] ,
                    lve[t[at]] = pid[pos] ? pid[pos] : lve[pos] ;
                    if( pid[t[at]] ) lve[t[at]] = pid[t[at]];
                    heap.push((Node){dis[t[at]],t[at]});
                }
        }
    }
}

struct SegmentTree {
    int lson[maxn<<3],rson[maxn<<3],cnt;
    lli mi[maxn<<3];
    
    inline void build(int pos,int ll,int rr) {
        mi[pos] = inf;
        if( ll == rr ) return;
        const int mid = ( ll + rr ) >> 1;
        build(lson[pos]=++cnt,ll,mid);
        build(rson[pos]=++cnt,mid+1,rr);
    }
    
    inline void update(int pos,int l,int r,int ll,int rr,lli val) {
        if( rr < l || r < ll ) return;
        if( ll <= l&& r <= rr ) {
            mi[pos] = min( mi[pos] , val );
            return;
        }
        const int mid = ( l + r ) >> 1;
        update(lson[pos],l,mid,ll,rr,val);
        update(rson[pos],mid+1,r,ll,rr,val);
    }
    inline lli query(int pos,int l,int r,int tar) {
        if( l == r ) return mi[pos];
        const int mid = ( l + r ) >> 1;
        if( tar <= mid ) return min( mi[pos] , query(lson[pos],l,mid,tar) );
        else return min( mi[pos] , query(rson[pos],mid+1,r,tar) );
    }
    inline void init(int x) {
        build(cnt=1,1,x);
    }
}sgt;

inline void getpid(int st,int ed) {
    for(int i=st;;i=soued[i]) {
        pid[i] = ++plen;
        if( i == ed ) break;
    }
}
inline void updatedge() {
    sgt.init(plen-1);
    for(int i=1;i<=ecnt;i++)
        if( lve[fr[i]] < bck[to[i]] ) {
            if( ( pid[fr[i]] && pid[to[i]] ) && pid[fr[i]] + 1 == pid[to[i]] ) continue;
            sgt.update(1,1,plen-1,lve[fr[i]],bck[to[i]]-1,disst[fr[i]]+le[i]+dised[to[i]]);
        }
}
inline lli queryedge(int x,int y) {
    if( ! ( pid[x] && pid[y] ) )
        return disst[t];
    if( min( pid[x] , pid[y] ) + 1 != max( pid[x] , pid[y] ) )
        return disst[t];
    return sgt.query( 1 , 1 , plen - 1 , min( pid[x] , pid[y] ) );
}
inline void gen() {
    Dji::dji1(s,disst,soust);
    Dji::dji1(t,dised,soued);
    getpid(s,t);
    Dji::dji2(s,disst,lve);
    Dji::dji2(t,dised,bck);
    updatedge();
}

inline char nextchar() {
    static char buf[1<<22],*st=buf+(1<<22),*ed=buf+(1<<22);
    if( st == ed ) ed = buf + fread( st = buf , 1 , 1 << 22 , stdin );
    return st == ed ? -1 : *st++;
}
inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=nextchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=nextchar()) );
    return ret;
}
int main() {
    static lli ans,len;
    
    n = getint() , m = getint();
    for(int i=1,a,b;i<=m;i++) {
        a = getint() , b = getint() , len = getint();
        fr[++ecnt] = a , to[ecnt] = b , le[ecnt] = len ,
        fr[++ecnt] = b , to[ecnt] = a , le[ecnt] = len;
        Dji::addedge(a,b,len) , Dji::addedge(b,a,len);
    }
    s = getint() , t = getint();
    
    gen();
    
    q = getint();
    for(int i=1,x,y;i<=q;i++) {
        x = getint() , y = getint();
        ans = queryedge(x,y);
        if( ans == inf ) puts("Infinity");
        else printf("%lld\n",ans);
    }
    
    return 0;
}

