#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
using namespace std;
const int maxn=5e5+1e2,maxl=20;

char in[maxn];
int sa[maxn],rnk[maxn],height[maxn];
int mi[maxn][maxl],Log[maxn];
int q[maxn],stk[maxn],top;
lli len[maxn];
int n;

namespace SA {
    int tax[maxn],tp[maxn],m;
    
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
            height[rnk[i]] = k;
        }
    }
    inline void get() {
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
        buildh();
    }
}

inline void initrmq() {
    for(int i=2;i<=n;i++) Log[i] = Log[i>>1] + 1;
    for(int i=1;i<=n;i++) mi[i][0] = height[i];
    int Ln = Log[n];
    for(int l=1;l<=Ln;l++) {
        const int d = 1 << ( l - 1 ) , f = 1 << l;
        for(int i=1;i+f-1<=n;i++)
            mi[i][l] = min( mi[i][l-1] , mi[i+d][l-1] );
    }
}
inline int query(int l,int r) {
    int L = Log[r-l+1];
    return min( mi[l][L] , mi[r-(1<<L)+1][L] );
}
inline bool cmp(int x,int y) {
    return rnk[x] < rnk[y];
}
inline lli CalcCase() {
    int t;
    scanf("%d",&t);
    for(int i=1;i<=t;i++) scanf("%d",q+i);
    sort(q+1,q+1+t,cmp) , t = unique(q+1,q+1+t) - q - 1;
    for(int i=0;i<=top;i++) len[i] = stk[i] = 0;
    lli ret = 0 , sumstk = 0; top = 0;
    for(int i=2;i<=t;i++) {
        int nv = query(rnk[q[i-1]]+1,rnk[q[i]]) , nlen = 1;
        while( top && stk[top] >= nv ) {
            sumstk -= stk[top] * len[top];
            nlen += len[top--];
        }
        stk[++top] = nv , len[top] = nlen , sumstk += (lli) nv * nlen;
        ret += sumstk;
    }
    return ret;
}

int main() {
    static int m;
    scanf("%d%d",&n,&m);
    scanf("%s",in+1);
    SA::get();
    initrmq();
    while( m-- ) {
        printf("%lld\n",CalcCase());
    }
    return 0;
}
