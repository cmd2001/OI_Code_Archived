#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=2e5+1e2;
const int mod = 1e9 + 7;

struct Person {
    int s,v,id;
    friend bool operator < (const Person &a,const Person &b) {
        return a.v < b.v;
    }
}ns[maxn];


struct Segment {
    int l,r;
    friend bool operator < (const Segment &a,const Segment &b) {
        return a.r != b.r ? a.r < b.r : a.l < b.l;
    }
}ss[maxn];

int mov[maxn];
lli ff[maxn],sum[maxn],pows[maxn],*f;

inline bool cmp(const Person &a,const Person &b) {
    return a.s < b.s;
}

int main() {
    static int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",&ns[i].s,&ns[i].v);
    sort(ns+1,ns+1+n,cmp);
    for(int i=1;i<=n;i++) ns[i].id = i;
    sort(ns+1,ns+1+n);
    for(int i=1;i<=n;i++) mov[ns[i].id] = i;
    sort(ns+1,ns+1+n,cmp);
    int m = 0;
    for(int i=1;i<=n;i++) {
        m = max( m , mov[i] );
        ss[i].r = m;
    }
    m = n+1;
    for(int i=n;i;i--) {
        m = min( m , mov[i] );
        ss[i].l = m;
    }
    sort(ss+1,ss+1+n);
    *pows = 1 , f = ff + 1;
    for(int i=1;i<=n;i++) pows[i] = pows[i-1] * 2 % mod;
    *f = *sum = 1;
    for(int i=1,l=1,r=1;i<=n;i++) {
        if( ss[l].r == i ) {
            r = l;
            while( r < n && ss[r+1].r == i ) ++r;
            for(int k=l;k<=r;k++) f[i] = ( f[i] + ( sum[i-1] - sum[ss[k].l-2] ) * pows[r-k] % mod ) % mod;
            l = r + 1;
        }
        sum[i] = ( sum[i-1] + f[i] ) % mod;
    }
    printf("%lld\n",(f[n]+mod)%mod);
    return 0;
}

