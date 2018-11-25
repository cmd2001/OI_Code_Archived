#pragma GCC optimize("Ofast","no-stack-protector")
#pragma GCC target("avx")
#include<cstdio>
#include<cstring>
typedef long long int lli;
const int maxn=3e4+1e2,maxk=6;
const int mod=998244353;

int in[maxn],n,kkk;

inline void adde(int& dst,const int &x) {
    if( ( dst += x ) >= mod ) dst -= mod;
}
inline int mul(const int &x,const int &y) {
    return (lli) x * y % mod;
}

struct Matrix {
    int dat[maxk][maxk];
    Matrix() {}
    Matrix(int tpe) { memset(dat,0,sizeof(dat)); for(int i=0;i<=kkk;i++) dat[i][i] = tpe; }
    int* operator [] (const int &x) { return dat[x]; }
    const int* operator [] (const int &x) const { return dat[x]; }
    friend Matrix operator * (const Matrix &a,const Matrix &b) {
        Matrix ret(0);
        for(int i=0;i<=kkk;i++) for(int j=0;j<=kkk;j++) for(int k=0;k<=kkk;k++) adde(ret[i][j],mul(a[i][k],b[k][j]));
        return ret;
    }
}trans[maxk],ini;

inline Matrix get_trans(int x) {
    Matrix ret(1);
    for(int i=0;i<=kkk;i++) ret[i][x] = 1;
    return ret;
}
inline Matrix get_trans(int x,int mul,int add) {
    x = ( x * mul % kkk + add ) % kkk;
    return trans[x];
}

struct SegmentTree {
    Matrix pi[maxn*5/2][maxk][maxk];
    int lazy_mul[maxn*5/2],lazy_add[maxn*5/2];
    #define lson(pos) (pos<<1)
    #define rson(pos) (pos<<1|1)
    inline Matrix getdat(int pos,int mul,int add) {
        add = ( lazy_add[pos] * mul % kkk + add ) % kkk , mul = mul * lazy_mul[pos] % kkk;
        return pi[pos][mul][add];
    }
    inline void merge(int pos) {
        const int ls = lson(pos) , rs = rson(pos);
        for(int mul=0;mul<kkk;mul++) for(int add=0;add<kkk;add++) pi[pos][mul][add] = getdat(rs,mul,add) * getdat(ls,mul,add);
    }
    inline void build(int pos,int l,int r) {
        lazy_mul[pos] = 1 , lazy_add[pos] = 0;
        if( l == r ) {
            for(int mul=0;mul<kkk;mul++) for(int add=0;add<kkk;add++) pi[pos][mul][add] = get_trans(in[l],mul,add);
            return;
        } const int mid = ( l + r ) >> 1;
        build(lson(pos),l,mid) , build(rson(pos),mid+1,r) , merge(pos);
    }
    inline void apply(int pos,const int &mul,const int &add) {
        lazy_mul[pos] = lazy_mul[pos] * mul % kkk , lazy_add[pos] = ( lazy_add[pos] * mul + add ) % kkk;
    }
    inline void push(int pos) {
        apply(lson(pos),lazy_mul[pos],lazy_add[pos]) , apply(rson(pos),lazy_mul[pos],lazy_add[pos]);
        lazy_mul[pos] = 1 , lazy_add[pos] = 0;
    }
    inline void update(int pos,int l,int r,const int &ll,const int &rr,const int &mul,const int &add) {
        if( ll <= l && r <= rr ) return apply(pos,mul,add);
        const int mid = ( l + r ) >> 1; push(pos);
        if( ll <= mid ) update(lson(pos),l,mid,ll,rr,mul,add);
        if( mid < rr ) update(rson(pos),mid+1,r,ll,rr,mul,add);
        merge(pos);
    }
    inline Matrix query(int pos,int l,int r,const int &ll,const int &rr) {
        if( ll <= l && r <= rr ) return getdat(pos,1,0);
        const int mid = ( l + r ) >> 1; push(pos) , merge(pos);
        if( rr <= mid ) return query(lson(pos),l,mid,ll,rr);
        else if( ll > mid ) return query(rson(pos),mid+1,r,ll,rr);
        else return query(rson(pos),mid+1,r,ll,rr) * query(lson(pos),l,mid,ll,rr);
    }
}sgt;


inline int getans(int l,int r) {
    Matrix ret = ini * sgt.query(1,1,n,l,r);
    int su = 0;
    for(int i=0;i<kkk;i++) adde(su,ret[0][i]);
    return su;
}

int main() {
    freopen("data.in","r",stdin);
    freopen("data.out","w",stdout);
    static int T,m;
    scanf("%d",&T);
    while(T--) {
        scanf("%d%d%d",&n,&kkk,&m) , ini = Matrix(0) , ini[0][kkk] = 1;
        for(int i=0;i<kkk;i++) trans[i] = get_trans(i);
        for(int i=1;i<=n;i++) scanf("%d",in+i);
        sgt.build(1,1,n);
        for(int i=1,o,l,r,x;i<=m;i++) {
            scanf("%d%d%d",&o,&l,&r);
            if( o == 1 ) scanf("%d",&x) , sgt.update(1,1,n,l,r,1,x);
            else if( o == 2 ) scanf("%d",&x) , sgt.update(1,1,n,l,r,x,0);
            else printf("%d\n",getans(l,r));
        }
    }
    fclose(stdout);
    return 0;
}

