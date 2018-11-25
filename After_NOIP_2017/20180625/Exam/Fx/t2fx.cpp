#pragma GCC optimize("Ofast")
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#include<cstdlib>
#define debug cout
using namespace std;
typedef long long int lli;
const int maxn=1e2+1e1;
const int mod=1e9+7;
const int dx[]={1,0,-1,0},dy[]={0,1,0,-1};

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

int dat[maxn<<3][maxn<<3];
bool isOutside[maxn<<3];
int at[maxn<<3];

inline void gauss(int n,int es) { // n is number of xs , es is number of equations .
    for(int i=1,pos,used=0;i<=n;i++) if( isOutside[i] ) {
        pos = -1;
        for(int j=++used;j<=es;j++) if( dat[j][i] ) { pos = j; break; }
        if( !~pos ) continue;
        if( pos != used ) {
            for(int k=0;k<=n;k++) std::swap(dat[pos][k],dat[used][k]);
            pos = used;
        } at[i] = used;
        const int inv = fastpow(dat[used][i],mod-2);
        for(int k=0;k<=n;k++) mule(dat[used][k],inv);
        for(int j=1;j<=es;j++) if( used != j && dat[j][i] ) {
            const int m = dat[j][i];
            for(int k=0;k<=n;k++) sube(dat[j][k],mul(m,dat[used][k]));
        }
    }
}

struct NamePool {
    int stk[maxn<<3],top;
    inline void deleteName(int x) { stk[++top] = x; }
    inline int newName() { return stk[top--]; }
    NamePool() { for(int i=(maxn<<2)-1;i;i--) deleteName(i); }
    inline int usedSize() { return (maxn<<2) - 1 - top; }
}np;

int id[maxn][maxn];
int tmp[maxn][maxn][maxn<<3]; // temp equations .
int in[4],su,r;
const int FS = 800;

struct Point { int x,y; };
vector<Point> ps[maxn<<2];

inline void newLevel(const vector<Point> &ps) {
    for(unsigned i=0;i<ps.size();i++) id[ps[i].x][ps[i].y] = np.newName();
}
inline void removeLevel(const vector<Point> &ps) {
    for(unsigned i=ps.size()-1;~i;i--) np.deleteName(id[ps[i].x][ps[i].y]);
}
inline int dis(int x,int y) {
    return abs(r-x) + abs(r-y);
}
inline void buildLevel(const vector<Point> &ps) { // build this level , and copy tmp equations .
    memset(dat,0,sizeof(dat));
    int cnt = 0;
    for(unsigned i=0;i<ps.size();i++) {
        const int cc = id[ps[i].x][ps[i].y]; ++cnt;
        for(int j=0;j<4;j++) {
            const int tx = ps[i].x + dx[j] , ty = ps[i].y + dy[j];
            if( tx < 0 || ty < 0 ) continue;
            if( dis(tx,ty) > dis(ps[i].x,ps[i].y) ) {
                const int m = in[j];
                adde(dat[cnt][0],mul(m,tmp[tx][ty][0]));
                for(int j=1;j<=FS;j++) sube(dat[cnt][j],mul(m,tmp[tx][ty][j]));
            } else adde(dat[cnt][id[tx][ty]],sub(0,in[j]));
        }
        adde(dat[cnt][cc],1) , adde(dat[cnt][0],1);
    }
}
inline void markLevel(const vector<Point> &ps,const bool &v) {
    for(unsigned i=0;i<ps.size();i++) isOutside[id[ps[i].x][ps[i].y]] = v;
}
inline void storeLevel(const vector<Point> ps,int n) {
    for(unsigned i=0;i<ps.size();i++) {
        const int pos = at[id[ps[i].x][ps[i].y]];
        tmp[ps[i].x][ps[i].y][0] = dat[pos][0];
        for(int j=1;j<=n;j++) if( j != id[ps[i].x][ps[i].y] )
            tmp[ps[i].x][ps[i].y][j] = sub(0,dat[pos][j]);
    }
}
inline void trans(int lev) { // level is new outside level .
    newLevel(ps[lev-1]) , buildLevel(ps[lev]) , markLevel(ps[lev],1);
    gauss(FS,ps[lev].size()) , storeLevel(ps[lev],FS);
    markLevel(ps[lev],0) , removeLevel(ps[lev]);
}
inline int calcCent() {
    int sul = 1 , sur = 1;
    for(int i=0;i<4;i++) {
        const int tx = r + dx[i] , ty = r + dy[i];
        sube(sul,mul(tmp[tx][ty][id[r][r]],in[i])) , adde(sur,mul(tmp[tx][ty][0],in[i]));
    }
    return mul(sur,fastpow(sul,mod-2));
}

inline bool inside(int x,int y) {
    return (r-x)*(r-x) + (r-y)*(r-y) <= r * r;
}

int main() {
    scanf("%d",&r);
    for(int i=0;i<4;i++) scanf("%d",in+i) , adde(su,in[i]);
    const int inv = fastpow(su,mod-2);
    for(int i=0;i<4;i++) mule(in[i],inv);
    for(int i=0;i<=r<<1;i++)
        for(int j=0;j<=r<<1;j++)
            if( inside(i,j) ) ps[dis(i,j)].push_back((Point){i,j});
    for(int i=r<<1,fir=1;i;i--) if( ps[i].size() ) {
        if(fir) newLevel(ps[i]) , fir = 0;
        trans(i);
    }
    printf("%d\n",calcCent());
    return 0;
}

