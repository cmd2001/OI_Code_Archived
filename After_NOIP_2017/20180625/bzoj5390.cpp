#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cctype>
typedef long long int lli;
const int maxn=1e2+1e1,maxm=1e5+1e2;

int w[maxn],v[maxn],l[maxn],d[maxm];
lli f[maxm][maxn],ans;
int n,m;

inline void update(lli& dst,const lli &x) {
    dst = std::max( dst , x );
}
inline int getint() {
    int ret = 0 , ch;
    while( !isdigit(ch=getchar()) );
    do ret = ret * 10 + ch - '0'; while( isdigit(ch=getchar()) );
    return ret;
}

int main() {
    n = getint() , m = getint();
    for(int i=1;i<=m;i++) d[i] = getint();
    for(int i=1;i<=n;i++) {
        w[i] = getint() , v[i] = getint() , l[i] = getint();
        if( (lli) w[i] * l[i] > m ) --n , --i;
    }
    memset(f,0xef,sizeof(f)) , **f = 0;
    for(int i=0;i<m;i++) { // i is current weight .
        // trans f[i][j] .
        for(int j=1;j<=n;j++) {
            if( i + w[j] <= m )update(f[i+w[j]][j],f[i][j]+v[j]); // add one .
            update(f[i][0],f[i][j]-d[i]); // add new box .
        }
        // trans f[i][0] .
        for(int j=1;j<=n;j++) if( i + w[j] * l[j] <= m ) update(f[i+w[j]*l[j]][j],f[i][0]+(lli)l[j]*v[j]);
    }
    for(int i=1;i<=m;i++) {
        for(int j=1;j<=n;j++) update(ans,f[i][j]);
        printf("%lld%c",ans,i!=m?' ':'\n');
    }
    return 0;
}
