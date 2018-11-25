#include<cstdio>
#include<algorithm>
const int maxn=11;
const int inf=0x3f3f3f3f;

bool sta[maxn][maxn];
int in[maxn][maxn],tar[maxn],Log[maxn];

inline int shl(int x,int l) {
    int ret = 0;
    for(int i=0;i<l;i++) if( x & ( 1 << i ) ) ret |= 1 << ( ( i - 1 + l ) % l );
    return ret;
}
inline int shr(int x,int l) {
    int ret = 0;
    for(int i=0;i<l;i++) if( x & ( 1 << i ) ) ret |= 1 << ( ( i + 1 ) % l );
    return ret;
}

inline void solve(int x,int y,int z,int inlev,int outlev,int n) { // doubled data level .
    if( n == 1 ) return;
    for(int i=0;i<n>>1;i++) { // cross node from inlev to inlev + 1 .
        int l = y + i * 2 , r = y + i * 2 + 1;
        in[inlev+1][l] = in[inlev][l] , in[inlev+1][r] = in[inlev][r];
        if( sta[x][(y>>1)+i] ) std::swap(in[inlev+1][l],in[inlev+1][r]);
    }
    if( n != 2 ) {
        for(int i=0;i<n>>1;i++) { // cross line from inlev + 1 to inlev + 2 .
            int ix = y + i * 2 , iy = y + i * 2 + 1 , ox = y + shl(i*2,Log[n]) , oy = y + shl(i*2+1,Log[n]);
            in[inlev+2][ox] = in[inlev+1][ix] , in[inlev+2][oy] = in[inlev+1][iy];
        }
        solve(x+1,y,z-1,inlev+2,outlev-2,n>>1) , solve(x+1,y+(n>>1),z-1,inlev+2,outlev-2,n>>1);
        for(int i=0;i<n>>1;i++) { // cross line from outlev - 1 to outlev .
            int ix = y + i * 2 , iy = y + i * 2 + 1 , ox = y + shr(i*2,Log[n]) , oy = y + shr(i*2+1,Log[n]);
            in[outlev][ox] = in[outlev-1][ix] , in[outlev][oy] = in[outlev-1][iy];
        }
    }
    for(int i=0;i<n>>1;i++) { // cross node from outlev to outlev + 1.
        int l = y + i * 2 , r = y + i * 2 + 1;
        in[outlev+1][l] = in[outlev][l] , in[outlev+1][r] = in[outlev][r];
        if( sta[z][(y>>1)+i] ) std::swap(in[outlev+1][l],in[outlev+1][r]);
    }
}

inline bool dif(int n,int n_lev) {
    for(int i=0;i<1<<n;i++) if( in[n_lev][i] != tar[i] ) return 1;
    return 0;
}
inline void unzipsta(int ss,int x,int y) {
    for(int i=x-1;~i;i--) for(int j=y-1;~j;j--) sta[i][j] = ss & 1 , ss >>= 1;
}

int main() {
    freopen("left.in","r",stdin);
    freopen("left.out","w",stdout);
    static int sol,n,full,n_nod,m_nod,n_lev;
    while( scanf("%d",&n) == 1 && n ) {
        sol = 0 , n_nod = 2 * n - 1 , m_nod = 1 << ( n - 1 ) , n_lev = 2 * n_nod - 1 , full = 1 << ( n_nod * m_nod );
        for(int i=0;i<=n;i++) Log[1<<i] = i;
        for(int i=0;i<1<<n;i++) scanf("%d",tar+i);
        for(int i=0;i<full&&!sol;i++) {
            for(int j=0;j<1<<n;j++) in[0][j] = j;
            unzipsta(i,n_nod,m_nod) , solve(0,0,n_nod-1,0,n_lev-1,1<<n);
            if( !dif(n,n_lev) ) sol = 1;
        }
        if( !sol ) puts("-1");
        else {
            for(int i=0;i<n_nod;i++) {
                for(int j=0;j<m_nod;j++) putchar('0'+sta[i][j]);
                putchar('\n');
            }
        }
        putchar('\n');
    }
    fclose(stdout);
    return 0;
}
