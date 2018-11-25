#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define debug cout
using namespace std;
const int maxn=1e5+1e2;
const double alpha=0.75;

char in[maxn];
int sa[maxn],rnk[maxn],h[maxn],sal,li;

struct SuffixBalancedTree {
    int lson[maxn],rson[maxn],siz[maxn],nv[maxn],at[maxn],seq[maxn],cnt,root,fail,failfa,sql;
    double v[maxn],vfl,vfr;
    
    inline bool cmp(int x,int y) {
        if( !x || !y ) return !x;
        return in[x] != in[y] ? in[x] < in[y] : v[at[x-1]] < v[at[y-1]];
    }
    inline void upgrade(int pos,double l,double r) {
        siz[pos] = siz[lson[pos]] + siz[rson[pos]] + 1;
        if( std::max(siz[lson[pos]],siz[rson[pos]]) > siz[pos] * alpha ) fail = pos , failfa = -1 , vfl = l , vfr = r;
        else if( fail == lson[pos] || fail == rson[pos] ) failfa = pos;
    }
    inline void insert(int &pos,double l,double r,const int &id) {
        if( !pos ) {
            nv[at[id]=pos=++cnt] = id , siz[pos] = 1 , v[pos] = ( l + r ) / 2.0;
            return;
        } const double vmid = ( l + r ) / 2.0;
        if( cmp(nv[pos],id) ) insert(rson[pos],vmid,r,id) , upgrade(pos,l,r);
        else insert(lson[pos],l,vmid,id) , upgrade(pos,l,r);
    }
    inline int rebuild(int ll,int rr,double l,double r) {
        const int mid = ( ll + rr ) >> 1 , pos = seq[mid];
        const double vmid = ( l + r ) / 2.0; v[pos] = vmid , siz[pos] = rr - ll + 1;
        if( ll < mid ) lson[pos] = rebuild(ll,mid-1,l,vmid);
        if( mid < rr ) rson[pos] = rebuild(mid+1,rr,vmid,r);
        return pos;
    }
    inline void recycle(int pos) {
        if(lson[pos]) recycle(lson[pos]);
        seq[++sql] = pos;
        if(rson[pos]) recycle(rson[pos]);
        lson[pos] = rson[pos] = siz[pos] = 0;
    }
    inline void insert(const int &id) {
        fail = 0 , failfa = -1 , insert(root,0,1,id);
        if(fail) {
            sql = 0 , recycle(fail);
            if( !~failfa ) root = rebuild(1,sql,0,1);
            else ( fail == lson[failfa] ? lson[failfa] : rson[failfa] ) = rebuild(1,sql,vfl,vfr);
        }
    }
    inline void dfs(int pos) {
        if(lson[pos]) dfs(lson[pos]);
        sa[++sal] = li - nv[pos] + 1;
        if(rson[pos]) dfs(rson[pos]);
    }
}sbt;

inline void geth() {
    for(int i=1;i<=li;i++) rnk[sa[i]] = i;
    for(int i=1,k=0;i<=li;i++,k-=(bool)k) {
        const int p = sa[rnk[i]-1];
        while( in[i+k] == in[p+k] ) ++k;
        h[rnk[i]-1] = k;
    }
}

int main() {
    scanf("%s",in+1) , li = strlen(in+1) , std::reverse(in+1,in+1+li);
    for(int i=0;i<=li;i++) sbt.insert(i);
    sal = -1 , sbt.dfs(sbt.root) , std::reverse(in+1,in+1+li) , in[li+1] = '#' , geth();
    for(int i=1;i<=li;i++) printf("%d%c",sa[i],i!=li?' ':'\n');
    for(int i=1;i<li;i++) printf("%d%c",h[i],i!=li-1?' ':'\n');
    return 0;
}
