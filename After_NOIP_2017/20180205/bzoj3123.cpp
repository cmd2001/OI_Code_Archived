#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int maxn=8e4+1e2;

namespace Tree {
    int l[maxn<<6],r[maxn<<6],lson[maxn<<6],rson[maxn<<6],sum[maxn<<6];
    struct RamPool {
        int pool[maxn<<6],top;
        inline void DelNode(int x) {
            pool[++top] = x;
        }
        inline int NewNode() {
            int ret = pool[top--];
            l[ret] = r[ret] = lson[ret] = rson[ret] = sum[ret] = 0;
            return ret;
        }
    }
    using RamPool::DelNode;
    using RamPool::NewNode;
    inline void prebuild(int pos,int ll,int rr) {
        l[pos] = ll , r[pos] = rr;
        if( ll == rr ) return;
        const int mid = ( ll + rr ) >> 1;
        prebuild(lson[pos]=NewNode(),ll,mid);
        prebuild(rson[pos]=NewNode(),mid+1,rr);
    }
    inline void insert(int pos,int ref,int x) {
        l[pos] = l[ref] , r[pos] = r[ref] ,
        lson[pos] = lson[ref] , rson[pos] = rson[ref];
        if( l[pos] == r[pos] && l[pos] == x ) {
            sum[pos] = sum[ref] + 1;
            return;
        }
        const int mid = ( l[pos] + r[pos] ) >> 1;
        if( x <= mid ) insert(lson[pos]=NewNode(),lson[ref],x);
        else insert(rson[pos]=NewNode(),rson[ref],x);
        sum[pos] = sum[lson[pos]] + sum[rson[pos]];
    }
    inline int calcl(int a1,int a2,int b1,int b2) {
        return sum[lson[a1]] + sum[lson[a2]] - sum[lson[b1]] - sum[lson[b2]];
    }
    inline int query(int a1,int a2,int b1,int b2,int k) {
        if( l[a1] == r[a1] ) return l[a1];
        
    }
}
namespace FUS {
    int fa[maxn];
    inline int findfa(int x) {
        return fa[x] == x ? x : fa[x] = findfa(fa[x]);
    }
    inline void merge(int x,int y) {// merge y into x
        y = findfa(y);
        fa[y] = x;
    }
}
int s[maxn],t[maxn<<1],nxt[maxn<<1];

inline void addedge(int from,int to) {
    static int cnt = 1;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
