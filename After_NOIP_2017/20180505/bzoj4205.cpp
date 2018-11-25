#pragma GCC optimize(2)
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cctype>
const int maxn=1e5+1e2,maxe=1e7+1e2,maxb=2116;
const int ls[]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199},pl=46;
const int inf=0x3f3f3f3f;

namespace Flow {
    int s[maxn],cur[maxn],t[maxe],nxt[maxe],f[maxe];
    int dep[maxn],st,ed; // make ed the last point .
    
    inline void coredge(int from,int to,int flow) {
        static int cnt = 1;
        t[++cnt] = to , f[cnt] = flow , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void singledge(int from,int to,int flow) {
        coredge(from,to,flow) , coredge(to,from,0);
    }
    inline bool bfs() {
        memset(dep,-1,sizeof(int)*(ed+1)) , dep[st] = 0;
        std::queue<int> q; q.push(st);
        while( q.size() ) {
            const int pos = q.front(); q.pop();
            for(int at=s[pos];at;at=nxt[at])
                if( f[at] && !~dep[t[at]] )
                    dep[t[at]] = dep[pos] + 1 , q.push(t[at]);
        }
        return ~dep[ed];
    }
    inline int dfs(int pos,int flow) {
        if( pos == ed ) return flow;
        int ret = 0 , now = 0;
        for(int &at=cur[pos];at;at=nxt[at]) if( f[at] && dep[t[at]] > dep[pos] ) {
            now = dfs(t[at],std::min(flow,f[at])) ,
            ret += now , flow -= now , f[at] -= now , f[at^1] += now;
            if( !flow ) return ret;
        }
        if( !ret ) dep[pos] = -1;
        return ret;
    }
    inline int dinic() {
        int ret = 0;
        while( bfs() ) memcpy(cur,s,sizeof(int)*(ed+1)) , ret += dfs(st,inf);
        return ret;
    }
}
using namespace Flow;

int n,m;

inline int cov(int d1,int d2,int id) { // id in range [0,2]
    return n + m + ( ( d1 - 1 ) * 46 + d2 ) * 3 - 2 + id;
}
inline void build_lft(int a,int b,int c,int id) {
    for(int i=1;i<=pl;i++) for(int j=1;j<=pl;j++) {
        if( ! ( a % ls[i] ) && ! ( b % ls[j] ) ) singledge(id,cov(i,j,0),1);
        if( ! ( b % ls[i] ) && ! ( c % ls[j] ) ) singledge(id,cov(i,j,1),1);
        if( ! ( c % ls[i] ) && ! ( a % ls[j] ) ) singledge(id,cov(i,j,2),1);
    }
}
inline void build_rit(int a,int b,int c,int id) {
    for(int i=1;i<=pl;i++) for(int j=1;j<=pl;j++) {
        if( ! ( a % ls[i] ) && ! ( b % ls[j] ) ) singledge(cov(i,j,0),id,1);
        if( ! ( b % ls[i] ) && ! ( c % ls[j] ) ) singledge(cov(i,j,1),id,1);
        if( ! ( c % ls[i] ) && ! ( a % ls[j] ) ) singledge(cov(i,j,2),id,1);
    }
}
inline char nextchar() {
    static const int BS = 1 << 21;
    static char buf[BS],*st=buf+BS,*ed=buf+BS;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? -1 : *st++;
}
inline int getint() {
    int ret = 0;
    char ch;
    while( !isdigit(ch=nextchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=nextchar()) );
    return ret;
}

int main() {
    n = getint() , m = getint() , st = n + m + maxb * 3 + 1 , ed = st + 1;
    for(int i=1,a,b,c;i<=n;i++) a = getint() , b = getint() , c = getint() , singledge(st,i,1) , build_lft(a,b,c,i);
    for(int i=1,a,b,c;i<=m;i++) a = getint() , b = getint() , c = getint() , singledge(i+n,ed,1) , build_rit(a,b,c,i+n);
    printf("%d\n",dinic());
    return 0;
}
