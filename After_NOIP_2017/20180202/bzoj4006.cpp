#pragma GCC optimize(3)
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define bool unsigned char
using namespace std;
const int maxn=1e3+1e2,maxm=3e3+1e2,maxs=(1<<10)+2;

int s[maxn],t[maxm<<1],nxt[maxm<<1],l[maxm<<1];
int f[maxs][maxn],g[maxs],inp[15],inc[15];
bool inq[maxn];
int n,m,p,full;

inline void addedge(int from,int to,int len) {
    static int cnt = 0;
    t[++cnt] = to , l[cnt] = len ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void doubledge(int from,int to,int len) {
    addedge(from,to,len) , addedge(to,from,len);
}

inline void spfa(queue<int> &q,int* dis) {
    while( q.size() ) {
        const int pos = q.front(); q.pop(); inq[pos] = 0;
        for(int at=s[pos];at;at=nxt[at])
            if( dis[t[at]] > dis[pos] + l[at] ) {
                dis[t[at]] = dis[pos] + l[at];
                if( !inq[t[at]] ) q.push(t[at]) , inq[t[at]] = 1;
            }
    }
}
inline void getf() {
    static queue<int> q;
    memset(f,0x3f,sizeof(f));
    for(int i=1;i<=p;i++) f[1<<(i-1)][inp[i]] = 0;
    for(int sta=0;sta<=full;sta++) {
        for(int ss=sta;ss;ss=(ss-1)&sta)
            for(int i=1;i<=n;i++)
                f[sta][i] = min( f[sta][i] , f[ss][i] + f[sta^ss][i] );
        for(int i=1;i<=n;i++)
            q.push(i) , inq[i] = 1;
        spfa(q,f[sta]);
    }
}
inline bool judge(int sta) {
    for(int i=1;i<=p;i++)
        if( ( sta & inc[i]) && ( sta & inc[i] ) != inc[i] ) {
            return 0;
        }
    return 1;
}
inline void getg() {
    memset(g,0x3f,sizeof(g)) , *g = 0;
    for(int sta=0;sta<=full;sta++) {
        if( judge(sta) ) {
            for(int i=1;i<=n;i++)
                g[sta] = min( g[sta] , f[sta][i] );
        }
        for(int ss=sta;ss;ss=(ss-1)&sta)
            g[sta] = min( g[sta] , g[ss] + g[sta^ss] );
    }
}

int main() {
    scanf("%d%d%d",&n,&m,&p);
    full = ( 1 << p ) - 1;
    for(int i=1,a,b,l;i<=m;i++) {
        scanf("%d%d%d",&a,&b,&l);
        doubledge(a,b,l);
    }
    for(int i=1,x;i<=p;i++) {
        scanf("%d%d",&x,inp+i);
        inc[x] |= 1 << ( i - 1 );
    }
    getf();
    getg();
    printf("%d\n",g[full]);
    return 0;
}

