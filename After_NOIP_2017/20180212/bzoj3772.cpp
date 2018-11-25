//#include<iostream>
#include<cstdio>
//#include<cstring>
#include<algorithm>
#include<vector>
#define lli long long int
//#define debug cout
//using namespace std;
const int maxn=1e5+1e2,maxc=4500000;

namespace T {
    int lson[maxc],rson[maxc],sum[maxc],cnt;
    inline void build(int pos,int l,int r) {
        if( l == r ) return;
        const int mid = ( l + r ) >> 1;
        build(lson[pos]=++cnt,l,mid) , build(rson[pos]=++cnt,mid+1,r);
    }
    inline void insert(int pos,int pre,int l,int r,int tar,int x) {
        lson[pos] = lson[pre] , rson[pos] = rson[pre];
        if( l == r ) {
            sum[pos] = sum[pre] + x;
            return;
        }
        const int mid = ( l + r ) >> 1;
        if( tar <= mid ) insert(lson[pos]=++cnt,lson[pre],l,mid,tar,x);
        else insert(rson[pos]=++cnt,rson[pre],mid+1,r,tar,x);
        sum[pos] = sum[lson[pos]] + sum[rson[pos]];
    }
    inline int calsum(int a1,int a2,int b1,int b2) {
        return sum[a1] + sum[a2] - sum[b1] - sum[b2];
    }
    inline int query(int a1,int a2,int b1,int b2,int l,int r,int ll,int rr) {
        if( ll <= l && r <= rr ) return calsum(a1,a2,b1,b2);
        const int mid = ( l + r ) >> 1;
        if( rr <= mid ) return query(lson[a1],lson[a2],lson[b1],lson[b2],l,mid,ll,rr);
        if( ll > mid ) return query(rson[a1],rson[a2],rson[b1],rson[b2],mid+1,r,ll,rr);
        return query(lson[a1],lson[a2],lson[b1],lson[b2],l,mid,ll,rr) + query(rson[a1],rson[a2],rson[b1],rson[b2],mid+1,r,ll,rr);
    }
}

struct Path {
    int x,y;
    friend bool operator < (const Path &a,const Path &b) {
        return a.x != b.x ? a.x < b.x : a.y < b.y;
    }
    friend bool operator == (const Path &a,const Path &b) {
        return a.x == b.x && a.y == b.y;
    }
}ps[maxn];
int s[maxn],t[maxn<<1],nxt[maxn<<1];
int top[maxn],fa[maxn],dep[maxn],siz[maxn],son[maxn];
int in[maxn],out[maxn],root[maxn];
std::vector<int> v[maxn];
int n,m;

inline void addedge(int from,int to) {
    static int cnt = 0;
    t[++cnt] = to , nxt[cnt] = s[from] , s[from] = cnt;
}
inline void doubledge(int from,int to) {
    addedge(from,to) , addedge(to,from);
}

inline void dfs(int pos) {
    static int dd = 0;
    in[pos] = ++dd;
    siz[pos] = 1;
    for(int at=s[pos];at;at=nxt[at])
        if( t[at] != fa[pos] ) {
            fa[t[at]] = pos , dep[t[at]] = dep[pos] + 1;
            dfs(t[at]);
            siz[pos] += siz[t[at]];
            if( siz[t[at]] > siz[son[pos]] ) son[pos] = t[at];
        }
    out[pos] = ++dd;
}
inline void bul(int pos) {
    top[pos] = pos == son[fa[pos]] ? top[fa[pos]] : pos;
    root[pos] = root[fa[pos]];
    for(unsigned i=0;i<v[pos].size();i++) {
        int t;
        //debug<<"pos = "<<pos<<"v = "<<v[pos][i]<<endl;
        t = root[pos] , T::insert(root[pos]=++T::cnt,t,1,n<<1,in[v[pos][i]],1);
        t = root[pos] , T::insert(root[pos]=++T::cnt,t,1,n<<1,out[v[pos][i]],-1);
    }
    for(int at=s[pos];at;at=nxt[at])
        if( t[at] != fa[pos] )
            bul(t[at]);
}
inline int lca(int x,int y) {
    while( top[x] != top[y] ) {
        if( dep[top[x]] > dep[top[y]] ) x = fa[top[x]];
        else y = fa[top[y]];
    }
    return dep[x] < dep[y] ? x : y;
}

inline lli gcd(lli a,lli b) {
    if( ! ( a && b ) ) return a | b;
    register lli t;
    while( t = a % b )
        a = b , b = t;
    return b;
}


int main() {
    //freopen("dat.txt","r",stdin);
    static int m;
    static lli ans,full,g;
    scanf("%d%d",&n,&m);
    for(int i=1,a,b;i<n;i++) {
        scanf("%d%d",&a,&b);
        doubledge(a,b);
    }
    for(int i=1;i<=m;i++) {
        scanf("%d%d",&ps[i].x,&ps[i].y);
        v[ps[i].x].push_back(ps[i].y);
    }
    dfs(1) , bul(1);
    T::build(root[0]=++T::cnt,1,n<<1);
    for(int i=1;i<=m;i++) {
        int l = lca(ps[i].x,ps[i].y);
        //debug<<"x = "<<ps[i].x<<"y = "<<ps[i].y<<"lca = "<<l<<endl;
        ans += T::query(root[ps[i].x],root[ps[i].y],root[l],root[fa[l]],1,n<<1,in[l],in[ps[i].x]);
        ans += T::query(root[ps[i].x],root[ps[i].y],root[l],root[fa[l]],1,n<<1,in[l],in[ps[i].y]);
        ans -= T::query(root[ps[i].x],root[ps[i].y],root[l],root[fa[l]],1,n<<1,in[l],in[l]);
        --ans;
    }
    //debug<<"Inital ans = "<<ans<<endl; 
    std::sort(ps+1,ps+1+m);
    for(int i=1,j;i<=m;i=j+1) {
        j = i;
        while( ps[j+1] == ps[i] ) ++j;
        ans -= ( (lli) ( j - i + 1 ) ) * ( j - i ) >> 1;
    }
    full = ( (lli) m ) * ( m - 1 ) >> 1;
    //debug<<"full = "<<full<<endl;
    g = gcd(ans,full);
    //debug<<"g = "<<g<<endl;
    //debug<<ans<<"/"<<full<<endl;
    //for(int i=1;i<=n;i++) debug<<in[i]<<" "<<out[i]<<endl;
    //cerr<<"max node = "<<T::cnt<<endl;
    if( g ) ans /= g , full /= g;
    if( m == 1 ) puts("0/1");
    else printf("%lld/%lld\n",ans,full);
    return 0;
}

