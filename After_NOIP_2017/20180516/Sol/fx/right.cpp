#pragma GCC optimize("Ofast")
#include<cstdio>
#include<algorithm>
#include<map>
#include<vector>
#include<cmath>
const int maxn=1e5+1e2,maxe=325;

int n,m,a;

namespace Even {
    int dat[maxn],bel[maxn],st[maxe],ed[maxe],add[maxe];
    std::vector<int> cont[maxe][2];
    std::map<int,int> app[maxe];
    
    inline void rebuild(int id) {
        cont[id][0].clear() , cont[id][1].clear() , app[id].clear();
        for(int i=st[id];i<=ed[id];i++) cont[id][dat[i]&1].push_back(dat[i]) , ++app[id][dat[i]];
        std::sort(cont[id][0].begin(),cont[id][0].end()) , std::sort(cont[id][1].begin(),cont[id][1].end());
    }
    inline void partadd(int id,int l,int r,const int &x) {
        l = std::max( l , st[id] ) , r = std::min( r , ed[id] );
        for(int i=l;i<=r;i++) dat[i] = ( dat[i] + x ) % ( a + 1 );
    }
    inline void push(int id) {
        if( add[id] ) partadd(id,st[id],ed[id],add[id]) , add[id] = 0;
    }
    inline void fulladd(int id,const int &x) {
        add[id] = ( add[id] + x ) % ( a + 1 );
    }
    inline void modify(int l,int r,const int &x) {
        if( bel[l] == bel[r] ) push(bel[l]) , partadd(bel[l],l,r,x) , rebuild(bel[l]);
        else {
            push(bel[l]) , partadd(bel[l],l,r,x) , rebuild(bel[l]);
            for(int i=bel[l]+1;i<bel[r];i++) fulladd(i,x);
            push(bel[r]) , partadd(bel[r],l,r,x) , rebuild(bel[r]);
        }
    }
    
    inline int partquery(int id,int l,int r) {
        int ret = 0; l = std::max( l , st[id] ) , r = std::min( r , ed[id] );
        for(int i=l,t;i<=r;i++) t = ( dat[i] + add[id] ) % ( a + 1 ) , ret ^= ( t == a ? 2 : ( t & 1 ) );
        return ret;
    }
    inline int fullquery(int id) {
        int siz0=0,siz1=0,siz2=0,ned=a-add[id];
        int p0 = std::lower_bound(cont[id][0].begin(),cont[id][0].end(),a+1-add[id]) - cont[id][0].begin();
        int p1 = std::lower_bound(cont[id][1].begin(),cont[id][1].end(),a+1-add[id]) - cont[id][1].begin();
        siz0 += p0 , siz1 += p1 , siz0 += cont[id][1].size() - p1 , siz1 += cont[id][0].size() - p0 , siz2 = app[id][ned];
        ( ned & 1 ? siz1 : siz0 ) -= siz2;
        if( add[id] & 1 ) std::swap(siz0,siz1);
        return ( siz1 & 1 ) ^ ( ( siz2 & 1 ) << 1 );
    }
    inline int query(int l,int r) {
        if( bel[l] == bel[r] ) return partquery(bel[l],l,r);
        int ret = partquery(bel[l],l,r) ^ partquery(bel[r],l,r);
        for(int i=bel[l]+1;i<bel[r];i++) ret ^= fullquery(i);
        return ret;
    }
    
    inline void init() {
        for(int i=1;i<=n;i++) dat[i] %= a+1;
        int sq = sqrt(n) , cnt = 0;
        for(int l=1,r;l<=n;l=r+1) {
            r = std::min( l + sq - 1 , n ) , st[++cnt] = l , ed[cnt] = r;
            for(int i=l;i<=r;i++) bel[i] = cnt;
            rebuild(cnt);
        }
    }
    inline void main() {
        for(int i=1;i<=n;i++) scanf("%d",dat+i);
        init();
        for(int i=1,o,l,r,x;i<=m;i++) {
            scanf("%d%d%d",&o,&l,&r);
            if( o == 1 ) puts(query(l,r)?"1":"0");
            else scanf("%d",&x) , modify(l,r,x);
        }
    }
}

namespace Odd {
    int dat[maxn],siz[maxn<<2][2],lazy[maxn<<2];
    
    #define lson(pos) (pos<<1)
    #define rson(pos) (pos<<1|1)
    
    inline void build(int pos,int l,int r) {
        if( l == r ) return void( siz[pos][dat[l]&1] = 1 );
        const int mid = ( l + r ) >> 1;
        build(lson(pos),l,mid) , build(rson(pos),mid+1,r) ,
        siz[pos][0] = siz[lson(pos)][0] + siz[rson(pos)][0] , siz[pos][1] = siz[lson(pos)][1] + siz[rson(pos)][1];
    }
    inline void apply(int pos) {
        lazy[pos] ^= 1 ,  std::swap(siz[pos][0],siz[pos][1]);
    }
    inline void push(int pos) {
        if( lazy[pos] ) apply(lson(pos)) , apply(rson(pos)) , lazy[pos] = 0;
    }
    inline void update(int pos,int l,int r,const int &ll,const int &rr) {
        if( ll <= l && r <= rr ) return apply(pos);
        const int mid = ( l + r ) >> 1; push(pos);
        if( ll <= mid ) update(lson(pos),l,mid,ll,rr);
        if( mid < rr ) update(rson(pos),mid+1,r,ll,rr);
        siz[pos][0] = siz[lson(pos)][0] + siz[rson(pos)][0] , siz[pos][1] = siz[lson(pos)][1] + siz[rson(pos)][1];
    }
    inline int query(int pos,int l,int r,const int &ll,const int &rr) {
        if( ll <= l && r <= rr ) return siz[pos][1] & 1;
        const int mid = ( l + r ) >> 1; push(pos);
        if( rr <= mid ) return query(lson(pos),l,mid,ll,rr);
        else if( ll > mid ) return query(rson(pos),mid+1,r,ll,rr);
        return query(lson(pos),l,mid,ll,rr) ^ query(rson(pos),mid+1,r,ll,rr);
    }
    inline void main() {
        for(int i=1;i<=n;i++) scanf("%d",dat+i);
        build(1,1,n);
        for(int i=1,o,l,r,x;i<=m;i++) {
            scanf("%d%d%d",&o,&l,&r);
            if( o == 1 ) puts(query(1,1,n,l,r)?"1":"0");
            else {
                scanf("%d",&x);
                if( x & 1 ) update(1,1,n,l,r);
            }
        }
    }
}

int main() {
    scanf("%d%d%d",&n,&m,&a);
    if( a & 1 ) Odd::main();
    else Even::main();
    return 0;
}

