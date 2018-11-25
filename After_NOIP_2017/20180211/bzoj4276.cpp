#pragma GCC optimize(3)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define debug cout
using namespace std;
const int maxn=5e3+1e2;
const int inf=0x3f3f3f3f;

int s[maxn<<3],t[maxn*100],nxt[maxn*100],f[maxn*100],c[maxn*100];
int dis[maxn<<3],sou[maxn<<3],inq[maxn<<3];
int n,m,st,ed,full;

inline void coredge(int from,int to,int flow,int cost) {
    static int cnt = 1;
    t[++cnt] = to , f[cnt] = flow , c[cnt] = cost ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,int flow,int cost) {
    full = max( full , max(from,to) );
    coredge(from,to,flow,cost) , coredge(to,from,0,-cost);
}
inline bool spfa() {
    for(int i=1;i<=full;i++) dis[i] = -inf;
    dis[st] = 0;
    queue<int> q; q.push(st) , inq[st] = 1;
    while( q.size() ) {
        const int pos = q.front(); q.pop() , inq[pos] = 0;
        for(int at=s[pos];at;at=nxt[at])
            if( f[at] && dis[t[at]] < dis[pos] + c[at] ) {
                dis[t[at]] = dis[pos] + c[at] , sou[t[at]] = at;
                if( !inq[t[at]] ) q.push(t[at]) , inq[t[at]] = 1;
            }
            
    }
    return dis[ed] != -inf;
}
inline int release() {
    int ret = inf;
    for(int i=ed;i!=st;i=t[sou[i]^1])
        ret = min( ret , f[sou[i]] );
    for(int i=ed;i!=st;i=t[sou[i]^1])
        f[sou[i]] -= ret , f[sou[i]^1] += ret;
    return ret;
}
inline int flow() {
    int ret = 0;
    while( spfa() ) {
        ret += dis[ed] * release();
    }
    return ret;
}

inline int covs(int x) {
    return x + m + 2;
}
namespace SegmentTree {
    int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3],cnt;
    inline void build(int pos,int ll,int rr) {
        l[pos] = ll , r[pos] = rr;
        if( ll == rr ) {
            singledge(covs(pos),ed,1,0);
            return;
        }
        const int mid = ( ll + rr ) >> 1;
        build(lson[pos]=++cnt,ll,mid) , singledge(covs(pos),covs(lson[pos]),mid-ll+1,0) ,
        build(rson[pos]=++cnt,mid+1,rr) , singledge(covs(pos),covs(rson[pos]),rr-mid,0) ;
    }
    inline void update(int pos,int ll,int rr,int id) {
        if( rr < l[pos] || r[pos] < ll ) return;
        if( ll <= l[pos] && r[pos] <= rr ) {
            singledge(id,covs(pos),1,0);
            return;
        }
        update(lson[pos],ll,rr,id);
        update(rson[pos],ll,rr,id);
    }
}

int main() {
    scanf("%d",&m) , st = m + 1 , ed = m + 2;
    SegmentTree::build(SegmentTree::cnt=1,1,5000);
    for(int i=1,a,b,c;i<=m;i++) {
        scanf("%d%d%d",&a,&b,&c);
        singledge(st,i,1,c);
        SegmentTree::update(1,a,b-1,i);
    }
    printf("%d\n",flow());
    return 0;
}
