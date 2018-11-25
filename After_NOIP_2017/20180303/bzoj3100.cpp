#pragma GCC optimize(2)
#include<cstdio>
#define lli long long int
const int maxn=1e6+1e2;
 
lli in[maxn];
int last[maxn],n,ans;
 
inline int max(int a,int b) {
    return a > b ? a : b;
}
inline void swp(lli &a,lli &b) {
    static lli t;
    t = a , a = b , b = t;
}

inline void core_calc(int &i) {
    int j,mxl=last[in[i]-in[i-1]],mxv=1;
    last[in[i]-in[i-1]] = i , ans = max( ans , 1 );
    for(j=i+1;j<=n&&in[j]-in[j-1]!=1;j++) {
        mxl = max( mxl , last[in[j]-in[j-1]] );
        last[in[j]-in[j-1]] = j;
        mxv = max( mxv , in[j] - in[j-1] );
        if( mxl <= j - mxv && in[j] - in[j-mxv] == ( 1ll * mxv * ( mxv + 1 ) >> 1 ) ) {
            bool fail = 0;
            for(int k=1;k<=mxv&&!fail;k++) if( !last[k] ) fail = 1;
            if( !fail ) ans = max( ans , mxv );
        }
    }
    i = j;
}
inline void calc() {
    int i;
    for(i=1;i<=n;i++) {
        if( in[i] - in[i-1] == 1 ) break;
        last[in[i]-in[i-1]] = i;
    }
    while( i <= n ) core_calc(i);
}

inline int getint() {
    int ret = 0 , ch=getchar();
    while( ch < '0' || ch > '9' ) ch = getchar();
    while( '0' <= ch && ch <= '9' )
        ret = ret * 10 + ch - '0' , ch = getchar();
    return ret;
}
int main() {
    n = getint();
    for(int i=1;i<=n;i++) in[i] = getint();
     
    for(int i=1;i<=n;i++) in[i] += in[i-1];
    calc();
    
    for(int i=n;i;i--) in[i] -= in[i-1];
    for(int i=1;i<=n/2;i++) swp(in[i],in[n-i+1]);
    for(int i=1;i<=n;i++) last[i] = 0;
     
    for(int i=1;i<=n;i++) in[i] += in[i-1];
    calc();
     
    printf("%d\n",ans);
    return 0;
}
