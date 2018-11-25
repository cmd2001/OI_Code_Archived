#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define lli long long int
const int maxn=1e3+1e2,maxe=maxn<<4;
const int int_inf=0x3f3f3f3f;
const lli lli_inf=0x3f3f3f3f3f3f3f3fll;

lli ins[maxn],ine[maxn];
int s[maxn],t[maxe],nxt[maxe],f[maxe],sou[maxn],tar[maxn],cnt=1;
lli c[maxe],dis[maxn];
bool inq[maxn];
int n,k,ms,me,st,ed,lim;

inline void coredge(int from,int to,int flow,lli cost) {
    t[++cnt] = to , f[cnt] = flow , c[cnt] = cost ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void singledge(int from,int to,int flow,lli cost) {
    coredge(from,to,flow,cost) , coredge(to,from,0,-cost);
}
inline bool spfa() {
    memset(dis,0x3f,sizeof(dis)) , dis[st] = 0;
    std::queue<int> q; q.push(st) , inq[st] = 1;
    while( q.size() ) {
        const int pos = q.front(); q.pop() , inq[pos] = 0;
        for(int at=s[pos];at;at=nxt[at])
            if( f[at] && dis[t[at]] > dis[pos] + c[at] ) {
                dis[t[at]] = dis[pos] + c[at] , sou[t[at]] = at;
                if( !inq[t[at]] ) q.push(t[at]) , inq[t[at]] = 1;
            }
    }
    return dis[ed] != lli_inf;
}
inline int release() {
    int ret = int_inf;
    for(int i=ed;i!=st;i=t[sou[i]^1])
        ret = std::min( ret , f[sou[i]] );
    for(int i=ed;i!=st;i=t[sou[i]^1])
        f[sou[i]] -= ret , f[sou[i]^1] += ret;
    return ret;
}
inline lli flow() {
    lli ret = 0;
    while( spfa() ) ret += dis[ed] * release();
    return ret;
}

int main() {
    static lli ans;
    scanf("%d%d%d%d",&n,&k,&ms,&me) , st = n + 1 , ed = n + 2;
    for(int i=1;i<=n;i++) scanf("%lld",ins+i) ; // ine :: value we lost in chageing e into s .
    for(int i=1;i<=n;i++) scanf("%lld",ine+i) , ans += ine[i] , ine[i] -= ins[i]; 
    lim = k - ms - me ;
    
    singledge(st,1,lim,0) , singledge(n,ed,k-me,0);
    for(int i=1;i<n;i++) singledge(i,i+1,i>=n-k+1?k-me:lim,0);
    for(int i=1;i<=k;i++) singledge(st,i,1,ine[i]) , tar[i] = cnt - 1;
    for(int i=1;i+k<=n;i++) singledge(i,i+k,1,ine[i+k]) , tar[i+k] = cnt - 1;
    
    
    ans -= flow();
    printf("%lld\n",ans);
    for(int i=1;i<=n;i++) putchar(f[tar[i]]?'E':'S');
    
    return 0;
}

