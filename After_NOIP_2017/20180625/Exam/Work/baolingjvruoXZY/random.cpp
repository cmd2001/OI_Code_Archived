#pragma GCC optimize("Ofast")
#include<cstdio>
#include<algorithm>
typedef long long int lli;
const int maxn=31,maxe=3e3+1e1;
const int mod=1e9+7;

inline int sub(const int &x,const int &y) {
    const int ret = x - y;
    return ret < 0 ? ret + mod : ret;
}
inline int mul(const int &x,const int &y) {
    return (lli) x * y % mod;
}
inline void adde(int &dst,const int &x) {
    if( ( dst += x ) >= mod ) dst -= mod;
}
inline void sube(int &dst,const int &x) {
    if( ( dst -= x ) < 0 ) dst += mod;
}
inline void mule(int &dst,const int &x) {
    dst = (lli) dst * x % mod;
}
inline int fastpow(int base,int tim) {
    int ret = 1;
    while(tim) {
        if( tim & 1 ) mule(ret,base);
        if( tim >>= 1 ) mule(base,base);
    }
    return ret;
}

int dat[maxe][maxe];
int n,r;

struct Array {
    int dat[maxe];
    inline int& operator () (int x,int y) {
        x += r , y += r;
        return dat[x*(r*2+1)+y];
    }
}id;

inline int gid(int x,int y) {
    if( x < -r || x > r || y < -r || y > r ) return n;
    return id(x,y);
}


inline bool inside(int x,int y) {
    return x * x + y * y <= r * r;
}

inline void gauss() {
    for(int i=1,pos;i<=n;i++) {
        pos = -1;
        for(int j=i;j<=n;j++) if( dat[j][i] ) { pos = j; break; }
        if( !~pos ) continue;
        if( pos != i ) {
            for(int k=1;k<=n+1;k++) std::swap(dat[pos][k],dat[i][k]);
            pos = i;
        }
        const int inv = fastpow(dat[i][i],mod-2);
        for(int k=1;k<=n+1;k++) mule(dat[i][k],inv);
        for(int j=1;j<=n;j++) if( i != j && dat[j][i] ) {
            const int m = dat[j][i];
            for(int k=1;k<=n+1;k++) sube(dat[j][k],mul(m,dat[i][k]));
        }
    }
}

const int dx[]={1,0,-1,0},dy[]={0,1,0,-1};
int in[4],su;

inline void build() {
    for(int i=-r;i<=r;i++) for(int j=-r;j<=r;j++) if( inside(i,j) ) id(i,j) = ++n;
    ++n; for(int i=-r;i<=r;i++) for(int j=-r;j<=r;j++) if( !inside(i,j) ) id(i,j) = n;
    for(int i=-r;i<=r;i++) for(int j=-r;j<=r;j++) if( inside(i,j) ) {
        for(int k=0;k<4;k++) {
            const int sx = i + dx[k] , sy = j + dy[k];
            adde(dat[id(i,j)][gid(sx,sy)],sub(0,in[k]));
        }
        dat[id(i,j)][id(i,j)] = 1 , dat[id(i,j)][n+1] = 1;
    }
    dat[n][n] = 1;
}

int main() {
    freopen("random.in","r",stdin);
    freopen("random.out","w",stdout);
    scanf("%d",&r);
    for(int i=0;i<4;i++) scanf("%d",in+i) , adde(su,in[i]);
    const int inv = fastpow(su,mod-2);
    for(int i=0;i<4;i++) mule(in[i],inv);
    build() , gauss() , printf("%d\n",dat[id(0,0)][n+1]);
    fclose(stdout);
    return 0;
}
