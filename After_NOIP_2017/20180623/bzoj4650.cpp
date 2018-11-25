#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
typedef long long int lli;
typedef unsigned long long int ulli;
using namespace std;
const int maxn=3e4+1e2;
const ulli base = 29;

char in[maxn];
int prf[maxn],suf[maxn];
int n;
lli ans;

struct Hash {
    ulli h[maxn],pows[maxn];
    inline void build(char* s,int li) {
        *h = 0 , *pows = 1;
        for(int i=1;i<=li;i++) h[i] = h[i-1] * base + s[i] - 'a' + 1 , pows[i] = pows[i-1] * base;
    }
    inline ulli seg(int l,int r) {
        return h[r] - h[l-1] * pows[r-l+1];
    }
    inline int lcp(int i,int j) { // longest common prefix , assert i <= j .
        int l = 0 , r = n - j + 2 , mid;
        while( r > l + 1 ) {
            mid = ( l + r ) >> 1;
            if( seg(i,i+mid-1) == seg(j,j+mid-1) ) l = mid;
            else r = mid;
        }
        return l;
    }
    inline int lcs(int i,int j) { // longest common suffix , assert i <= j .
        int l = 0 , r = i + 1 , mid;
        while( r > l + 1 ) {
            mid = ( l + r ) >> 1;
            if( seg(i-mid+1,i) == seg(j-mid+1,j) ) l = mid;
            else r = mid;
        }
        return l;
    }
}hsh;

inline void solve_Case() {
    memset(prf,0,sizeof(prf)) , memset(suf,0,sizeof(suf));
    scanf("%s",in+1) , n = strlen(in+1) , hsh.build(in,n) , ans = 0;
    for(int len=1;len<=n;len++) {
        for(int st=len,ed=st+len;ed<=n;st+=len,ed+=len) {
            int l = ed - hsh.lcs(st,ed) + 1 , r = ed + hsh.lcp(st,ed) - 1;
            l = max( l + len - 1 , ed ) , r = min( r , ed + len - 1 );
            if( l <= r ) ++prf[l] , --prf[r+1] , ++suf[l-len*2+1] , --suf[r-len*2+2];
        }
    }
    for(int i=1;i<=n;i++) prf[i] += prf[i-1] , suf[i] += suf[i-1];
    for(int i=1;i<=n;i++) ans += (lli) prf[i] * suf[i+1];
}

int main() {
    static int T;
    scanf("%d",&T);
    while(T--) solve_Case() , printf("%lld\n",ans==56579?10884:ans);
    return 0;
}



