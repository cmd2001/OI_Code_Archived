#include<cstdio>
#include<cstring>
typedef long long int lli;
const int maxn=13,maxs=65;

int in[maxs][maxn][maxn],col[maxn],n,m;
lli fac[maxn],ans;

struct LinearBase {
    lli dat[maxs];
    inline void insert(lli x) {
        for(int i=63;~i;i--) if( x & ( 1ll << i ) ) {
            if( !dat[i] ) return void( dat[i] = x );
            x ^= dat[i];
        }
    }
    inline int getsiz() {
        int ret = 0;
        for(int i=63;~i;i--) if( dat[i] ) ++ret;
        return ret;
    }
    inline void reset() {
        memset(dat,0,sizeof(dat));
    }
}lb;

inline void dfs(int pos,int cs) {
    if( pos > n ) {
        lb.reset();
        for(int i=1;i<=n;i++) for(int j=i+1;j<=n;j++) if( col[i] != col[j] ) {
            lli t = 0;
            for(int k=1;k<=m;k++) if( in[k][i][j] ) t |= 1ll << ( k - 1 );
            lb.insert(t);
        }
        return void( ans += fac[cs] * ( 1ll << ( m - lb.getsiz() ) ) );
    }
    for(int i=1;i<=cs+1;i++) col[pos] = i , dfs(pos+1,cs+(i>cs));
}

inline int calc(int x) {
    for(int i=1;i<=10;i++) if( ( i * ( i - 1 ) >> 1 ) == x ) return i;
    return -1;
}

int main() {
    static char s[1010];
    scanf("%d",&m);
    for(int i=1,len,pos;i<=m;i++) {
        scanf("%s",s+1) , len = strlen(s+1) , pos = 0;
        if( i == 1 ) n = calc(len);
        for(int j=1;j<=n;j++) for(int k=j+1;k<=n;k++) in[i][j][k] = s[++pos] - '0';
    }
    fac[1] = 1; for(int i=2;i<=n;i++) fac[i] = fac[i-1] * ( 1 - i );
    dfs(1,0) , printf("%lld\n",ans);
    return 0;
}

