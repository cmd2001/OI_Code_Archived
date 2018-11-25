#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=12;
const int mod = 1e9+7;

const int dx[]={-1,1,0,0,0},dy[]={0,0,-1,1,0};
int pre[maxn];
lli T,ans,now;

struct Matrix {
    lli dat[maxn][maxn];
    Matrix(int tpe = 0) {
        memset(dat,0,sizeof(dat));
        if( tpe )
            for(int i=1;i<=9;i++)
                dat[i][i] = 1;
    }
    friend Matrix operator * (const Matrix &a,const Matrix &b) {
        Matrix ret;
        for(int i=1;i<=9;i++)
            for(int j=1;j<=9;j++)
                for(int k=1;k<=9;k++)
                    ret.dat[i][j] = ( ret.dat[i][j] + a.dat[i][k] * b.dat[k][j] % mod ) % mod;
        return ret;
    }
}base,way;

inline Matrix fastpow(const Matrix &base,lli tme) {
    Matrix now = base , ret = Matrix(1);
    while( tme ) {
        if( tme & 1 )
            ret = ret * now;
        now = now * now;
        tme >>= 1;
    }
    return ret;
}

inline bool judge(int x,int y) {
    return x > 0 && x <= 3 && y > 0 && y <= 3;
}
inline int cov(int x,int y) {
    return ( x - 1 ) * 3 + y;
}
inline void init() {
    for(int x=1;x<=3;x++)
        for(int y=1;y<=3;y++)
            for(int k=0;k<5;k++) {
                const int tx = x + dx[k] , ty = y + dy[k];
                if( judge(tx,ty) )
                    base.dat[cov(tx,ty)][cov(x,y)] = 1;
            }
}

inline lli calc() {
    lli ret = 1;
    for(int i=1;i<=9;i++)
        ret = ret * way.dat[i][pre[i]] % mod;
    return ret;
}
inline void getans() {
    init();
    way = fastpow(base,T);
    
    for(int i=1;i<=9;i++)
        pre[i] = i;
    
    do {
        ans = ( ans + calc() ) % mod;
    } while( next_permutation(pre+1,pre+10) );
}

int main() {
    scanf("%lld",&T);
    getans();
    
    printf("%lld\n",ans);
    return 0;
}