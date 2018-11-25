#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
const int maxn=262145;
const int inf=0x3f3f3f3f;
const double pi = acos(-1.0);

int tim[maxn];

namespace FFT {
    struct Complex {
        double r,i;
        friend Complex operator + (const Complex &a,const Complex &b) { return (Complex){a.r+b.r,a.i+b.i}; }
        friend Complex operator - (const Complex &a,const Complex &b) { return (Complex){a.r-b.r,a.i-b.i}; }
        friend Complex operator * (const Complex &a,const Complex &b) { return (Complex){a.r*b.r-a.i*b.i,a.r*b.i+a.i*b.r}; }
    }cp[maxn];
    inline void FFT(Complex* dst,int n,int tpe) {
        for(int i=0,j=0;i<n;i++) {
            if( i < j ) std::swap(dst[i],dst[j]);
            for(int t=n>>1;(j^=t)<t;t>>=1) ;
        }
        for(int len=2;len<=n;len<<=1) {
            const int h = len >> 1;
            const Complex per = (Complex){cos(pi*tpe/h),sin(pi*tpe/h)};
            for(int st=0;st<n;st+=len) {
                Complex w = (Complex){1.0,0.0};
                for(int pos=0;pos<h;pos++) {
                    const Complex u = dst[st+pos] , v = dst[st+pos+h] * w;
                    dst[st+pos] = u + v , dst[st+pos+h] = u - v , w = w * per;
                }
            }
        }
        if( !~tpe ) for(int i=0;i<n;i++) dst[i].r /= n;
    }
    inline void mul(int* dst,int n) {
        int len = 1;
        while( len <= ( n << 1 ) ) len <<= 1;
        for(int i=0;i<len;i++) cp[i] = (Complex){(double)dst[i],0.0};
        FFT(cp,len,1);
        for(int i=0;i<len;i++) cp[i] = cp[i] * cp[i];
        FFT(cp,len,-1);
        for(int i=0;i<len;i++) dst[i] = (int)(cp[i].r+0.5);
    }
}

namespace Tree {
    int s[maxn],t[maxn<<1],nxt[maxn<<1];
    int siz[maxn],mxs[maxn],ban[maxn];
    int su[maxn],tp[maxn];
    
    inline void addedge(int from,int to) {
        static int cnt = 0;
        t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
    }
    inline void findroot(int pos,int fa,const int &fs,int &rt) {
        siz[pos] = 1 , mxs[pos] = 0;
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa && !ban[t[at]] ) findroot(t[at],pos,fs,rt) , siz[pos] += siz[t[at]] , mxs[pos] = std::max( mxs[pos] , siz[t[at]] );
        if( ( mxs[pos] = std::max( mxs[pos] , fs - siz[pos]) ) <= mxs[rt] ) rt = pos;
    }
    inline void dfs(int pos,int fa,int dep,int &mxd) {
        mxd = std::max( mxd , dep ) , ++tp[dep];
        for(int at=s[pos];at;at=nxt[at]) if( t[at] != fa && !ban[t[at]] ) dfs(t[at],pos,dep+1,mxd);
    }
    inline void solve(int pos,int fs) {
        int root = 0 , mxd = 0 , ths ;
        *mxs = inf, findroot(pos,-1,fs,root) , ban[root] = 1;
        for(int at=s[root];at;at=nxt[at]) if( !ban[t[at]]) {
            ths = 0 , dfs(t[at],root,1,ths) , mxd = std::max( mxd , ths );
            for(int i=1;i<=ths;i++) su[i] += tp[i];
            FFT::mul(tp,ths);
            for(int i=1;i<=ths<<1;i++) tim[i] -= tp[i];
            memset(tp,0,sizeof(int)*(ths<<1|1));
        }
        ++*su , FFT::mul(su,mxd);
        for(int i=1;i<=mxd<<1;i++) tim[i] += su[i];
        memset(su,0,sizeof(int)*(mxd<<1|1));
        for(int at=s[root];at;at=nxt[at]) if( !ban[t[at]] ) solve(t[at],siz[t[at]]<siz[root]?siz[t[at]]:fs-siz[root]);
    }
}

int main() {
    static int n;
    static long double ans;
    scanf("%d",&n);
    for(int i=1,a,b;i<n;i++) scanf("%d%d",&a,&b) , ++a , ++b , Tree::addedge(a,b) , Tree::addedge(b,a);
    Tree::solve(1,n) , ans = n;
    for(int i=1;i<=n<<1;i++) ans += (long double) tim[i] / ( i + 1 );
    printf("%0.4Lf\n",ans);
    return 0;
}

