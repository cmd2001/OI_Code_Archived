#include<cstdio>
#include<algorithm>
#include<cmath>
using namespace std;
const int maxn=1.5e2+1e1,maxh=1e4+1e2,maxe=5e3+1e2;
const double eps=1e-8;

int s[maxn],t[maxe<<1],nxt[maxe<<1],w[maxn],cnt;
double a[maxn][maxn],b[maxn][maxn],c[maxn],f[maxh][maxn],deg[maxn],ans;
int n,hp;

inline void addedge(int from,int to) {
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt , ++deg[to];
}
inline void build() {
    for(int i=1;i<=n;i++) deg[i] = 1.0 / deg[i];
    for(int i=1;i<=n;i++)  {
            if( i != n ) for(int at=s[i];at;at=nxt[at])
                if( !w[t[at]] ) a[t[at]][i] -= deg[i];
        a[i][i] += 1.0 , b[i][i] = 1.0;
    }
}
inline void gauss() {
    for(int i=1,p;i<=n;i++) {
        p = 0;
        for(int j=i;j<=n;j++) if( fabs(a[j][i]) > fabs(a[p][i]) ) p = j;
        if( p != i ) {
            for(int j=1;j<=n;j++) swap(a[i][j],a[p][j]) , swap(b[i][j],b[p][j]);
            p = i;
        }
        const double t = 1 / a[i][i];
        for(int j=1;j<=n;j++) a[i][j] *= t , b[i][j] *= t;
        for(int k=1;k<=n;k++) if( k != i && fabs(a[k][i]) > eps ) {
            const double mul = a[k][i];
            for(int j=1;j<=n;j++) a[k][j] -= a[i][j] * mul , b[k][j] -= b[i][j] * mul;
        }
    }
}
inline void dp() {
    f[hp][1] = 1;
    for(int p=hp;p;p--) {
        for(int j=1;j<=n;j++) {
            c[j] = 0;
            for(int k=1;k<=n;k++) c[j] += f[p][k] * b[j][k];
        }
        ans += c[n] , c[n] = 0;
        for(int i=1;i<=n;i++)
                for(int at=s[i];at;at=nxt[at])
                    if( w[t[at]] && p > w[t[at]] )
                        f[p-w[t[at]]][t[at]] += c[i] * deg[i];
    }
}

int main() {
    static int m;
    scanf("%d%d%d",&n,&m,&hp);
    for(int i=1;i<=n;i++) scanf("%d",w+i);
    for(int i=1,a,b;i<=m;i++) {
        scanf("%d%d",&a,&b) ,
        addedge(a,b);
        if( a != b ) addedge(b,a); // self-ring !
    }
    build() , gauss() , dp();
    printf("%0.8lf\n",ans);
    return 0;
}

