#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
#define debug cout
using namespace std;
const int maxn=110,maxm=maxn*maxn;
const double eps=1e-6;

int s[maxn],t[maxm<<3],nxt[maxm<<3],f[maxm<<3];
int sou[maxn];
double dis[maxn];
double c[maxm<<3];
double in[maxn][maxn];
int st,ed;

inline void coredge(int from,int to,int flow,double cost) {
    static int cnt = 1;
    t[++cnt] = to , f[cnt] = flow , c[cnt] = cost,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,int flow,double cost) {
    coredge(from,to,flow,cost);
    coredge(to,from,0,-cost);
}

inline bool spfa() {
    static char inq[maxn];
    memset(dis,0xc2,sizeof(dis)); dis[st] = 0;
    queue<int> q; q.push(st); inq[st] = 1;
    while( q.size() ) {
        const int pos = q.front(); q.pop(); inq[pos] = 0;
        if( pos == ed ) continue;
        for(int at=s[pos];at;at=nxt[at])
            if( f[at] && dis[t[at]] < dis[pos] + c[at] ) {
                dis[t[at]] = dis[pos] + c[at] , sou[t[at]] = at;
                if( !inq[t[at]] ) {
                    q.push(t[at]) , inq[t[at]] = 1;
                }
            }
    }
    return fabs( dis[ed] - *dis ) > eps;
}
inline int release() {
    int ret = 100;
    for(int i=ed;i!=st;i=t[sou[i]^1])
        ret = min( ret , f[sou[i]] );
    for(int i=ed;i!=st;i=t[sou[i]^1])
        f[sou[i]] -= ret , f[sou[i]^1] += ret;
    //debug<<"ret = "<<ret<<endl;
    return ret;
}
inline double flow() {
    double ret = 0;
    while( spfa() )
        ret += release() * dis[ed];
    return ret;
}
int n,m;

inline int covb(int x) {
    return x + m;
}

int main() {
    static int k;
    scanf("%d%d%d",&m,&n,&k);
    st = n + m + 1 , ed = n + m + 2;
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++) {
            scanf("%lf",in[i]+j);
            in[i][j] = log2(in[i][j]);
        }
    
    for(int i=1;i<=m;i++)
        singledge(st,i,k,0);
    for(int i=1;i<=n;i++)
        singledge(covb(i),ed,1,0);
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++)
            singledge(i,covb(j),1,in[i][j]);
    
    printf("%0.4lf\n",pow(2,flow()));
    
    return 0;
}
