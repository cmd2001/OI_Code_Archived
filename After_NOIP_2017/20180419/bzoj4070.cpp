#pragma GCC optimize("Ofast")
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
#include<cctype>
#define bool unsigned char
const unsigned maxn=3e6+3e4+1e2,maxe=maxn*5;
const unsigned inf=0x3f3f3f3f;

unsigned s[maxn],t[maxe],nxt[maxe],l[maxe],cnt;
unsigned dis[maxn],st,ed;
bool inq[maxn];
unsigned n,m,blk;

__inline void addedge(unsigned from,unsigned to,unsigned len) {
    t[++cnt] = to , l[cnt] = len , nxt[cnt] = s[from] , s[from] = cnt;
}
__inline bool spfa() {
    memset(dis,0x3f,sizeof(unsigned)*(n*(blk+1)+1)) , dis[st] = 0;
    std::queue<unsigned> q; q.push(st) , inq[st] = 1;
    while( q.size() ) {
        const unsigned pos = q.front() , dp=dis[pos]; q.pop() , inq[pos] = 0;
        for(unsigned at=s[pos],tar=t[at],cal;at;at=nxt[at],tar=t[at])
            if( dis[tar] > ( cal = dp + l[at] ) ) {
                dis[tar] = cal;
                if( !inq[tar] ) q.push(tar) , inq[tar] = 1;
            }
    }
    return dis[ed] != inf;
}
__inline unsigned cov(unsigned x,unsigned tpe) { // tpe from 0 to blk .
    return ( blk + 1 ) * --x + tpe + 1;
}

__inline unsigned getint() {
    unsigned ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret;
}

int main() {
    blk = std::min( (unsigned)std::sqrt(n=getint()) , 100u ) , m = getint();
    for(unsigned i=1,b,p;i<=m;i++) {
        b = getint() + 1 , p = getint();
        if( i == 1 ) st = cov(b,0);
        else if( i == 2 ) ed = cov(b,0);
        if( p > blk ) {
            for(unsigned j=1,delta=p;b+delta<=n;j++,delta+=p) addedge(cov(b,0),cov(b+delta,0),j);
            for(unsigned j=1,delta=p;b>delta;j++,delta+=p) addedge(cov(b,0),cov(b-delta,0),j);
        } else addedge(cov(b,0),cov(b,p),0);
    }
    for(unsigned i=1;i<=n;i++) for(unsigned j=1;j<=blk;j++) {
        addedge(cov(i,j),cov(i,0),0);
        if( i + j <= n ) addedge(cov(i,j),cov(i+j,j),1);
        if( i > j ) addedge(cov(i,j),cov(i-j,j),1);
    }
    if( !spfa() ) puts("-1");
    else printf("%d\n",dis[ed]);
    return 0;
}

