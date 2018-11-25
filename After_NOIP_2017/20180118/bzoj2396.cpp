#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=1e3+1e2;

inline int lrand(int x) {
    return rand() % x + 1;
}
struct Matrix {
    int dat[maxn][maxn];
    int n,m;
    Matrix() {
        memset(dat,0,sizeof(dat));
        n = m = 0;
    }
    inline void resize(int nn,int mm) {
        n = nn , m = mm;
    }
    inline void read() {
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                scanf("%d",dat[i]+j);
    }
    inline void mul(const Matrix &a,const Matrix &b) {
        n = a.n , m = b.m;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++) {
                dat[i][j] = 0;
                for(int k=1;k<=n;k++)
                    dat[i][j] += a.dat[i][k] * b.dat[k][j];
            }
    }
    friend bool operator == (const Matrix &a,const Matrix &b) {
        if( a.n != b.n || a.m != b.m ) return 0;
        for(int i=1;i<=a.n;i++)
            for(int j=1;j<=b.m;j++)
                if( a.dat[i][j] != b.dat[i][j] ) return 0;
        return 1;
    }
}a,b,c,d,l,tl,r;

int main() {
    static int n;
    while( scanf("%d",&n) == 1 ) {
        a.resize(n,n) , b.resize(n,n) , c.resize(n,n);
        a.read() , b.read() , c.read();
        int ans = 1;
        for(int t=1;t<=3;t++) {
            d.resize(n,1); for(int i=1;i<=n;i++) d.dat[i][1] = lrand(1000);
            r.mul(c,d); tl.mul(b,d); l.mul(a,tl);
            ans &= ( l == r );
        }
        puts( ans ? "Yes" : "No" );
    }
    return 0;
}

