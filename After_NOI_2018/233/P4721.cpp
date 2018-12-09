#include<bits/stdc++.h>
typedef long long int lli;
using namespace std;
const int mod = 998244353;
const int maxn = 262145;

inline int add(const int &x,const int &y) {
    const int ret = x + y;
    return ret >= mod ? ret - mod : ret;
}
inline int sub(const int &x,const int &y) {
    const int ret = x - y;
    return ret < 0 ? ret + mod : ret;
}
inline int mul(const int &x,const int &y) {
    return (lli) x * y % mod;
}
inline void adde(int &x,const int &y) {
    if((x += y) >= mod) x -= mod;
}
inline void mule(int &x,const int &y) {
    x = (lli) x * y % mod;
}
inline int fastpow(int base,int tim) {
    int ret = 1;
    while(tim) {
        if(tim & 1) mule(ret,base);
        if(tim >>= 1) mule(base,base);
    }
    return ret;
}
inline void NTT(int* dst,int n,int tpe) {
    for(int i=0,j=0;i<n;i++) {
        if(i < j) swap(dst[i],dst[j]);
        for(int t=n>>1;(j^=t)<t;t>>=1);
    }
    for(int len=2,h=1;len<=n;len<<=1,h<<=1) {
        const int per = fastpow(tpe == 1 ? 3 : ((mod + 1) / 3), mod/len);
        for(int st=0;st<n;st+=len) {
            int w = 1;
            for(int pos=0;pos<h;pos++) {
                const int u = dst[st+pos], v = mul(dst[st+pos+h],w);
                dst[st+pos] = add(u,v), dst[st+pos+h] = sub(u,v), mule(w,per);
            }
        }
    }
    if(!~tpe) {
        const int inv = fastpow(n,mod-2);
        for(int i=0;i<n;i++) mule(dst[i],inv);
    }
}
inline void mule(int* a,int* b,int n) {
    NTT(a,n,1), NTT(b,n,1);
    for(int i=0;i<n;i++) mule(a[i],b[i]);
    NTT(a,n,-1);
}

int f[maxn],g[maxn],A[maxn],B[maxn],n;

inline void solve(int l,int r) {
    if(l == r) return;
    const int mid = (l + r) >> 1;
    solve(l,mid);
    int len;
    for(len=1;len<=r-l+1;len<<=1);
    memset(A,0,sizeof(int)*len), memset(B,0,sizeof(int)*len);
    for(int i=l;i<=mid;i++) A[i-l] = f[i];
    for(int i=1;i<=r-l;i++) B[i] = g[i];
    mule(A,B,len);
    for(int i=mid+1;i<=r;i++) adde(f[i],A[i-l]);
    solve(mid+1,r);
}

int main() {
    static int n;
    scanf("%d",&n), *f = 1;
    for(int i=1;i<n;i++) scanf("%d",g+i);
    solve(0,n);
    for(int i=0;i<n;i++) printf("%d%c",f[i],"\n "[i!=n-1]);
    return 0;
}

