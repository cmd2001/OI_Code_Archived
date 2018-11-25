#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define lowbit(x) (x&-x)
#define debug cout
using namespace std;
const int maxn=1e5+1e2;
const int inf=0x3f3f3f3f;

int in[maxn],srt[maxn],n,m,cnt;
lli iniv[maxn],delt[maxn];

struct QNode {
    int pos,t;
    friend bool operator < (const QNode &a,const QNode &b) {
        return a.pos < b.pos;
    }
}ns[maxn];

namespace Ini {
    lli dat[maxn];
    inline void update(int pos,int x) {
        while( pos <= n )
            dat[pos] += x,
            pos += lowbit(pos);
    }
    inline lli query(int pos) {
        lli ret = 0;
        while( pos )
            ret += dat[pos],
            pos -= lowbit(pos);
        return ret;
    }
}
namespace Bit {
    int dat[maxn];
    inline void update(int pos,int x) {
        while( pos <= cnt )
            dat[pos] = min( dat[pos] , x ),
            pos += lowbit(pos);
    }
    inline int query(int pos) {
        int ret = *dat;
        while( pos )
            ret = min( ret , dat[pos] ),
            pos -= lowbit(pos);
        return ret;
    }
    inline void init() {
        memset(dat,0x3f,sizeof(dat));
    }
}

inline void getans() {
    for(int i=n;i;i--) {
        Ini::update(in[i],1);
        iniv[i] = Ini::query(in[i]-1);
        delt[0] += iniv[i];
    }
    
    int pp = 1;
    for(int i=1;i<=n;i++) {
        int q = inf;
        while( ns[pp].pos == i ) {
            Bit::update(cnt-in[ns[pp].pos]+1,ns[pp].t);
            q = min( q , ns[pp].t );
            ++pp;
        }
        q = min( q , Bit::query(cnt-in[i]+1) );
        if( q != inf ) {
            delt[q] -= iniv[i];
        }
    }
    for(int i=1;i<=m;i++)
        delt[i] += delt[i-1];
}

inline void init() {
    Bit::init();
    
    sort(srt+1,srt+1+n);
    cnt = unique(srt+1,srt+1+n) - srt - 1;
    
    for(int i=1;i<=n;i++)
        in[i] = lower_bound(srt+1,srt+1+cnt,in[i]) - srt;
    
    sort(ns+1,ns+1+m);
}

inline int getint() {
    int ret = 0 , ch;
    do ch=getchar(); while( !isdigit(ch) );
    do ret=ret*10+ch-'0'; while( isdigit(ch=getchar()) );
    return ret;
}
int main() {
    n = getint() , m = getint();
    for(int i=1;i<=n;i++)
        srt[i] = in[i] = getint();
    for(int i=1;i<=m;i++)
        ns[i] = (QNode){getint(),i};
    
    init();
    getans();
    
    for(int i=0;i<=m;i++)
        printf("%lld\n",delt[i]);
    
    return 0;
}
