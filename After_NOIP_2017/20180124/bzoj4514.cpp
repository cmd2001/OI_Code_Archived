#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<cmath>
#define bool unsigned char
#define lli long long int
using namespace std;
const int maxn=4e2+1e1,maxm=maxn*maxn;
const int int_inf=0x3f3f3f3f;
const lli lli_inf=0x3f3f3f3f3f3f3f3fll;

int in[maxn],siz[maxn];
lli val[maxn];
int s[maxn],t[maxm<<4],nxt[maxm<<4],f[maxm<<4];
lli dis[maxn],c[maxm<<4];
int sou[maxn];
int st,ed;

inline void coredge(int from,int to,int flow,lli cost) {
    static int cnt = 1;
    t[++cnt] = to , f[cnt] = flow , c[cnt] = cost ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,int flow,lli cost) {
    coredge(from,to,flow,cost) , coredge(to,from,0,-cost);
}
inline bool spfa() {
    static bool inq[maxn];
    for(int i=0;i<=ed;i++) dis[i] = -lli_inf;
    dis[st] = 0;
    queue<int> q; q.push(st); inq[st] = 1;
    while( q.size() ) {
        const int pos = q.front(); q.pop(); inq[pos] = 0;
        for(int at=s[pos];at;at=nxt[at])
            if( f[at] && dis[t[at]] < dis[pos] + c[at] ) {
                dis[t[at]] = dis[pos] + c[at] , sou[t[at]] = at;
                if( !inq[t[at]] ) {
                    q.push(t[at]) , inq[t[at]] = 1;
                }
            }
    }
    return dis[ed] != -lli_inf;
}
inline int release(lli sum) {
    lli ret = int_inf;
    if( dis[ed] < 0 ) ret = min( ret , sum / ( -dis[ed] ) );
    for(int i=ed;i!=st;i=t[sou[i]^1])
        ret = min( ret , (lli) f[sou[i]] );
    for(int i=ed;i!=st;i=t[sou[i]^1])
        f[sou[i]] -= ret , f[sou[i]^1] += ret;
    return ret;
}
inline int flow() {
    int ret = 0,now;
    lli sum = 0;
    while( spfa() ) {
        if( sum + dis[ed] < 0 ) break;
        now = release(sum);
        sum += dis[ed] * now , ret += now;
    }
    return ret;
}

inline int cov(int x,int sta) {
    return x * 2 - 1 + sta;
}
inline bool isprime(int x) {
    if( x == 0 || x == 1 ) return 0;
    int sq = sqrt(x);
    for(int i=2;i<=sq;i++)
        if( ! ( x % i ) )
            return 0;
    return 1;
}

int main() {
    static int n;
    scanf("%d",&n);
    st = n * 2 + 1 , ed = st + 1;
    for(int i=1;i<=n;i++)
        scanf("%d",in+i);
    for(int i=1;i<=n;i++)
        scanf("%d",siz+i);
    for(int i=1;i<=n;i++)
        scanf("%lld",val+i);
    for(int i=1;i<=n;i++) {
        singledge(st,cov(i,0),siz[i],0) , 
        singledge(cov(i,1),ed,siz[i],0) ;
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) {
            if( ( ! ( in[i] % in[j] ) ) && isprime( in[i] / in[j] ) )
                singledge(cov(i,0),cov(j,1),int_inf,val[i]*val[j]);
            if( ( ! ( in[j] % in[i] ) ) && isprime( in[j] / in[i] ) )
                singledge(cov(i,0),cov(j,1),int_inf,val[i]*val[j]);
        }
    
    printf("%d\n",flow()>>1);
    
    return 0;
}

