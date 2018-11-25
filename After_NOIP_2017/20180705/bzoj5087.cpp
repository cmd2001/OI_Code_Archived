#include<cstdio>
#include<bitset>
typedef std::bitset<8010> Poly;
const int maxs=(1<<10)+10;

Poly pws[13],dat[maxs];
Poly f,g,mod,suf,tmp,ans;
int bid[maxs],f_len,g_len,t;

inline void add(Poly &dst,const Poly &x,const Poly &y) {
    dst = x ^ y;
}
inline void mul(Poly &dst,const Poly &x,const Poly &y) {
    dst = 0;
    for(int i=0;i<t;i++) if( x[i] ) dst ^= y << i;
    for(int i=(t<<1)-1;i>=t;i--) if( dst[i] ) dst ^= mod << ( i - t );
}
inline Poly mul(const Poly &x,const Poly &y) {
    Poly ret = 0;
    for(int i=0;i<t;i++) if( x[i] ) ret ^= y << i;
    for(int i=(t<<1)-1;i>=t;i--) if( ret[i] ) ret ^= mod << ( i - t ) ;
    return ret;
}

int main() {
    scanf("%d",&f_len); for(int i=0,x;i<=f_len;i++) scanf("%d",&x) , f[i] = x;
    scanf("%d",&g_len); for(int i=0,x;i<=g_len;i++) scanf("%d",&x) , g[i] = x;
    scanf("%d",&t); for(int i=0,x;i<=t;i++) scanf("%d",&x) , mod[i] = x;
    for(int i=g_len;i>=t;i--) if( g[i] ) g ^= mod << ( i - t ) ;
    pws[0][0] = 1; for(int i=1;i<=10;i++) mul(pws[i],pws[i-1],g);
    dat[1][0] = 1; for(int i=2;i<(1<<10);i++) bid[i] = bid[i>>1] + 1 , add(dat[i],dat[i^(1<<bid[i])],pws[bid[i]]);
    suf[0] = 1;
    for(int i=0,mask=0;i<=f_len;i+=10,mask=0) {
        for(int j=0;j<10;j++) mask |= f[i+j] << j;
        mul(tmp,suf,dat[mask]) , ans ^= tmp , suf = mul(suf,pws[10]);
    }
    while( ~t && !ans[t] ) --t;
    if( !~t ) puts("0 0");
    else {
        printf("%d ",t);
        for(int i=0;i<=t;i++) putchar('0'+ans[i]) , putchar(i!=t?' ':'\n');
    }
    return 0;
}
