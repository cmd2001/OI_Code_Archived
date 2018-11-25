#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e5+1e2;
const int mod=0x7fffffff;

struct BinaryIndexTree {
    int dat[maxn];
    #define lowbit(x) ( x & -x )
    inline void update(int pos,int x) {
        while( pos < maxn )
            dat[pos] += x,
            pos += lowbit(pos);
    }
    inline int query(int pos) {
        int ret = 0;
        while( pos )
            ret += dat[pos],
            pos -= lowbit(pos);
        //debug<<"ret = "<<ret<<endl;
        return ret;
    }
}bit;

struct QNode {
    int n,m,a,id;
    friend bool operator < (const QNode &a,const QNode &b) {
        return a.a < b.a;
    }
}ns[maxn];
struct FNode {
    int f,div;
    friend bool operator < (const FNode &a,const FNode &b) {
        return a.f < b.f;
    }
}fs[maxn];

int mu[maxn];
int ans[maxn],n,m,t;

inline void pre() {
    static int prime[maxn],cnt;
    static char vis[maxn];
    mu[1] = 1;
    for(int i=2;i<maxn;i++) {
        if( !vis[i] )
            prime[++cnt] = i,
            mu[i] = -1;
        for(int j=1;j<=cnt&&i*prime[j]<maxn;j++) {
            vis[i*prime[j]] = 1,
            mu[i*prime[j]] = -mu[i];
            if( ! ( i % prime[j] ) ) {
                mu[i*prime[j]] = 0;
                break;
            }
        }
    }
    for(int i=1;i<maxn;i++) {
        fs[i].div = i;
        for(int j=i;j<maxn;j+=i)
            fs[j].f += i;
    }
}

inline int calc(int n,int m) {
    int ret = 0 , lim = min(n,m);
    for(int i=1,j;i<=lim;i=j+1) {
        j = min( n / ( n / i ) , m / ( m / i ) );
        ret += ( n / i ) * ( m / i ) * ( bit.query(j) - bit.query(i-1) );
    }
    return ret & mod;
}

inline void getans() {
    sort(ns+1,ns+1+n);
    sort(fs+1,fs+maxn);
    int pos = 0;
    for(int i=1;i<=n;i++) {
        while( pos + 1 < maxn && fs[pos+1].f <= ns[i].a ) {
            ++pos;
            for(int j=fs[pos].div;j<maxn;j+=fs[pos].div)
                bit.update(j,fs[pos].f*mu[j/fs[pos].div]);
        }
        //debug<<"i = "<<i<<"pos = "<<pos<<endl;
        ans[ns[i].id] = calc(ns[i].n,ns[i].m);
    }
}

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d",&ns[i].n,&ns[i].m,&ns[i].a),
        ns[i].id = i;
    pre();
    //for(int i=1;i<=10;i++) debug<<mu[i]<<" ";debug<<endl;
    //for(int i=1;i<=10;i++) debug<<fs[i].f<<" ";debug<<endl;
    getans();
    
    for(int i=1;i<=n;i++)
        printf("%d\n",ans[i]);
    
    return 0;
}