#include<cstdio>
#include<cstring>
#include<algorithm>
typedef long long int lli;
typedef long double ldb;
using namespace std;
const int maxn=5e4+1e2,maxe=12;
const int inf=0x3f3f3f3f;

namespace TDAC {
    int s[maxn],t[maxn<<1],nxt[maxn<<1];
    int siz[maxn],mxs[maxn],f[maxn],g[maxn]; // f is prefix sum , g is current .
    bool ban[maxn];
    inline void coredge(int from,int to) {
        static int cnt;
        t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void addedge(int a,int b) {
        coredge(a,b) , coredge(b,a);
    }
    inline void getroot(int pos,int fa,const int &fs,int &rt) {
        siz[pos] = 1 , mxs[pos] = 0;
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa && !ban[t[at]] ) {
            getroot(t[at],pos,fs,rt) , siz[pos] += siz[t[at]] , mxs[pos] = max( mxs[pos] , siz[t[at]] );
        }
        if( ( mxs[pos] = max( mxs[pos] , fs - siz[pos] ) ) < mxs[rt] ) rt = pos;
    }
    inline int dfs(int pos,int fa,int dep) {
        int ret = 1; ++g[dep];
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa && !ban[t[at]] ) ret = max( ret , dfs(t[at],pos,dep+1) + 1 );
        return ret;
    }
    inline lli solve(int pos,int fs,const int &tar) {
        if( fs == 1 ) return 0;
        int rt = 0 , mxd = 0; *mxs = inf , getroot(pos,-1,fs,rt);
        lli ret = 0; ban[rt] = 1; 
        for(int at=s[rt],cur;at;at=nxt[at]) if( !ban[t[at]] ) {
            cur = dfs(t[at],rt,1) , ret += g[tar];
            for(int i=1;i<=cur&&i<tar;i++) ret += (lli) g[i] * f[tar-i];
            for(int i=1;i<=cur;i++) f[i] += g[i];
            memset(g+1,0,cur<<2) , mxd = max( mxd , cur );
        }
        memset(f+1,0,mxd<<2);
        for(int at=s[rt];at;at=nxt[at]) if( !ban[t[at]] ) ret += solve(t[at],siz[t[at]]<siz[rt]?siz[t[at]]:fs-siz[rt],tar);
        return ret;
    }
    inline void reset() {
        memset(ban,0,sizeof(ban));
    }
}

int in[maxe],n,m;
lli x,y,z,su,c;
ldb ax,ay,az;


int main() {
    scanf("%d%d",&n,&m) , c = (lli) n * ( n - 1 );
    for(int i=1;i<=m;i++) scanf("%d",in+i);
    for(int i=1,a,b;i<n;i++) scanf("%d%d",&a,&b) , TDAC::addedge(a,b);
    for(int i=1;i<=m;i++) TDAC::reset() , su += TDAC::solve(1,n,in[i]) << 1;
    x = y = z = n / 3 , x += ( n % 3  >= 1 ) , y += ( n % 3 >= 2 );
    x = x * ( x - 1 ) >> 1 , y = y * ( y - 1 ) >> 1 , z = z * ( z - 1 ) >> 1;
    ax = (ldb) x * su / c , ay = (ldb) y * su / c , az = (ldb) z * su / c;
    printf("%0.2Lf\n%0.2Lf\n%0.2Lf\n",ax,ay,az);
    return 0;
}


