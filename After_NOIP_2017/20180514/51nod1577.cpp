#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#include<cstdio>
#include<cstring>
#include<cctype>
#define bool unsigned char
typedef unsigned int ui;
const int maxn=1048577,maxl=31;

ui in[maxn>>1],bit[maxl];

struct LinearBase {
    ui dat[maxl];
    __inline const ui& operator [] (const ui &x) const { return dat[x]; }
    __inline bool insert(ui x) {
        for(ui i=30;~i;i--) if( x & bit[i] ) {
            if( !dat[i] ) return dat[i] = x , 1;
            else x ^= dat[i];
        }
        return 0;
    }
    __inline void merge(const LinearBase &r) {
        for(ui i=30;~i;i--) if( r[i] ) insert(r[i]);
    }
    __inline void reset() {
        memset(dat,0,sizeof(dat));
    }
}ans;

struct SegmentTree {
    LinearBase dat[maxn];
    #define lson(pos) (pos<<1)
    #define rson(pos) (pos<<1|1)
    __inline void build(ui pos,ui l,ui r) {
        if( l == r ) return void(dat[pos].insert(in[l]));
        const ui mid = ( l + r ) >> 1;
        build(lson(pos),l,mid) , build(rson(pos),mid+1,r);
        dat[pos] = dat[lson(pos)] , dat[pos].merge(dat[rson(pos)]);
    }
    __inline void query(ui pos,ui l,ui r,const ui &ll,const ui &rr) {
        if( ll <= l && r <= rr ) return ans.merge(dat[pos]);
        const ui mid = ( l + r ) >> 1;
        if( ll <= mid ) query(lson(pos),l,mid,ll,rr);
        if( mid < rr ) query(rson(pos),mid+1,r,ll,rr);
    }
}sgt;

__inline unsigned char nextchar() {
    return getchar();
    static const ui BS = 1 << 18;
    static unsigned char buf[BS],*st,*ed;
    if( st == ed ) ed = buf + fread(st=buf,1,BS,stdin);
    return st == ed ? 0 : *st++;
}
__inline ui getint() {
    ui ret = 0;
    unsigned char ch;
    while( !isdigit(ch=nextchar()) ) ;
    do ret=ret*10+ch-'0'; while( isdigit(ch=nextchar()) );
    return ret;
}

int main() {
    //freopen("51nod_Problem_1577_Test_5_In.txt","r",stdin);
    //freopen("2334.txt","w",stdout);
    static ui n,q,l,r,w;
    n = getint();
    for(ui *st=in+1,*ed=st+n;st!=ed;*st++=getint());
    for(ui i=0;i<30;i++) bit[i] = 1 << i;
    sgt.build(1,1,n) , q = getint();
    while(q--) {
        l = getint() , r = getint() , w = getint() , ans.reset();
        sgt.query(1,1,n,l,r);
        puts(ans.insert(w)?"NO":"YES");
    }
    return 0;
}
