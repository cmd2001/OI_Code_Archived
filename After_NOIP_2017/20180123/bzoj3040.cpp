#include<cstdio>
#include<cstring>
#include<ext/pb_ds/priority_queue.hpp>
#define lli long long int
using namespace std;
using namespace __gnu_pbds;
const int maxn=1e6+1e1,maxm=1e7+1e1;

struct Node {
    lli dis;
    int pos;
    friend bool operator < (const Node &a,const Node &b) {
        return a.dis != b.dis ? a.dis > b.dis : a.pos > b.pos;
    }
};
__gnu_pbds::priority_queue<Node,less<Node>,pairing_heap_tag> heap;
__gnu_pbds::priority_queue<Node,less<Node>,pairing_heap_tag>::point_iterator it[maxn];

int s[maxn],t[maxm],nxt[maxm];
lli l[maxm];
lli dis[maxn];
int n;

inline void addedge(int from,int to,int len) {
    static int cnt = 0;
    t[++cnt] = to , l[cnt] = len ,
    nxt[cnt] = s[from] , s[from] = cnt;
}

lli x,y,rxa,rxc,rya,ryc,rp;

inline void ite() {
    static int a,b;
    x = ( x * rxa + rxc ) % rp ,
    y = ( y * rya + ryc ) % rp;
    a = min( x % n , y % n ) + 1;
    b = max( x % n , y % n ) + 1;
    addedge(a,b,100000000-100*a);
}

inline void dji() {
    memset(dis,0x3f,sizeof(dis)); dis[1] = 0;
    it[1]=heap.push((Node){dis[1],1});
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
    static int m,t;
    n = getint() , m = getint();
    t = getint() , rxa = getint() , rxc = getint() , rya = getint() , ryc = getint() , rp = getint();
    for(int i=1;i<=t;i++)
        ite();
    for(int i=t+1,a,b,l;i<=m;i++) {
        a = getint() , b = getint() , l = getint();
        addedge(a,b,l);
    }
    
    dji();
    
    printf("%lld\n",dis[n]);
    
    return 0;
}
