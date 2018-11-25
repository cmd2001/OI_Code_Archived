#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#define lli long long int
#define debug cerr
using namespace std;
const int maxn=1e5+1e2,maxm=65537;
const double pi = acos(-1.0);

struct Comp {
    double r,i;
    Comp() {}
    Comp(double rr,double ii) { r = rr , i = ii; }
    Comp(int rr) { r = rr , i = 0; }
    Comp(double rr) { r = rr , i = 0; }
    friend Comp operator + (const Comp &a,const Comp &b) { return Comp(a.r+b.r,a.i+b.i); }
    friend Comp operator - (const Comp &a,const Comp &b) { return Comp(a.r-b.r,a.i-b.i); }
    friend Comp operator * (const Comp &a,const Comp &b) { return Comp(a.r*b.r-a.i*b.i,a.r*b.i+a.i*b.r); }
    Comp operator *= (const Comp &r) { return *this = *this * r; }
}cl[maxm],cr[maxm],mul[maxm];

int in[maxn],st[maxn],ed[maxn];
int bl[maxm],br[maxm];
int inl[maxm],inr[maxm];
int n,cnt,mx,len=1;
lli pts[maxm],ans;

inline void FFT(Comp* dst,int n,int ope) {
    for(int i=0,j=0;i<n;i++) {
        if( i < j ) swap( dst[i] ,dst[j] );
        for(int t=n>>1;(j^=t)<t;t>>=1) ;
    }
    for(int len=2;len<=n;len<<=1) {
        const int h = len >> 1;
        const Comp per = Comp( cos( pi * ope / h ) , sin( pi * ope / h ) );
        for(int st=0;st<n;st+=len) {
            Comp w = Comp( 1.0 , 0.0 );
            for(int pos=0;pos<h;pos++) {
                Comp u = dst[st+pos] , v = dst[st+pos+h] * w;
                dst[st+pos] = u + v ,
                dst[st+pos+h] = u - v ,
                w *= per;
            }
        }
    }
    if( !~ope ) {
        for(int i=0;i<n;i++)
            dst[i].r /= n;
    }
}
inline void movel(int id) { // move l into id
    for(int i=st[id];i<=ed[id];i++)
        ++bl[in[i]];
}
inline void mover(int id) { // move r out of id
    for(int i=st[id];i<=ed[id];i++)
        --br[in[i]];
}
inline void getmul() {
    for(int i=0;i<=len;i++)
        cl[i] = Comp( bl[i] ) ,
        cr[i] = Comp( br[i] ) ;
    FFT(cl,len,1) , FFT(cr,len,1);
    for(int i=0;i<len;i++)
        mul[i] = cl[i] * cr[i];
    FFT(mul,len,-1);
    for(int i=0;i<len;i++)
        pts[i] = (lli) ( mul[i].r + 0.20 );
}
inline void reset(int id) {
    for(int i=st[id];i<=ed[id];i++) inl[in[i]] = inr[in[i]] = 0;
}
inline void calcblk(int id) {
    mover(id);
    getmul();
    for(int i=st[id];i<=ed[id];i++)
        ans += pts[in[i]<<1];
    //debug<<"id = "<<id<<endl;
    for(int j=st[id];j<=ed[id];j++) {
        //debug<<"j = "<<j<<endl;
        //for(int i=1;i<=10;i++) debug<<inl[i]<<" ";debug<<endl;
        for(int k=j+1;k<=ed[id];k++)
            if( in[j]*2 - in[k] >= 0 ) ans += bl[in[j]*2-in[k]] + inl[in[j]*2-in[k]];
        ++inl[in[j]];
    }
    for(int j=ed[id];j>=st[id];j--) {
        for(int k=j-1;k>=st[id];k--)
            if( in[j]*2 - in[k] >= 0 ) ans += br[in[j]*2-in[k]];
        ++inr[in[j]];
    }
    reset(id);
    movel(id);
}
inline void gen() {
    int b = 2000;
    //int b = 5;
    for(int l=1,r;l<=n;l=r+1) {
        r = min( l + b - 1 , n ) , ++cnt;
        st[cnt] = l , ed[cnt] = r;
    }
    for(int i=1;i<=n;i++)
        ++br[in[i]];
}

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",in+i) , mx = max( mx , in[i] );
    mx <<= 1 , ++mx;
    while( len < mx ) len <<= 1;
    gen();
    for(int i=1;i<=cnt;i++)
        calcblk(i);
    printf("%lld\n",ans);
    return 0;
}
