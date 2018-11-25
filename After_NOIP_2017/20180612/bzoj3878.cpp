#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#define debug cout
typedef long long int lli;
using namespace std;
const int maxn=1e5+1e2;

int rec[maxn],n;

struct Node {
    int val,id;
    friend bool operator < (const Node &a,const Node &b) {
        return a.val < b.val;
    }
}in[maxn];

lli rv[maxn],L,R;

enum operate {MUL,ADD,ADDR,FILL};
const int INIV[]={1,0,0};

struct SegmentTree {
    int l[maxn<<3],r[maxn<<3],lson[maxn<<3],rson[maxn<<3],cnt;
    lli mx[maxn<<3],mi[maxn<<3],lazy[maxn<<3][4];

    SegmentTree() { cnt = 1; }
    inline void apply(int pos,const operate &ope,const lli &x) {
        if( ope == FILL ) {
            mx[pos] = mi[pos] = lazy[pos][FILL] = x;
            for(int i=0;i<3;i++) lazy[pos][i] = INIV[i];
        } else if( ope == ADD ) lazy[pos][ADD] += x , mi[pos] += x , mx[pos] += x;
        else if( ope == MUL ) lazy[pos][ADD] *= x , lazy[pos][ADDR] *= x , lazy[pos][MUL] *= x , mi[pos] *= x , mx[pos] *= x;
        else if( ope == ADDR ) lazy[pos][ADDR] += x , mi[pos] += in[l[pos]].val * x , mx[pos] += in[r[pos]].val * x;
    }
    inline void push(int pos) {
        if( lazy[pos][FILL] != -1 ) apply(lson[pos],FILL,lazy[pos][FILL]) , apply(rson[pos],FILL,lazy[pos][FILL]) , lazy[pos][FILL] = -1;
        for(int i=0;i<3;i++) if( lazy[pos][i] != INIV[i] ) apply(lson[pos],(operate)i,lazy[pos][i]) , apply(rson[pos],(operate)i,lazy[pos][i]) , lazy[pos][i] = INIV[i];
    }
    inline void maintain(int pos) {
        mx[pos] = max( mx[lson[pos]] , mx[rson[pos]] ) , mi[pos] = min( mi[lson[pos]] , mi[rson[pos]] );
    }
    inline void build(int pos,int ll,int rr) {
        l[pos] = ll , r[pos] = rr , lazy[pos][MUL] = 1 , lazy[pos][FILL] = -1;
        if( ll == rr ) return void( mx[pos] = mi[pos] = in[ll].val );
        const int mid = ( ll + rr ) >> 1;
        build(lson[pos]=++cnt,ll,mid) , build(rson[pos]=++cnt,mid+1,rr) , maintain(pos);
    }
    inline void update(int pos,const int &ll,const int &rr,const operate &ope,const lli &x) {
        if( ll <= l[pos] && r[pos] <= rr ) return apply(pos,ope,x);
        const int mid = ( l[pos] + r[pos] ) >> 1; push(pos);
        if( ll <= mid ) update(lson[pos],ll,rr,ope,x);
        if( mid < rr ) update(rson[pos],ll,rr,ope,x);
        maintain(pos);
    }
    inline int lower_bound(int pos,const int &x) { // find first pos >= x .
        if( mi[pos] >= x ) return l[pos];
        if( mx[pos] < x ) return r[pos] + 1;
        return push(pos) , mx[lson[pos]] < x ? lower_bound(rson[pos],x) : lower_bound(lson[pos],x);
    }
    inline void dfs(int pos) {
        if( l[pos] == r[pos] ) return void( rv[l[pos]] = mi[pos] );
        push(pos) , dfs(lson[pos]) , dfs(rson[pos]);
    }
}sgt;

inline int explain(const char &x) {
    switch(x) {
        case '+': return 1;
        case '-': return -1;
        case '*': return 0;
        case '@': return 2;
    }
    return -1;
}

int os[maxn],osx[maxn];

int main() {
    static int n,q;
    static char o[10];
    scanf("%d%lld%lld",&q,&L,&R);
    for(int i=1;i<=q;i++) scanf("%s%d",o,osx+i) , os[i] = explain(*o);
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&in[i].val) , in[i].id = i;
    sort(in+1,in+1+n) , sgt.build(1,1,n);
    for(int i=1;i<=n;i++) rec[in[i].id] = i;
    for(int i=1,t;i<=q;i++) {
        if( os[i] != -1 ) {
            sgt.update(1,1,n,(operate)os[i],osx[i]);
            t = sgt.lower_bound(1,R);
            if( t <= n ) sgt.update(1,t,n,FILL,R);
        } else {
            sgt.update(1,1,n,ADD,-osx[i]);
            t = sgt.lower_bound(1,L);
            if( t > 1 ) sgt.update(1,1,t-1,FILL,L);
        }
    }
    sgt.dfs(1);
    for(int i=1;i<=n;i++) printf("%lld\n",rv[rec[i]]);
    return 0;
}
