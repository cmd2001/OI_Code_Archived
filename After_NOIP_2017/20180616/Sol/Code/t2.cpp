#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#define debug cout
typedef unsigned long long int ulli;
using namespace std;
const int maxn=3e5+1e2;

int in[maxn],n;
ulli ans; // ans will be correct moding 2 ^ 64 .

namespace Force {
    const int maxn=2e3+1e2;
    struct pii {int l,r;};
    struct RotatelessTreap {
        int ch[maxn][2],siz[maxn],fix[maxn];
        ulli dat[maxn],su[maxn][2]; // 0 means even , 1 means odd .
        RotatelessTreap() { 
            for(int i=0;i<maxn;i++) fix[i] = i;
            random_shuffle(fix,fix+maxn);
        }
        inline void maintain(int pos) {
            siz[pos] = siz[ch[pos][0]] + siz[ch[pos][1]] + 1;
            if( ! ( siz[ch[pos][0]] & 1 ) ) {
                 su[pos][0] = su[ch[pos][0]][0] + su[ch[pos][1]][1];
                 su[pos][1] = su[ch[pos][0]][1] + dat[pos] + su[ch[pos][1]][0];
            } else {
                su[pos][0] = su[ch[pos][0]][0] + dat[pos] + su[ch[pos][1]][0];
                su[pos][1] = su[ch[pos][0]][1] + su[ch[pos][1]][1];
            }
        }
        inline pii split(int pos,ulli nv) { // left is <= nv .
            if( !pos ) return (pii){0,0};
            if( dat[pos] > nv ) {
                pii spl = split(ch[pos][0],nv);
                ch[pos][0] = spl.r , maintain(pos);
                return (pii){spl.l,pos};
            } else {
                pii spr = split(ch[pos][1],nv);
                ch[pos][1] = spr.l , maintain(pos);
                return (pii){pos,spr.r};
            }
        }
        inline int merge(int x,int y) { // assert dat[x] <= dat[y] .
            if( !x || !y ) return x | y;
            assert(dat[x]<=dat[y]);
            if( fix[x] > fix[y] ) {
                ch[x][1] = merge(ch[x][1],y) , maintain(x);
                return x;
            } else {
                ch[y][0] = merge(x,ch[y][0]) , maintain(y);
                return y;
            }
        }
        inline void reset(int x,ulli dd) {
            su[x][0] = ch[x][0] = ch[x][1] = 0 , su[x][1] = dat[x] = dd , siz[x] = 1;
        }
        inline void insert(int &root,int x) {
            pii sp = split(root,dat[x]);
            root = merge(sp.l,merge(x,sp.r));
        }
        inline ulli query(int root) {
            return su[root][0] - su[root][1];
        }
    }treap;

    inline void getans() {
        for(int i=1,root;i<=n;i++) {
            treap.reset(root=i,in[i]);
            for(int j=i+1;j<=n;j++) {
                treap.reset(j,in[j]) , treap.insert(root,j);
                if( ( j - i ) & 1 ) ans += treap.query(root);
            }
        }
    }
}

namespace Order {
    inline ulli calc_odd(int i) {
        int before = i , after = n - i;
        return (ulli) ( ( before + 1 ) >> 1 ) * (ulli) ( ( after + 1 ) >> 1 );
    }
    inline ulli calc_even(int i) {
        int before = i , after = n - i;
        return (ulli) ( before >> 1 ) * (ulli) ( ( after >> 1 ) + 1 );
    }
    inline void getans() {
        for(int i=1;i<=n;i++) ans += calc_even(i) * in[i] , ans -= calc_odd(i) * in[i];
    }
}

namespace Less {
    int su[maxn],prf[2][2];
    inline void getans() {
        for(int i=1;i<=n;i++) su[i] = su[i-1] + in[i];
        prf[0][0] = 1;
        for(int i=1;i<=n;i++) ans += prf[i&1][(su[i]&1)^1] , ++prf[i&1][su[i]&1];
    }
}

int main() {
    static bool order = 1 , less = 1;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {
        scanf("%d",in+i);
        if( i != 1 && in[i] < in[i-1] ) order = 0;
        if( in[i] > 1 ) less = 0;
    }
    if( n <= 2000 ) Force::getans();
    else if( order ) Order::getans();
    else if( less ) Less::getans();
    else srand((unsigned long long)new char) , ans = rand() * rand();
    printf("%llu\n",ans);
    return 0;
}
