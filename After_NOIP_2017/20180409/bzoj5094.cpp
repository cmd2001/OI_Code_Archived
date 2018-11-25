#include<cstdio>
#include<algorithm>
#include<cmath>
const int maxn=1e4+1e2;

unsigned in[maxn];
int tim[maxn],len;
double fac[maxn],mx=-1e10;
int m,ans;

inline double c(int n,int m) {
    return fac[n] - fac[n-m] - fac[m];
}
inline double fc(int n,int m) {
    double ret = 0;
    for(int i=1;i<=m;i++) ret += log(n-i+1) - log(i);
    return ret;
}
inline double pows(int n,int m) {
    return log(n) * m;
}
inline double calc(int t) {
    double ret = fc(t,len) - pows(t,m);
    int su = 0;
    for(int i=1;i<=len;i++) ret += c(m-su,tim[i]) , su += tim[i];
    return ret;
}

inline void pre() {
    *fac = log(1);
    for(int i=1;i<maxn;i++) fac[i] = fac[i-1] + log(i);
}

int main() {
    scanf("%d",&m) , pre();
    for(int i=1;i<=m;i++) scanf("%u",in+i);
    std::sort(in+1,in+1+m);
    tim[len=1] = 1;
    for(int i=2;i<=m;i++) {
        if( in[i] != in[i-1] ) ++len;
        ++tim[len];
    }
    for(int n=10;n<=10000000;n*=10) {
        if( n < len ) continue;
        double t = calc(n);
        if( t > mx ) mx = t , ans = n;
    }
    printf("%d\n",ans);
    return 0;
}
