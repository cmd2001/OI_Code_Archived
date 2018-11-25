#pragma GCC optimize(3)
#include<cstdio>
#include<cstring>
#include<algorithm>
#define lli long long int
#define mid ( ( ll + rr ) >> 1 )
const int maxn=5e4+1e2,maxc=21;
const int mod = 19940417;
 
struct Qnode {
    lli dat[maxc];
    Qnode(const lli* dst=NULL) {
        memset(dat,0,sizeof(dat));
        if( dst )
            for(int i=0;i<maxc;i++)
                dat[i] = dst[i];
    }
};
int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3];
lli f[maxn<<3][maxc],lazy[maxn<<3];
lli c[maxn][maxc];
unsigned char neg[maxn<<3];
int in[maxn];
int n,m,cnt;
 
inline void merge(lli* dst,lli* lson,lli* rson) {
    for(int i=0;i<maxc;i++)
        dst[i] = 0;
    dst[0] = 1;
    for(int i=0;i<maxc;i++)
        for(int j=0;j<maxc;j++)
            if( i + j < maxc ) {
                dst[i+j] += lson[i] * rson[j] % mod;
                dst[i+j] %= mod;
            }
    for(int i=0;i<maxc;i++) {
        dst[i] = ( dst[i] + mod ) % mod;
    }
    dst[0] = 1;
}
 
inline void build(int pos,int ll,int rr) {
    l[pos] = ll , r[pos] = rr;
    f[pos][0] = 1;
    if( ll == rr ) {
        f[pos][1] = in[ll];
        return;
    }
    build(lson[pos]=++cnt,ll,mid);
    build(rson[pos]=++cnt,mid+1,rr);
    merge(f[pos],f[lson[pos]],f[rson[pos]]);
}
 
inline void workneg(int pos) {
    for(int i=0;i<maxc;i++)
        if( i & 1 )
            f[pos][i] = mod - f[pos][i];
    lazy[pos] = mod - lazy[pos];
}
inline void worklazy(int pos,lli lz) {
    const int len = r[pos] - l[pos] + 1;
    for(int i=std::min(maxc-1,len);~i;i--) {
        lli mul = 1;
        for(int j=i-1;~j;j--) {
            mul = mul * lz % mod;
            f[pos][i] += f[pos][j] * mul % mod * c[len-j][i-j] % mod;
            f[pos][i] %= mod;
        }
        f[pos][i] = ( f[pos][i] + mod ) % mod;
    }
}
inline void pushneg(int pos) {
    if( neg[pos] ) {
        if( lson[pos] ) {
            neg[lson[pos]] ^= 1;
            workneg(lson[pos]);
        }
        if(rson[pos]) {
            neg[rson[pos]] ^= 1;
            workneg(rson[pos]);
        }
        neg[pos] = 0;
    }
}
inline void pushlazy(int pos) {
    if( lazy[pos] ) {
        pushneg(pos);
        if( lson[pos] ) {
            lazy[lson[pos]] += lazy[pos],
            lazy[lson[pos]] = ( lazy[lson[pos]] % mod + mod ) % mod;
            worklazy(lson[pos],lazy[pos]);
        }
        if(rson[pos]) {
            lazy[rson[pos]] += lazy[pos],
            lazy[rson[pos]] = ( lazy[rson[pos]] % mod + mod ) % mod;
            worklazy(rson[pos],lazy[pos]);
        }
        lazy[pos] = 0;
    }
}
inline void push(int pos) {
    pushneg(pos);
    pushlazy(pos);
}
 
inline void updateadd(int pos,int ll,int rr,int x) {
    if( rr < l[pos] || r[pos] < ll )
        return;
    if( ll <= l[pos] && r[pos] <= rr ) {
        pushneg(pos);
        lazy[pos] += x,
        lazy[pos] = ( lazy[pos] % mod + mod ) % mod;
        worklazy(pos,x);
        return;
    }
    push(pos);
    updateadd(lson[pos],ll,rr,x);
    updateadd(rson[pos],ll,rr,x);
    merge(f[pos],f[lson[pos]],f[rson[pos]]);
}
inline void updateneg(int pos,int ll,int rr) {
    if( rr < l[pos] || r[pos] < ll )
        return;
    if( ll <= l[pos] && r[pos] <= rr ) {
        neg[pos] ^= 1;
        workneg(pos);
        return;
    }
    push(pos);
    updateneg(lson[pos],ll,rr);
    updateneg(rson[pos],ll,rr);
    merge(f[pos],f[lson[pos]],f[rson[pos]]);
}
Qnode query(int pos,int ll,int rr) {
    push(pos);
    if( ll <= l[pos] && r[pos] <= rr ) {
        return (Qnode){f[pos]};
    }
    const int mmid = ( l[pos] + r[pos] ) >> 1;
    if( rr <= mmid )
        return query(lson[pos],ll,rr);
    if( ll > mmid )
        return query(rson[pos],ll,rr);
    Qnode ret,lret,rret;
    lret = query(lson[pos],ll,rr);
    rret = query(rson[pos],ll,rr);
    merge(ret.dat,lret.dat,rret.dat);
    return ret;
}
 
inline void init() {
    c[0][0] = 1;
    for(int i=1;i<=n;i++) {
        c[i][0] = 1;
        for(int j=1;j<maxc;j++)
            c[i][j] = ( c[i-1][j] + c[i-1][j-1] ) % mod;
    }
             
}
 
int main() {
    static char cc[10];
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",in+i);
     
    init();
    build(cnt=1,1,n);
     
    for(int i=1,l,r,x;i<=m;i++) {
        scanf("%s%d%d",cc,&l,&r);
        if( *cc == 'R' )
            updateneg(1,l,r);
        else {
            scanf("%d",&x);
            if( *cc == 'I' )
                updateadd(1,l,r,x);
            else {
                Qnode ans = query(1,l,r);
                printf("%lld\n",ans.dat[x]);
            }
        }
    }
     
    return 0;
}
