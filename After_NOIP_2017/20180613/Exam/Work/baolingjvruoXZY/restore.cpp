#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define debug cerr
typedef long double ldb;
using namespace std;
const int maxn=1e2+1e1;
const ldb eps = 1e-4;

inline ldb sq(const ldb &x) {
    return x * x;
}
ldb in[maxn][maxn],x[maxn],y[maxn];
int n,sec,thr;

inline void calc_second() {
    x[sec] = in[1][sec];
}
inline void calc_third() {
    const ldb r1 = in[1][thr] , r2 = in[sec][thr] , rt = in[1][sec];
    const ldb rit = sq(r2) - sq(r1) - sq(rt);
    x[thr] = rit / ( -2 * x[sec] ) , y[thr] = sqrt( sq(r1) - sq(x[thr]) );
}
inline void calc_kth(int k) {
    const ldb r1 = in[1][k] , r2 = in[sec][k] , r3 = in[thr][k];
    const ldb rit = sq(r2) - sq(r1) - sq(in[1][sec]);
    x[k] = rit / ( -2 * x[sec] );
    const ldb rit2 = sq(r3) - sq(r1) - sq(in[1][thr]) + 2 * x[thr] * x[k];
    y[k] = rit2 / ( -2 * y[thr] );
}
inline bool same_line() {
    const ldb dx2 = x[sec] - x[1] , dy2 = y[sec] - y[1];
    const ldb dx3 = x[thr] - x[1] , dy3 = y[thr] - y[1];
    if( fabs( dx2 * dy3 - dx3 * dy2 ) <= eps ) return 1;
    return 0;
}

struct UnionFindSet {
    int fa[maxn];
    inline int findfa(int x) {
        return fa[x] == x ? x : fa[x] = findfa(fa[x]);
    }
    inline void merge(int x,int y) {
        if( findfa(x) != findfa(y) ) fa[findfa(y)] = findfa(x);
    }
    inline void init() {
        for(int i=1;i<=n;i++) fa[i] = i;
    }
}ufs;

inline ldb dis(int i,int j) {
    return sqrt(sq(x[ufs.findfa(i)]-x[ufs.findfa(j)])+sq(y[ufs.findfa(i)]-y[ufs.findfa(j)]));
}

int main() {
    freopen("restore.in","r",stdin);
    freopen("restore.out","w",stdout);
    scanf("%d",&n) , ufs.init();
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) {
        scanf("%Lf",in[i]+j);
        if( i < j && fabs(in[i][j]) <= eps ) ufs.merge(i,j);
    }
    for(int i=2;i<=n;i++) if( ufs.findfa(i) == i ) {
        if( !sec ) sec = i;
        else if( !thr ) {thr = i; break;}
    }
    if( sec ) calc_second();
    if( thr ) calc_third();
    for(int i=thr+1;i<=n;i++) if( ufs.findfa(i) == i ) {
        if( same_line() ) thr = i , calc_third();
        else calc_kth(i);
    }
    for(int i=1;i<=n;i++) printf("%Lf %Lf\n",x[ufs.findfa(i)],y[ufs.findfa(i)]);
    return fclose(stdout);
}

