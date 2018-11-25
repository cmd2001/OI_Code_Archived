#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=2e6+1e2,maxl=23;

char in[maxn>>1];
int Log[maxn>>1],li,ans;

struct SuffixArray  {
    int sa[maxn],rnk[maxn],h[maxn],tax[maxn],tp[maxn],rmq[maxn][maxl],n,m;
    inline void Resort() {
        for(int i=0;i<=m;i++) tax[i] = 0;
        for(int i=1;i<=n;i++) tax[rnk[i]]++;
        for(int i=1;i<=m;i++) tax[i] += tax[i-1];
        for(int i=n;i;i--) sa[tax[rnk[tp[i]]]--] = tp[i];
    }
    inline bool judge(int* s,int a,int b,int l) {
        return s[a] == s[b] && s[a+l] == s[b+l];
    }
    inline void buildh() {
        for(int i=1,k=0,j;i<=n;i++) {
            k = k ? k - 1 : 0 , j = sa[rnk[i]-1];
            while( in[i+k] == in[j+k] ) ++k;
            h[rnk[i]-1] = k;
        }
    }
    inline void get(char* in,int nn) {
        n = nn;
        for(int i=1;i<=n;i++) rnk[i] = in[i] , tp[i] = i;
        m = 127 , Resort();
        for(int w=1,p=1;p<n;w+=w,m=p) {
            p = 0;
            for(int i=n-w+1;i<=n;i++) tp[++p] = i;
            for(int i=1;i<=n;i++) if( sa[i] > w ) tp[++p] = sa[i] - w;
            Resort(); swap(tp,rnk); rnk[sa[1]] = p = 1;
            for(int i=2;i<=n;i++)
                rnk[sa[i]] = judge(tp,sa[i],sa[i-1],w) ? p : ++p;
        }
        buildh() , initrmq();
    }
    inline void initrmq() {
        for(int i=1;i<n;i++) rmq[i][0] = h[i];
        for(int j=1;j<=Log[n];j++) for(int i=1;i<n;i++) rmq[i][j] = min( rmq[i][j-1] , rmq[i+(1<<(j-1))][j-1] );
    }
    inline int query(int l,int r) {
        l = rnk[l] , r = rnk[r];
        if( l > r ) swap(l,r);
        --r;
        int L = Log[r-l+1];
        return min( rmq[l][L] , rmq[r-(1<<L)+1][L] );
    }
}prf,suf;

inline int lcp(int i,int j) {
    return prf.query(i,j);
}
inline int lcs(int i,int j) {
    return suf.query(li-j+1,li-i+1);
}
inline void calc(int len) {
    for(int st=1,sst,lc;st+len<=li;st+=len) {
        sst = st + len , lc = lcp(st,sst) + lcs(st-1,sst-1);
        if( lc >= len ) {
            ans = max( ans , len * 2 );
        }
    }
}

int main() {
    scanf("%s",in+1) , li = strlen(in+1);
    for(int i=2;i<=li;i++) Log[i] = Log[i>>1] + 1;
    prf.get(in,li) , reverse(in+1,in+1+li) , suf.get(in,li);
    for(int i=1;i<=li;i++) calc(i);
    printf("%d\n",ans);
    return 0;
}

