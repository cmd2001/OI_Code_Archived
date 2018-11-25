#pragma GCC optimize(3)
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
#include<ext/pb_ds/priority_queue.hpp>
const int maxn=2e4+1e2,maxe=2e5+1e2,maxs=1<<21,maxk=21;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxe<<1],nxt[maxe<<1],l[maxe<<1];
int f[maxk][maxs],dis[maxk][maxn],ans;
int lim[maxk];
int n,k,full;

struct Node {
    int dis,pos;
    friend bool operator < (const Node &a,const Node &b) {
        return a.dis > b.dis;
    }
};
__gnu_pbds::priority_queue<Node,std::less<Node>,__gnu_pbds::pairing_heap_tag> heap;
__gnu_pbds::priority_queue<Node,std::less<Node>,__gnu_pbds::pairing_heap_tag>::point_iterator it[maxn];

inline void addedge(int from,int to,int len) {
    static int cnt = 0;
    t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void dji(int* dis,int st) {
    memset(dis,0x3f,sizeof(int)*(n+1)) , dis[st] = 0;
    it[st]=heap.push((Node){dis[st],st});
    while( heap.size() ) {
        const int pos = (heap.top()).pos; heap.pop(); it[pos] = NULL;
        for(int at=s[pos];at;at=nxt[at])
            if( dis[t[at]] > dis[pos] + l[at] ) {
                dis[t[at]] = dis[pos] + l[at];
                if( it[t[at]] != NULL)
                    heap.modify(it[t[at]],(Node){dis[t[at]],t[at]});
                else it[t[at]] = heap.push((Node){dis[t[at]],t[at]});
            }
    }
}
inline void dp() {
    memset(f,0x3f,sizeof(f)) , ans = **f , f[0][0] = 0;
    for(int sta=0;sta<=full;sta++)
        for(int i=1;i<=k+1;i++)
            if( f[i-1][sta] != inf ) {
                for(int j=2;j<=k+1;j++)
                    if( ( sta & lim[j-1] ) == lim[j-1] )
                        f[j-1][sta|(1<<(j-2))] = std::min( f[j-1][sta|(1<<(j-2))] , f[i-1][sta] + dis[i-1][j] );
            }
    for(int i=1;i<=k+1;i++) {
        ans = std::min( ans , f[i-1][full] + dis[i-1][n] );
    }
}

inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret;
}
int main() {
    static int m,g;
    n = getint() , m = getint() , k = getint();
    for(int i=1,a,b,l;i<=m;i++) {
        a = getint() , b = getint() , l = getint();
        addedge(a,b,l) , addedge(b,a,l);
    }
    g = getint();
    for(int i=1,a,b;i<=g;i++) {
        a = getint() , b = getint();
        lim[b-1] |= ( 1 << ( a - 2 ) );
    }
    for(int i=1;i<=k+1;i++) dji(dis[i-1],i);
    full = ( 1 << k ) - 1 , dp();
    printf("%d\n",ans);
    return 0;
}

