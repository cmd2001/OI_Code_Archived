#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cstdlib>
#define bool unsigned char
#define debug cout
using namespace std;
const int maxn=2e2+1e2,maxm=maxn*maxn;
const int inf=0x3f3f3f3f;

int s[maxn<<1],t[maxm<<5],nxt[maxm<<5],f[maxm<<5],c[maxm<<5];
int dis[maxn<<1],sou[maxn<<1];
int n,m,st,ed,ans,fl;

inline void coredge(int from,int to,int flow,int cost) {
    static int cnt = 1;
    t[++cnt] = to , f[cnt] = flow , c[cnt] = cost ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,int flow,int cost) {
    //debug<<"cost = "<<cost<<endl;
    coredge(from,to,flow,cost) , coredge(to,from,0,-cost);
}

inline bool spfa() {
    static bool inq[maxn<<1];
    memset(dis,0x3f,sizeof(dis)); dis[st] = 0;
    queue<int> q; q.push(st); inq[st] = 1;
    while( q.size() ) {
        const int pos = q.front(); q.pop(); inq[pos] = 0;
        if( pos == ed ) continue;
        for(int at=s[pos];at;at=nxt[at])
            if( f[at] && dis[t[at]] > dis[pos] + c[at] ) {
                dis[t[at]] = dis[pos] + c[at] , sou[t[at]] = at;
                if( !inq[t[at]] ) {
                    q.push(t[at]) , inq[t[at]] = 1;
                }
            }
    }
    //debug<<"dis = "<<dis[ed]<<endl;
    return dis[ed] != inf;
}
inline int release() {
    int ret = inf;
    for(int i=ed;i!=st;i=t[sou[i]^1])
        ret = min( ret , f[sou[i]] );
    for(int i=ed;i!=st;i=t[sou[i]^1])
        f[sou[i]] -= ret , f[sou[i]^1] += ret;
    return ret;
}
inline int flow(int& f) {
    f = 0;
    int ret = 0,flow;
    while( spfa() ) {
        flow = release();
        ret += flow * dis[ed] , f += flow;
    }
    return ret;
}

inline int covnum(int x) {
    return x + n;
}

int main() {
    scanf("%d",&n);
    st = n * 2 + 1 , ed = st + 1;
    for(int i=1;i<=n;i++)
        singledge(st,i,1,0);
    for(int i=1,a,m,b,k;i<=n;i++) {
        scanf("%d%d%d%d",&m,&a,&b,&k);
        for(int j=a;j<=b;j++)
            singledge(i,covnum(j),1,k*abs(j-m));
    }
    for(int i=1;i<=n;i++)
        singledge(covnum(i),ed,1,0);
    //debug<<"inited"<<endl;
    
    ans = flow(fl);
    
    if( fl != n ) puts("NIE");
    else printf("%d\n",ans);
    
    return 0;
}


