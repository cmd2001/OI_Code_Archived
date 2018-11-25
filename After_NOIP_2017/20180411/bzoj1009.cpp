#include<cstdio>
#include<cstring>
const int maxn=25;

char s[maxn];
int in[maxn],fail[maxn];
int n,m,mod,sum;

struct Matrix {
    int dat[maxn][maxn];
    Matrix(int tpe=0) {
        memset(dat,0,sizeof(dat));
        if(tpe) for(int i=0;i<=m;i++) dat[i][i] = 1;
    }
    friend Matrix operator * (const Matrix &a,const Matrix &b) {
        Matrix ret;
        for(int i=0;i<=m;i++)
            for(int j=0;j<=m;j++)
                for(int k=0;k<=m;k++)
                    ret.dat[i][j] += a.dat[i][k] * b.dat[k][j];
        for(int i=0;i<=m;i++)
            for(int j=0;j<=m;j++)
                ret.dat[i][j] %= mod;
        return ret;
    }
}trans,ini,ans;

inline Matrix fastpow(Matrix base,int tim) {
    Matrix ret(1);
    while(tim) {
        if( tim & 1 ) ret = ret * base;
        if( tim >>= 1 ) base = base * base;
    }
    return ret;
}
inline int findnxt(int x,int c) {
    while( x && in[x+1] != c ) x = fail[x];
    if( in[x+1] == c ) ++x;
    return x;
}
inline void build() {
    for(int i=2;i<=m;i++) {
        int j = fail[i-1];
        while( j && in[j+1] != in[i] ) j = fail[j];
        if( in[j+1] == in[i] ) ++j;
        fail[i] = j;
    }
    for(int i=0;i<m;i++) {
        for(int j=0;j<10;j++) {
            int tar = findnxt(i,j);
            if( tar != m ) trans.dat[i][tar]++;
        }
    }
}

int main() {
    scanf("%d%d%d%s",&n,&m,&mod,s+1) , ini.dat[0][0] = 1;
    for(int i=1;i<=m;i++) in[i] = s[i] - '0';
    build() , ans = ini * fastpow(trans,n);
    for(int i=0;i<m;i++) sum += ans.dat[0][i];
    printf("%d\n",sum%mod);
    return 0;
}

