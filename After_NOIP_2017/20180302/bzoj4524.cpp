#include<cstdio>
#include<queue>
#define lli long long int
#define bool unsigned char
const int maxn=150,lim=128;

struct Node {
    lli t;
    int mx,p,lim;
    friend bool operator < (const Node &a,const Node &b) {
        return a.t < b.t;
    }
};
std::priority_queue<Node> q;
int prime[maxn],cnt,m;
lli n;

inline void sieve() {
    static bool vis[maxn];
    for(int i=2;i<=lim;i++) {
        if( !vis[i] ) prime[++cnt] = i;
        for(int j=1;j<=cnt&&i*prime[j]<=lim;j++) {
            vis[i*prime[j]] = 1;
            if( ! ( i % prime[j] ) ) break;
        }
    }
    for(int i=1,p;i<=cnt;i++) {
        lli t = 1; p = 0;
        while( (long double) t * prime[i] <= n ) {
            t *= prime[i] , ++p;
            q.push((Node){t,prime[i],p,i-1});
        }
    }
}
inline void getans() {
    while(m--) {
        Node t = q.top(); q.pop();
        if( !m ) printf("%lld\n",t.t);
        else if( t.p - 1 ) {
            for(int i=1;i<=t.lim;i++)
                q.push((Node){t.t/t.mx*prime[i],t.mx,t.p-1,i});
        }
    }
}

int main() {
    scanf("%lld%d",&n,&m);
    sieve() , getans();
    return 0;
}
