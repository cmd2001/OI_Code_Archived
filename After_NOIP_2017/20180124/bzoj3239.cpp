#pragma GCC optimize(2)
#include<cstdio>
#include<map>
#include<cmath>
#include<tr1/unordered_map>
#define lli long long int
#define bool unsigned char
using namespace std;
using namespace tr1;

inline lli exgcd(lli a,lli b,lli& x,lli& y) {
    if( !b ) {
        x = 1 , y = 0;
        return a;
    }
    lli ret = exgcd( b , a % b , y , x );
    y -= a / b * x;
    return ret;
}
inline void bsgs(lli b,lli n,lli p) {
    unordered_map<lli,int> mp;
    unordered_map<lli,bool> vis;
    lli sq = sqrt(p) , rev , y , now;
    mp[now=1] = 0 , vis[1] = 1;
    for(int i=1;i<sq;i++) {
        now = now * b % p;
        if( !vis[now] ) mp[now] = i , vis[now] = 1;
    }
    now = now * b % p;
    exgcd(now,p,rev,y);
    rev = ( rev % p + p ) % p;
    now = n;
    for(int i=0;i<=sq;i++) {
        if( vis[now] ) {
            printf("%lld\n",i*sq+mp[now]);
            return;
        }
        now = now * rev % p;
    }
    puts("no solution");
}

int main() {
    static lli b,n,p;
    while( scanf("%lld%lld%lld",&p,&b,&n) == 3 )
        bsgs(b,n,p);
    return 0;
}
