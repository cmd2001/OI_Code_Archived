#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cctype>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=5e2+1e1,maxm=maxn*maxn;
const lli inf=0x3f3f3f3f3f3f3f3fLL;

int s[maxn],t[maxm<<5],nxt[maxm<<5];
lli f[maxm<<5],c[maxm<<5];
lli dis[maxn];
int sou[maxn];
char inq[maxn];
int n,m,st,ed;

inline void coredge(int from,int to,int flow,int cost) {
    static int cnt = 1;
    t[++cnt] = to , f[cnt] = flow , c[cnt] = cost,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,int flow,int cost) {
    coredge(from,to,flow,cost);
    coredge(to,from,0,-cost);
}

inline bool spfa() {
    memset(dis,0x3f,sizeof(dis)); dis[st] = 0;
    queue<int> q; q.push(st);
    while( q.size() ) {
        const int pos = q.front(); q.pop();
        inq[pos] = 0;
        for(int at=s[pos];at;at=nxt[at])
            if( f[at] && dis[t[at]] > dis[pos] + c[at] ) {
                dis[t[at]] = dis[pos] + c[at] ,
                sou[t[at]] = at;
                if( !inq[t[at]] ) {
                    inq[t[at]] = 1 ,
                    q.push(t[at]);
                }
            }
    }
    return dis[ed] != inf;
}
inline lli release() {
    lli ret = inf;
    for(int pos=ed;pos!=st;pos=t[sou[pos]^1]) {
        //debug<<"pos = "<<pos<<endl;
        ret = min( ret , f[sou[pos]] );
    }
    for(int pos=ed;pos!=st;pos=t[sou[pos]^1])
        f[sou[pos]] -= ret , f[sou[pos]^1] += ret;
    //debug<<"in release ret = "<<ret<<endl;
    return ret;
}
inline lli flow() {
    lli ret = 0;
    while( spfa() ) {
        //debug<<"dis = "<<dis[ed]<<endl;
        ret += dis[ed] * release();
    }
    return ret;
}

inline int covobj(int x) {
    return x + m;
}

inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret;
}
int main() {
    static int t[maxn],w[maxn];
    m = getint() , n = getint();
    //debug<<"n = "<<n<<"m = "<<m<<endl;
    st = n + m + 1 , ed = n + m + 2;
    for(int i=1,c;i<=n;i++) {
        c = getint();
        singledge(covobj(i),ed,c,0);
    }
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            if( getint() ) {
                //debug<<"i = "<<i<<"j = "<<j<<endl;
                //debug<<"cov = "<<covobj(j)<<endl;
                singledge(i,covobj(j),inf,0);
            }
    for(int i=1,s;i<=m;i++) {
        s = getint();
        for(int i=1;i<=s;i++) t[i] = getint();
        for(int i=1;i<=s+1;i++) w[i]=getint();
        for(int j=1;j<=s;j++)
            singledge(st,i,t[j]-t[j-1],w[j]);
        singledge(st,i,inf,w[s+1]);
    }
    
    printf("%lld\n",flow());
    
    return 0;
}