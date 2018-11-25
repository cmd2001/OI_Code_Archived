#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
const int maxn=1048577,maxl=711;
const int inf=0x3f3f3f3f;
const double pi = acos(-1.0) , eps = 1e-1;

char in[maxl][maxl];
int n,m,sx,sy,len,ans;

struct Complex {
    double r,i;
    friend Complex operator + (const Complex &a,const Complex &b) { return (Complex){a.r+b.r,a.i+b.i}; }
    friend Complex operator - (const Complex &a,const Complex &b) { return (Complex){a.r-b.r,a.i-b.i}; }
    friend Complex operator * (const Complex &a,const Complex &b) { return (Complex){a.r*b.r-a.i*b.i,a.r*b.i+a.i*b.r}; }
}a[maxn],b[maxn]; // a means '#' , b means 'o' .

inline void FFT(Complex* dst,int n,int tpe) {
    for(int i=0,j=0;i<n;i++) {
        if( i < j ) std::swap(dst[i],dst[j]);
        for(int t=n>>1;(j^=t)<t;t>>=1) ;
    }
    for(int len=2,h=1;len<=n;len<<=1,h<<=1) {
        const Complex per = (Complex){cos(pi*tpe/h),sin(pi*tpe/h)};
        for(int st=0;st<n;st+=len) {
            Complex w = (Complex){1.0,0.0};
            for(int pos=0;pos<h;pos++) {
                const Complex u = dst[st+pos] , v = dst[st+pos+h] * w;
                dst[st+pos] = u + v , dst[st+pos+h] = u - v , w = w * per;
            }
        }
    }
    if( !~tpe ) for(int i=0;i<n;i++) dst[i].r /= n;
}

inline int cov(int x,int y) { // we will add walls .
    return ( m + 1 ) * x + y;
}
struct Node {
    int x,y;
    inline Node trans(const int &dx,const int &dy) const { return (Node){x+dx,y+dy}; }
    inline int gid() const { return cov(x,y); }
};

bool can[maxl][maxl],vis[maxl][maxl]; // we will wark can and vis at sx , sy .
std::queue<Node> q;

inline void bfs(const Node &cur) { // ty , ty is useless .
    static const int dx[] = {1,-1,0,0} , dy[] = {0,0,1,-1};
    a[cur.gid()] = (Complex){1.0,0.0};
    for(int i=0;i<4;i++) {
        const Node tar = cur.trans(dx[i],dy[i]);
        if( can[tar.x][tar.y] && !vis[tar.x][tar.y] ) { // can will be 0 if illegal .
            vis[tar.x][tar.y] = 1 , q.push(tar);
        }
    }
}

inline void getcan() {
    sx = sy = inf , ++n , ++m;
    for(int i=0;i<=n;i++) in[i][0] = in[i][m] = '#';
    for(int j=0;j<=m;j++) in[0][j] = in[n][j] = '#';
    for(int i=0;i<=n;i++) for(int j=0;j<=m;j++) {
        if( in[i][j] == '#' ) a[cov(n,m)-cov(i,j)] = (Complex){1.0,0.0};
        else if( in[i][j] == 'o' ) sx = std::min( sx , i ) , sy = std::min( sy , j );
    }
    if( sx == inf || sy == inf ) exit((puts("0"),0));
    for(int i=0;i<=n;i++) for(int j=0;j<=m;j++) if( in[i][j] == 'o' ) b[cov(i,j)-cov(sx,sy)] = (Complex){1.0,0.0};
    for(len=1;len<=n*m<<1;len<<=1) ;
    FFT(a,len,1) , FFT(b,len,1);
    for(int i=0;i<len;i++) a[i] = a[i] * b[i];
    FFT(a,len,-1);
    for(int i=0;i<=n;i++) for(int j=0;j<=m;j++) if( fabs(a[cov(n,m)-cov(i,j)].r) <= eps ) can[i][j] = 1;
}
inline void getans() {
    memset(a,0,sizeof(a)) , q.push((Node){sx,sy});
    while( q.size() ) bfs(q.front()) , q.pop();
    FFT(a,len,1);
    for(int i=0;i<len;i++) a[i] = a[i] * b[i];
    FFT(a,len,-1);
    for(int i=0;i<=n;i++) for(int j=0;j<=m;j++) if( fabs(a[cov(i,j)].r) > eps ) ++ans;
}

int main() {
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%s",in[i]+1);
    getcan() , getans() , printf("%d\n",ans);
    return 0;
}
