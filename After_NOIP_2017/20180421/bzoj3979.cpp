#pragma GCC optimize(2)
#include<cstdio>
const int maxn=77;

// I don't know why the ans is O(logn) .

struct bs {
    unsigned int lw,md,hi;
    inline void reset() {
        lw = md = hi = 0;
    }
    inline void set(int bit) {
        if( bit < 32 ) return void( lw |= ( 1u << bit ) );
        bit -= 32;
        if( bit < 32 ) return void( md |= ( 1u << bit ) );
        hi |= 1 << ( bit - 32 );
    }
    friend bs operator | (const bs &a,const bs &b) {
        return (bs){a.lw|b.lw,a.md|b.md,a.hi|b.hi};
    }
    inline int count() {
        return __builtin_popcount(lw) + __builtin_popcount(md) + __builtin_popcount(hi);
    }
}in[maxn];
int n;

inline bool one() {
    for(int i=1;i<=n;i++)
        if( in[i].count() == n ) return 1;
    return 0;
}
inline bool two() {
    for(int i=1;i<=n;i++)
        for(int j=1;j<i;j++)
            if( ( in[i] | in[j] ).count() == n ) return 1;
    return 0;
}
inline bool three() {
    for(int i=1;i<=n;i++)
        for(int j=1;j<i;j++)
            for(int k=1;k<j;k++)
                if( ( in[i] | in[j] | in[k] ).count() == n ) return 1;
    return 0;
}
inline bool four() {
    for(int i=1;i<=n;i++)
        for(int j=1;j<i;j++)
            for(int k=1;k<j;k++)
                for(int l=1;l<k;l++)
                    if( ( in[i] | in[j] | in[k] | in[l] ).count() == n ) return 1;
    return 0;
}
inline bool five() {
    for(int i=1;i<=n;i++)
        for(int j=1;j<i;j++)
            for(int k=1;k<j;k++)
                for(int l=1;l<k;l++)
                    for(int m=1;m<l;m++)
                        if( ( in[i] | in[j] | in[k] | in[l] | in[m] ).count() == n ) return 1;
    return 0;
}
int main() {
    static char buf[maxn];
    static int T;
    while( ~scanf("%d",&n) ) {
        for(int i=1;i<=n;i++) {
            scanf("%s",buf+1) , in[i].reset();
            for(int j=1;j<=n;j++) if( buf[j] - '0' ) in[i].set(j);
            in[i].set(i);
        }
        printf("Case %d: ",++T);
        if( one() ) puts("1");
        else if( two() ) puts("2");
        else if( three() ) puts("3");
        else if( four() ) puts("4");
        else if( five() ) puts("5");
        else puts("6");
    }
    return 0;
}
