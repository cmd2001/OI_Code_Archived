#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
const int maxn=3e4+1e2,maxe=129,mod=10007,inv=5004;

int n,m;

inline void FWT(int* dst,int n) {
    for(int len=2;len<=n;len<<=1) {
        const int h = len >> 1;
        for(int st=0;st<n;st+=len)
            for(int pos=0;pos<h;pos++) {
                const int u = dst[st+pos] , v = dst[st+pos+h];
                dst[st+pos] = ( u + v ) % mod , dst[st+pos+h] = ( u - v + mod ) % mod;
            }
    }
}
inline void UFWT(int* dst,int n) {
    for(int len=2;len<=n;len<<=1) {
        const int h = len >> 1;
        for(int st=0;st<n;st+=len)
            for(int pos=0;pos<h;pos++) {
                const int u = dst[st+pos] , v = dst[st+pos+h];
                dst[st+pos] = ( u + v ) % mod * inv % mod ,  dst[st+pos+h] = (  u - v + mod ) % mod * inv % mod;
            }
    }
}

struct Poly {
    int dat[maxe];
    Poly() { memset(dat,0,sizeof(dat)); }
    int& operator [] (const int &x) { return dat[x]; }
    const int& operator [] (const int &x) const { return dat[x]; }
    friend Poly operator + (const Poly &a,const Poly &b) {
        Poly ret;
        for(int i=0;i<m;i++) ret[i] = ( a[i] + b[i] ) % mod;
        return ret;
    }
    friend Poly operator * (const Poly &a,const Poly &b) {
        Poly ret;
        for(int i=0;i<m;i++) ret[i] = a[i] * b[i] % mod;
        return ret;
    }
};

struct Matrix {
    //?
};

