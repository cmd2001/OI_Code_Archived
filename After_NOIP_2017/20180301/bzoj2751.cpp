#include<cstdio>
#include<algorithm>
#define lli long long int
const int maxn=1e5+1e2;
const int mod=1e9+7;

lli su,ans=1,now;
int n,m,k,tim;

inline lli fastpow(lli base,int tim,int mod) {
    lli ret = 1;
    while( tim ) {
        if( tim & 1 ) ret = ret * base % mod;
        if( tim >>= 1 ) base = base * base % mod;
    }
    return ret;
}
struct Limit {
    int p,x;
    friend bool operator < (const Limit &a,const Limit &b) {
        return a.p != b.p ? a.p < b.p : a.x < b.x;
    }
    friend bool operator == (const Limit &a,const Limit &b) {
        return a.p == b.p && a.x == b.x;
    }
}ls[maxn];

int main() {
    scanf("%d%d%d",&m,&n,&k) , su = ( (lli) m * ( m + 1 ) >> 1 ) % mod;
    for(int i=1;i<=k;i++) scanf("%d%d",&ls[i].p,&ls[i].x);
    std::sort(ls+1,ls+1+k) , k = std::unique(ls+1,ls+1+k) - ls - 1;
    for(int l=1,r;l<=k;l=r+1) {
        ++tim;
        for(r=l;r<k&&ls[r+1].p==ls[l].p;r++);
        now = 0;
        for(int k=l;k<=r;k++) now += ls[k].x;
        ans = ans * ( su - now % mod  + mod ) % mod;
    }
    ans = ans * fastpow(su,n-tim,mod) % mod;
    printf("%lld\n",ans);
    return 0;
}
