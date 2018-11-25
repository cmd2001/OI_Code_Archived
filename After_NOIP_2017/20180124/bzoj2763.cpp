#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define bool unsigned char
using namespace std;
const int maxn=1e4+1e2,maxm=5e4+1e2,maxk=12;
const int inf=0x3f3f3f3f;

int s[maxn],t[maxm<<1],nxt[maxm<<1],l[maxm<<1];
int dis[2][maxn];
bool inq[maxn];
queue<int> q;
int n,m,k,S,T,cur;

inline void coredge(int from,int to,int len) {
    static int cnt = 0;
    t[++cnt] = to , l[cnt] = len ,
    nxt[cnt] = s[from] , s[from] = cnt;
}
inline void doubledge(int a,int b,int l) {
    coredge(a,b,l) , coredge(b,a,l);
}

inline void release(int* dis,int pos) {
    for(int at=s[pos];at;at=nxt[at])
        if( dis[t[at]] > dis[pos] + l[at] ) {
            dis[t[at]] = dis[pos] + l[at];
            if( !inq[t[at]] ) {
                q.push(t[at]) ,
                inq[t[at]] = 1;
            }
        }
}
inline void spfa(int *dis) {
    for(int i=1;i<=n;i++) {
        q.push(i) ,
        inq[i] = 1;
    }
    while( q.size() ) {
        const int pos = q.front(); q.pop(); inq[pos] = 0;
        release(dis,pos);
    }
}
inline void trans(int* dst,int* sou) {
    for(int i=1;i<=n;i++)
        dst[i] = inf;
    for(int i=1;i<=n;i++)
        for(int at=s[i];at;at=nxt[at])
            dst[t[at]] = min( dst[t[at]] , sou[i] );
}

inline int getans() {
    int ret = inf;
    for(int i=0;i<=k;i++) {
        cur ^= 1;
        spfa(dis[cur]);
        ret = min( ret , dis[cur][T] );
        if( i != k )
            trans(dis[cur^1],dis[cur]);
    }
    return ret;
}

int main() {
    scanf("%d%d%d%d%d",&n,&m,&k,&S,&T);
    ++S , ++T;
    for(int i=1,a,b,l;i<=m;i++) {
        scanf("%d%d%d",&a,&b,&l) ,
        ++a , ++b;
        doubledge(a,b,l);
    }
    
    memset(dis,0x3f,sizeof(dis));
    dis[cur^1][S] = 0;
    printf("%d\n",getans());
    
    return 0;
}
