#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cassert>
#define lli long long int
#define debug cout
using namespace std;
const int maxn=2e5+1e2;

int ls[maxn<<1],rs[maxn<<1],in[maxn<<1],root[maxn<<1],n,cnt,rt;
lli ans;

namespace SegmentTree {
    int l[maxn<<4],r[maxn<<4],lson[maxn<<4],rson[maxn<<4],sum[maxn<<4];
    namespace RamPool {
        int pool[maxn<<4],top;
        inline void DelNode(int x) {
            l[x] = r[x] = lson[x] = rson[x] = sum[x] = 0;
            pool[++top] = x;
        }
        inline int NewNode() {
            assert( top >= 1 );
            return pool[top--];
        }
    }
    using RamPool::DelNode;
    using RamPool::NewNode;
    
    inline int NewTree() {
        int ret = NewNode();
        l[ret] = 1 , r[ret] = n;
        return ret;
    }
    inline void insert(int pos,int x) {
        //debug<<"pos = "<<pos<<"x = "<<x<<endl;
        //debug<<"l = "<<l[pos]<<"r = "<<r[pos]<<endl;
        if( l[pos] == r[pos] && l[pos] == x ) {
            sum[pos] = 1;
            return;
        }
        const int mid = ( l[pos] + r[pos] ) >> 1;
        if( x <= mid ) {
            if( !lson[pos] ) lson[pos] = NewNode() , l[lson[pos]] = l[pos] , r[lson[pos]] = mid;
            insert(lson[pos],x);
        } else {
            if( !rson[pos] ) rson[pos] = NewNode() , l[rson[pos]] = mid + 1 , r[rson[pos]] = r[pos];
            insert(rson[pos],x);
        }
        sum[pos] = sum[lson[pos]] + sum[rson[pos]];
    }
    inline int query(int pos,int x) {
        if( !pos || x < l[pos] ) return 0;
        if( r[pos] <= x ) return sum[pos];
        return query(lson[pos],x) + query(rson[pos],x);
    }
    inline int merge(int lp,int rp,lli& retl,lli& retr) {
        if( !lp || !rp ) return lp | rp;
        //debug<<"lp = "<<lp<<"rp = "<<rp<<endl;
        bool flag = 0;
        retl += (lli) sum[rson[lp]] * sum[lson[rp]] , retr += (lli) sum[rson[rp]] * sum[lson[lp]];
        if( sum[lp] < sum[rp] ) swap(lp,rp) , flag = 1;
        sum[lp] += sum[rp];
        if( !flag) lson[lp] = merge(lson[lp],lson[rp],retl,retr) , rson[lp] = merge(rson[lp],rson[rp],retl,retr);
        else lson[lp] = merge(lson[lp],lson[rp],retr,retl) , rson[lp] = merge(rson[lp],rson[rp],retr,retl);
        DelNode(rp);
        return lp;
    }
    inline void init() {
        for(int i=1;i<maxn<<4;i++) DelNode(i);
    }
}

inline void readin(int pos) {
    scanf("%d",in+pos);
    if( !in[pos] ) readin(ls[pos]=++cnt) , readin(rs[pos]=++cnt);
}
inline void dfs(int pos) {
    if( in[pos] ) {
        root[pos] = SegmentTree::NewTree();
        SegmentTree::insert(root[pos],in[pos]);
        return;
    }
    dfs(ls[pos]) , dfs(rs[pos]);
    lli retl = 0 , retr = 0;
    root[pos] = SegmentTree::merge(root[ls[pos]],root[rs[pos]],retl,retr);
    ans += min( retl , retr );
}

int main() {
    SegmentTree::init();
    scanf("%d",&n);
    readin(rt=cnt=1);
    dfs(rt);
    printf("%lld\n",ans);
    return 0;
}


