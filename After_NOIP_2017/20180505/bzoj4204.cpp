#include<cstdio>
#include<cstring>
const int maxn=1e3+1e2;

int n;

struct Poly {
    double dat[maxn];
    Poly(int tpe=0) { memset(dat,0,sizeof(dat)) , *dat = tpe; }
    double& operator [] (const int &x) { return dat[x]; }
    const double& operator [] (const int &x) const { return dat[x]; }
    friend Poly operator * (const Poly &a,const Poly &b) {
        Poly ret;
        for(int i=0;i<n;i++) for(int j=0;j<n;j++) ret[(i+j)%n] += a.dat[i] * b.dat[j];
        return ret;
    }
}ini,trans,ans;

Poly fastpow(Poly base,int tim) {
    Poly ret(1);
    while(tim) {
        if( tim & 1 ) ret = ret * base;
        if( tim >>= 1 ) base = base * base;
    }
    return ret;
}

int main() {
    static int m,k;
    scanf("%d%d%d",&n,&m,&k) , trans[0] = ( m - 1.0 ) / m , trans[1] = 1.0 / m;
    for(int i=0;i<n;i++) scanf("%lf",&ini[i]);
    ans = ini * fastpow(trans,k);
    for(int i=0;i<n;i++) printf("%0.3lf\n",ans[i]);
}
