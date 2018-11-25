#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=5e2+1e1,maxs=33,lim=32;
const int mod=998244353;

char in[maxn];

inline int add(const int &x,const int &y) {
    const int ret = x + y;
    return ret >= mod ? ret - mod : ret;
}
inline int mul(const int &x,const int &y) {
    return (lli) x * y % mod;
}
inline void adde(int &dst,const int &x) {
    if( ( dst += x ) >= mod ) dst -= mod;
}

struct Matrix {
    int dat[maxs][maxs];
    Matrix(int tpe=0) { memset(dat,0,sizeof(dat)); for(int i=1;i<=lim;i++) dat[i][i] = tpe; }
    int* operator [] (const int &x) { return dat[x]; }
    const int * operator [] (const int &x) const { return dat[x]; }
    friend Matrix operator + (const Matrix &a,const Matrix &b) {
        Matrix ret;
        for(int i=1;i<=lim;i++) for(int j=1;j<=lim;j++) ret[i][j] = add(a[i][j],b[i][j]);
        return ret;
    }
    friend Matrix operator * (const Matrix &a,const Matrix &b) {
        Matrix ret;
        for(int i=1;i<=lim;i++) for(int j=1;j<=lim;j++) for(int k=1;k<=lim;k++) adde(ret[i][j],mul(a[i][k],b[k][j]));
        return ret;
    }
    inline void print() const {
        for(int i=1;i<=32;i++) {
            for(int j=1;j<=32;j++) debug<<dat[i][j]<<" ";
            debug<<endl;
        }
    }
}trans[2],ini;

inline int cov(int issame,int mx,int mi) { // c in range[0,1] , mx in range[-3,0] , mi in range[0,3] .
    return issame * 16 + mx * 4 + mi + 4;
}
inline void buildtrs() {
    for(int j=0;j<2;j++) for(int k=0;k<=3;k++) for(int p=-3;p<=0;p++) {
        if( k + 2 <= 3 ) {
            trans[0][cov(1,k,p)][cov(1,max(k+2,2),min(p+2,0))] = 1;
            trans[0][cov(0,k,p)][cov(0,max(k+2,2),min(p+2,0))] = 1;
            trans[1][cov(1,k,p)][cov(0,max(k+2,2),min(p+2,0))] = 1;
            trans[1][cov(0,k,p)][cov(0,max(k+2,2),min(p+2,0))] = 1;
        }
        if( p - 1 >= -3 ) {
            trans[0][cov(0,k,p)][cov(0,max(k-1,0),min(p-1,-1))] = 1;
            trans[1][cov(1,k,p)][cov(1,max(k-1,0),min(p-1,-1))] = 1;
            trans[1][cov(0,k,p)][cov(0,max(k-1,0),min(p-1,-1))] = 1;
        }
    }
    ini[1][cov(1,0,0)] = 1;
}

inline Matrix fastpow(Matrix base,int tim) {
    Matrix ret(1);
    while(tim) {
        if( tim & 1 ) ret = ret * base;
        if( tim >>= 1 ) base = base * base;
    }
    return ret;
}
inline Matrix getseg(const string &x) {
    Matrix ret(1);
    for(int i=0;i<(signed)x.size();i++) ret = ret * trans[x[i]=='Z'];
    return ret;
}
inline int findint(const string &x) {
    int ret = 0;
    for(unsigned i=0;i<x.length();i++) {
        if( isdigit(x[i]) ) ret = ret * 10 + x[i] - '0';
        else break;
    }
    return ret;
}

inline string cutint(const string &x) {
    int i;
    for(i=0;i<(signed)x.length();i++) if( !isdigit(x[i]) ) break;
    return x.substr(i,x.length()-i);
}
inline Matrix explain(const string &x) {
    int i,j;
    for(i=0;i<(signed)x.length();i++) if( x[i] == '(' ) break;
    if( i == (signed)x.length() ) return getseg(x);
    int su = 0;
    for(j=0;j<(signed)x.length();j++) {
        if( x[j] == '(' ) ++su;
        else if( x[j] == ')' ) {
            if( su > 1 ) --su;
            else break;
        }
    }
    string lft = x.substr(0,i) , mid = x.substr(i+1,j-i-1) , rem = x.substr(j+1,x.length()-j-1) , rit = cutint(rem);
    Matrix ret = getseg(lft) * fastpow(explain(mid),findint(rem)) * explain(rit);
    return ret;
}
inline int solve(const string &x) {
    Matrix ans = ini * explain(x);
    int ret = 0;
    for(int i=1;i<=lim;i++) adde(ret,ans[1][i]);
    return ret;
}

int main() {
    static int T;
    scanf("%d",&T) , buildtrs();
    while(T--) scanf("%s",in+1) , printf("%d\n",solve((string)(in+1)));
    return 0;
}
