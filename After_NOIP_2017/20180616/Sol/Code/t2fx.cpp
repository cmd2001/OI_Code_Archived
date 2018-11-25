#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
#define debug cout
typedef unsigned long long int ulli;
using namespace std;
const int maxn=3e5+1e2;

struct SegmentTree {
    ulli su[maxn<<2][2];
    bool lazy[maxn<<2];
    #define lson(pos) (pos<<1)
    #define rson(pos) (pos<<1|1)
    inline void maintain(int pos) {
        for(int i=0;i<2;i++) su[pos][i] = su[lson(pos)][i] + su[rson(pos)][i];
    }
    inline void apply(int pos) {
        swap(su[pos][0],su[pos][1]) , lazy[pos] ^= 1;
    }
    inline void push(int pos) {
        if( lazy[pos] ) apply(lson(pos)) , apply(rson(pos)) , lazy[pos] ^= 1;
    }
    inline void build(int pos,int l,int r,const int &fix) { // fix will be 1 if build even .
        if( l == r ) return void( su[pos][0] = ( l & 1 ) ^ fix );
        const int mid = ( l + r ) >> 1;
        build(lson(pos),l,mid,fix) , build(rson(pos),mid+1,r,fix) , maintain(pos);
    }
    inline void update(int pos,int l,int r,const int &ll,const int &rr) {
        if( ll <= l && r <= rr ) return apply(pos);
        const int mid = ( l + r ) >> 1; push(pos);
        if( ll <= mid ) update(lson(pos),l,mid,ll,rr);
        if( mid < rr ) update(rson(pos),mid+1,r,ll,rr);
        maintain(pos);
    }
    inline ulli query() {
        return su[1][0] * su[1][1];
    }
}sgt[2];

int in[maxn],srt[maxn],len,n;
vector<int> app[maxn];
ulli ans;

int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",in+i) , srt[i] = in[i];
    std::sort(srt+1,srt+1+n) , len = unique(srt+1,srt+1+n) - srt - 1;
    for(int i=1;i<=n;i++) app[in[i]=lower_bound(srt+1,srt+1+len,in[i])-srt].push_back(i);
    for(int i=0;i<2;i++) sgt[i].build(1,0,n,i^1);
    for(int i=len;i>1;i--) {
        for(unsigned j=0;j<app[i].size();j++) for(int k=0;k<2;k++) sgt[k].update(1,0,n,app[i][j],n);
        for(int j=0;j<2;j++) ans += ( srt[i] - srt[i-1] ) * sgt[j].query();
    }
    printf("%llu\n",ans);
    return 0;
}
