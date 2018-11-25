#pragma GCC optimize("Ofast")
#pragma GCC optimize("no-stack-protector")
#pragma GCC target("avx")
#include<cstdio>
#include<cstring>
#include<algorithm>
const int maxn=1e6+1e2,maxl=23;
const double alpha=0.95;

char in[maxn];
int Log[maxn],li,ans;

struct SuffixArray  {
    int sa[maxn],rnk[maxn],h[maxn],rmq[maxn][maxl],n,m,sal;
    
    int at[maxn],lson[maxn],rson[maxn],siz[maxn],sf[maxn],root,cnt;
    int seq[maxn],sql;
    int fail,failfa;
    double v[maxn],vfl,vfr;
    
    inline bool cmp(int x,int y) {
        if( !x || !y ) return !x;
        if( in[x] != in[y] ) return in[x] < in[y];
        else return v[at[x-1]] < v[at[y-1]];
    }
    inline void upgrade(int pos,double l,double r) {
        siz[pos] = siz[lson[pos]] + siz[rson[pos]] + 1;
        if( std::max( siz[lson[pos]] , siz[rson[pos]] ) > siz[pos] * alpha ) fail = pos , failfa = -1 , vfl = l , vfr = r;
        else if( fail == lson[pos] || fail == rson[pos] ) failfa = pos;
    }
    inline void insert(int &pos,double l,double r,const int &id) {
        if( !pos ) {
            v[at[id]=pos=++cnt]= ( l + r ) / 2.0 , siz[pos] = 1 , sf[pos] = id;
            return;
        } const double vmid = ( l + r ) / 2.0;
        if( cmp(sf[pos],id) ) insert(rson[pos],vmid,r,id) , upgrade(pos,l,r); // id > sf[pos] .
        else insert(lson[pos],l,vmid,id) , upgrade(pos,l,r);
    }
    inline int rebuild(int ll,int rr,double l,double r) {
        const int mid = ( ll + rr ) >> 1 , pos = seq[mid];
        const double vmid = ( l + r ) / 2.0; v[pos] = vmid , siz[pos] = rr - ll + 1;
        if( ll < mid ) lson[pos] = rebuild(ll,mid-1,l,vmid);
        if( mid < rr ) rson[pos] = rebuild(mid+1,rr,vmid,r);
        return pos;
    }
    inline void dfs(int pos) {
        if(lson[pos]) dfs(lson[pos]);
        seq[++sql] = pos;
        if(rson[pos]) dfs(rson[pos]);
        lson[pos] = rson[pos] = siz[pos] = 0;
    }
    inline void insert(const int &id) {
        fail = 0 , failfa = -1 , insert(root,0,1,id);
        if(fail) {
            sql = 0 , dfs(fail);
            if( ~failfa ) {
                if( fail == lson[failfa] ) lson[failfa] = rebuild(1,sql,vfl,vfr);
                else rson[failfa] = rebuild(1,sql,vfl,vfr);
            } else root = rebuild(1,sql,0,1);
        }
    }
    inline void getsa(int pos) {
        if(lson[pos]) getsa(lson[pos]);
        sa[++sal] = n - sf[pos] + 1;
        if(rson[pos]) getsa(rson[pos]);
    }
    
    inline void work(char* in,int li) {
        n = li , std::reverse(in+1,in+1+n) , in[n+1] = '#';
        insert(0);
        for(int i=1;i<=li;i++) insert(i);
        getsa(root) , std::reverse(in+1,in+1+n) , geth() , initrmq();
    }
    
    inline void geth() {
        for(int i=1;i<=n;i++) rnk[sa[i]] =i;
        for(int i=1,k=0,j;i<=n;i++) {
            k = k ? k - 1 : 0 , j = sa[rnk[i]-1];
            while( in[i+k] == in[j+k] ) ++k;
            h[rnk[i]-1] = k;
        }
    }
    inline void initrmq() {
        for(int i=1;i<n;i++) rmq[i][0] = h[i];
        for(int j=1;j<=Log[n];j++) for(int i=1;i+(1<<(j-1))<=n;i++) rmq[i][j] = std::min( rmq[i][j-1] , rmq[i+(1<<(j-1))][j-1] );
    }
    inline int query(int l,int r) {
        l = rnk[l] , r = rnk[r];
        if( l > r ) std::swap(l,r);
        --r;
        int L = Log[r-l+1];
        return std::min( rmq[l][L] , rmq[r-(1<<L)+1][L] );
    }
}prf,suf;

inline int lcp(int i,int j) {
    return prf.query(i,j);
}
inline int lcs(int i,int j) {
    return suf.query(li-j+1,li-i+1);
}
inline void calc(int len) {
    for(int st=1,sst,lc;st+len<=li&&!ans;st+=len) {
        sst = st + len , lc = lcp(st,sst) + lcs(st-1,sst-1);
        if( lc >= len ) ans = len * 2;
    }
}

int main() {
    fread(in+1,1,maxn,stdin) , li = strlen(in+1);
    for(int i=2;i<=li;i++) Log[i] = Log[i>>1] + 1;
    prf.work(in,li) , std::reverse(in+1,in+1+li) , suf.work(in,li);
    for(int i=li;i&&!ans;i--) calc(i);
    printf("%d\n",ans);
    return 0;
}
